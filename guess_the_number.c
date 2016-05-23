/*===========================================================================================

NAME: guess_the_number.c

AUTHOR: Camron Khan
DATE: 3/28/16

DESCRIPTION: Two players attempt to guess a number between 0 and 99

INSTRUCTIONS:
-- Players are assigned guessing order randomly
-- During their designated turn, players may choose to submit a guess or pass
-- Players are given feedback whether their guesses are too high, too low, or correct
-- Players cannot pass two turns in a row
-- Players may pass a maximum of 3 times
-- Play continues until a player guesses the number correctly 

===========================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define player data type
typedef struct {
	int number;					// Player's number
	int passed_last_turn;		// Pass flag tracking if passed on last turn
	int total_passes;			// Number of times player has passed
} player;

/*
	Procedure updating the active player at the conclusion of a turn
	int ap 			The active player
	return int 		2 if passing play to player 2; otherwise 1
*/
int change_active_player(int ap) {
	if (ap == 1) {
		return 2;
	}
	else {
		return 1;
	}
}

/*
	Procedure verifying if a player is allowed to pass
	Player must not have passed during last turn and cannot exceed 3 passes
	player p[] 		Array of players
	int ap 			The active player
	return int 		1 if player allowed to pass; otherwise 0
*/
int check_can_pass(player p[], int ap) {
	if (p[ap-1].passed_last_turn == 0 && p[ap-1].total_passes < 3) {
		return 1;
	}
	else {
		return 0;
	}
}

/*
	Procedure updating a player's last pass flag and pass counter'
	player p[]		Array of players
	int ap 			The active player
	int pf 			The pass flag (0 to reset; otherwise 1 if just passed)
	int pc 			Number of passes to add to counter
	return void
*/
void update_pass_attributes(player p[], int ap, int pf, int pc) {
	p[ap-1].passed_last_turn = pf;
	p[ap-1].total_passes += pc;
}

main() {

	// Create array of two players
	player players[2];

	// Initialize player 1
	players[0].number = 1;
	players[0].passed_last_turn = 0;
	players[0].total_passes = 0;

	// Initialize player 2
	players[1].number = 2;
	players[1].passed_last_turn = 0;
	players[1].total_passes = 0;

	// Set seed variable and generate pseudorandom number between 1 and 100 to be guessed
	srand(time(NULL));
	int target = rand() % 100 + 1;

	// Generate pseudorandom number between 1 and 2 to assign starting player
	int active_player = rand() % 2 + 1;

	// Initialize correct guess flag to 0
	int correct_guess = 0;

	// Game introduction
	printf("\n*****************************\nWelocome to Guess the Number!\n*****************************\n\n");
	printf("Player %i goes first. Enter your number to make a guess.\n\n", active_player);

	// Game engine is a do-while loop, which continues until correct guess flag is set to 1
	do {
		int player_number;						// Temp variable to store player's inputted number
		printf("Player Number (1 or 2): ");		// Request player's number
		scanf("%i", &player_number);			// Store player's number in player_num
		printf("\n");
		
		// If incorrect player number is entered, notify player and return to query
		if (player_number != active_player) {
			printf("You have to wait your turn!\n\n");
		}
		// Otherwise, prompt player for a guess
		else {
			char player_guess[10];							// Temp variable to store player's inputted guess
			printf("Enter Your Guess (1-100 or PASS): ");	// Request player's guess
			scanf("%s", player_guess);						// Store player's guess in player_guess
			printf("\n");

			// Verify if player chose to pass
			int player_choice = strcasecmp(player_guess, "PASS");

			// If player chose to pass...
			if (player_choice == 0) {

				// Verify if player is allowed to pass
				int passable = check_can_pass(players, active_player);

					// If player cannot pass, notify player and return to query
					if (passable == 0) {
						printf("You may not pass. Please try again.\n\n");
					}
					// Otherwise, increment pass flag / pass counter and update active player to next player
					else {
						update_pass_attributes(players, active_player, 1, 1);
						printf("Player %i passed. You have passed %i time(s). You have %i pass(es) remaining.\n\n",
							active_player, players[active_player-1].total_passes, 3-players[active_player-1].total_passes);
						active_player = change_active_player(active_player);
					}
			}
			// Otherwise, verify if correct guess was entered
			else {
				// Convert player input to integer
				int player_guess_int = atoi(player_guess);

				// If guess was too high, notify player, update pass flag, and update active player to next player
				if (player_guess_int > target) {
					printf("Too high.\n\n");
					update_pass_attributes(players, active_player, 0, 0);
					active_player = change_active_player(active_player);
				}
				// If guess was too low, notify player, update pass flag, and update active player to next player
				else if (player_guess_int < target) {
					printf("Too low.\n\n");
					update_pass_attributes(players, active_player, 0, 0);
					active_player = change_active_player(active_player);
				}
				// If guess was correct, notify player and set correct guess flag to 1 to exit loop
				else {
					printf("Player %i wins! The correct number is %i!\n", player_number, player_guess_int);
					correct_guess = 1;
				}
			}
		}
	} while (correct_guess == 0);

	printf("\n************************************\nThanks for playing Guess the Number!\n************************************\n\n");
}