#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() // we can also put values and types into brackets  
{
	Reset();
}


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; } //Getter
bool FBullCowGame::IsGameWon() const { return bGameIsWon; } //Getter -> these "::" say "I am a part of FBullCowGame class "
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,16 },{ 7,20 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
} //Getter

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "pla";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }
	else if (!IsLowerCase(Guess)) { return EGuessStatus::Not_Lowercase; }
	else if (Guess.length() != GetHiddenWordLength()) { return EGuessStatus::Wrong_length; }
	else { return EGuessStatus::OK; }

} //TODO make actual error

  // recieves a VALID guess, increments turns, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length(); //assuming same length as guess

	for (int32 i = 0; i < WordLenght; i++) {
		for (int32 j = 0; j < WordLenght; j++) {
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) { BullCowCount.Bulls++; }
				else { BullCowCount.Cows++; }
			}
		}
	}

	if (BullCowCount.Bulls == WordLenght)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // Iteracja przez TMap
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) return false;
		else { LetterSeen[Letter] = true; }
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}


// cont - Funkcja, która jest const to funkcja, która obiecuje, ¿e jeœli siê j¹ wywo³a na rzecz jakiegoœ obiektu, to nie bêdzie modyfikowaæ jego danych sk³¹dowych. 
// Jest to wazne w sytuacjach, gdy zamierzamy w danej klasie definiowaæ sobie obiekty typu const