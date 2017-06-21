/*This is the console executable, that makes use of the BullCow Class
This acts as view in MVC pattern, and is responsible for
all user interaction. For game logic see the FBullCowGame class.

*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPLayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game (BCGame.MyCurrentTry = 1, BCGame.MyMaxTries = 5)

					 //entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPLayAgain();
	} while (bPlayAgain);

	return 0;
}

// introduce the game
void PrintIntro()
{
	std::cout << R"(
                            .-.
                           ##  )
                           *

                         _.-+*'`*+-._
                       ,##  _    _   #.
                      ;### ((.;;.))  ##:
                .=._.;    ,-*:;;:*-. *##:._.=,
                 >##;    *-')_@@_(`-*   ;###<
 ---------------`****------(o `` o)-----*****'---------------
                            `-""-'                             )" << '\n';
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isograme I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {	// ! means == false
		FText Guess = GetValidGuess(); // TODO make loop checking valid

									   // Submit valid guess to the game, and recive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() //Not getter but function which takes 'cin'
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() - CurrentTry + 1 << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// Check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);// keep looping until we get no errors
	return Guess;
}

bool AskToPLayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { std::cout << "Well done - You win!\n"; }
	else { std::cout << "Better luck next time!\n"; }
}