# guess_the_number

##The Problem:
Create a program that will simulate the child's number guessing game with two players who will play against the computer. The program should have the following requirements:
- When the program is invoked the computer will pseudorandomly choose which player will go first.
- Play begins when the computer interface asks "Player Number". A player number (either 1 or 2) is entered from the keyboard. If a player enters their number at the keyboard and it is not their turn the computer will report back "You have to wait your turn" and return to the query "Player Number". If it is a player's turn the computer will query "Enter Your Guess". The player may either enter a guess or indicate a desire to pass the play to the other player by entering the word PASS at the prompt. If the player enters a guess the computer will report back that the guess is too high, too low or correct and return to the query "Player Number" and pass play to the other player.
- No player may pass two turns in a row, and cannot exceed more than three passes for the entire game. If the player chooses to pass the computer should report "You have passed X number of times, you have Y more times left" before returning the query "Player Number".
- The play progresses until one user provides a correct guess.

##Pseudocode:
```c
STRUCT player  {
Player's number
Pass flag tracking if passed on last turn
Number of times player has passed
}

PROCEDURE change_active_player  {
If active player == 1, return 2
Else return 1
}

PROCEDURE check_can_pass  {
If player did not pass last turn AND player has less than 3 passes, return 1
Else return 0
}

PROCEDURE update_pass_attributes  {
Set pass flag to 1 to prevent subsequent pass
Increment total passes
}

MAIN guess_the_number  {
Create array of two players
Initialize players 1 & 2
Set seed variable and generate pseudorandom number between 1 and 100 to be guessed
Generate pseudorandom number between 1 and 2 to assign starting player
Initialize correct guess flag to 0
Game engine is a do-while loop, which continues until correct guess flag is set to 1  {
Declare temp variable to store player's inputted number
Request player's number
Store player's number in player_num
If incorrect player number is entered, notify player and return to query
Otherwise, prompt player for a guess  {
Declare temp variable to store player's inputted guess
Request player's guess
Store player's guess in player_guess
Verify if player chose to pass
If player chose to pass  {
Verify if player is allowed to pass
If player cannot pass, notify player and return to query
Otherwise, increment pass flag / pass counter and update active player to next player
}
Otherwise, verify if correct guess was entered  {
Convert player input to integer
If guess was too high, notify player, update pass flag, and update active player to next player
If guess was too low, notify player, update pass flag, and update active player to next player
If guess was correct, notify player and set correct guess flag to 1 to exit loop
}
}
} while (correct_guess == 0)
}
```