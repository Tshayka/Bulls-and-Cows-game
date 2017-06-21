#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// two values initialised to zero
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
	int32 GetHiddenWordLength() const; //Getter
	bool IsGameWon() const;	//Getter
	EGuessStatus CheckGuessValidity(FString) const; //Getter

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
