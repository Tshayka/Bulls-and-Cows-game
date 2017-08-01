/* The game logic */


#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_length,
	Not_Lowercase,
};


class FBullCowGame
{
public:
	FBullCowGame(); //constructor, initialize start values, no type on begining!

	int32 GetMaxTries() const; //Getter
	int32 GetCurrentTry() const; //Getter
	int32 GetMyRound() const; //Getter
	bool FBullCowGame::IsFirstGame() const;
	int32 GetHiddenWordLength() const; //Getter
	bool IsGameWon() const;	//Getter
	EGuessStatus CheckGuessValidity(FString) const; //Getter

	void FirstGame();
	void NewGame();
	FBullCowCount SubmitValidGuess(FString);
	FString WordToGuess(int32);
	bool SetGameStatus();
	int32 IncrementRound();
	int32 AskForDifficulty(bool);
	// FString SetHiddenWord();


private:
	int32 MyCurrentTry;
	int32 MyRound = 1;
	FString MyHiddenWord;
	int32 MyDifficulty;
	bool bGameIsWon;
	bool bFirstGame;
	

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;

};
