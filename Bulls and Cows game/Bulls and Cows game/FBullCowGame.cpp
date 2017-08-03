#pragma once
#include "FBullCowGame.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <ctime>
#include <vector>
#include <map>
#define TMap std::map

// Namespace from Unreal Engine
using int32 = int;
using FText = std::string;

// For constructor we can also put values and types into brackets  
FBullCowGame::FBullCowGame() 
{
	FirstGame();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; } //Getter
int32 FBullCowGame::GetMyRound() const { return MyRound; } //Getter
bool FBullCowGame::IsGameWon() const { return bGameIsWon; } //Getter -> these "::" say "I am a part of FBullCowGame class "
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsFirstGame() const { return bFirstGame; }

bool FBullCowGame::SetGameStatus() { return bFirstGame = false; } //Setter
int32 FBullCowGame::IncrementRound() { return MyRound++; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ { 3,5 },{ 4,7 },{ 5,10 },{ 6,16 },{ 7,20 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
} //Getter

void FBullCowGame::FirstGame()
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
	std::cout << std::endl;

	bFirstGame = true;
		
	MyDifficulty = AskForDifficulty(bFirstGame);
	
	const FString HIDDEN_WORD = WordToGuess(MyDifficulty);
	MyHiddenWord = HIDDEN_WORD;
	
	MyRound = 0;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

void FBullCowGame::NewGame()
{	
	bFirstGame = false;
	MyCurrentTry = 1;
	bGameIsWon = false;
	
	const FString HIDDEN_WORD = WordToGuess(MyDifficulty);
	MyHiddenWord = HIDDEN_WORD;

	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }
	else if (!IsLowerCase(Guess)) { return EGuessStatus::Not_Lowercase; }
	else if (Guess.length() != GetHiddenWordLength()) { return EGuessStatus::Wrong_length; }
	else { return EGuessStatus::OK; }
}

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
	for (auto Letter : Word) // Iteration by TMap
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

FText FBullCowGame::WordToGuess(int32 MyDifficulty)
{
	// Vectors with stored words
	std::vector<FText> ThreeLetter;
	std::vector<FText> FourLetter;
	std::vector<FText> FiveLetter;
	std::vector<FText> SixLetter;
	std::vector<FText> SevenLetter;

	std::fstream file;
	file.open("Isograms.txt", std::ios::in);

	if (!file.is_open())
	{
		std::cout << "File doesn't exist!";
		exit(0);
	}

	FText line;
	int32 Line_nr = 1;
	FText word;

	while (std::getline(file, line))
	{
		std::stringstream ss(line);

			for (int i = 0; ss >> word; i++)
			{
				if (word.length() == 3) { ThreeLetter.push_back(word); }
				if (word.length() == 4) { FourLetter.push_back(word); }
				if (word.length() == 5) { FiveLetter.push_back(word); }
				if (word.length() == 6) { SixLetter.push_back(word); }
				if (word.length() == 7) { SevenLetter.push_back(word); }
			}
	}
	file.close();

	std::mt19937 randomGenerator(time(0));

	// each one has it own range, because in dictionary is different amount of words
	std::uniform_int_distribution<int> TheeLetterRoll(0, ThreeLetter.size());
	std::uniform_int_distribution<int> FourLetterRoll(0, FourLetter.size());
	std::uniform_int_distribution<int> FiveLetterRoll(0, FiveLetter.size());
	std::uniform_int_distribution<int> SixLetterRoll(0, SixLetter.size());
	std::uniform_int_distribution<int> SevenLetterRoll(0, SevenLetter.size());

	switch (MyDifficulty) {
	case 3:
		MyHiddenWord = ThreeLetter[TheeLetterRoll(randomGenerator)];
		break;
	case 4:
		MyHiddenWord = FourLetter[FourLetterRoll(randomGenerator)];
		break;
	case 5:
		MyHiddenWord = FiveLetter[FiveLetterRoll(randomGenerator)];
		break;
	case 6:
		MyHiddenWord = SixLetter[SixLetterRoll(randomGenerator)];
		break;
	case 7:
		MyHiddenWord = SevenLetter[SevenLetterRoll(randomGenerator)];
		break;
	}
	return MyHiddenWord;
}

int32 FBullCowGame::AskForDifficulty(bool FirstGame)
{
	int32 Difficulty;

	if (FirstGame == true) {
		std::cout << "What length of word do you choose? (3-7)\n";
		do { std::cin >> Difficulty; } while (Difficulty < 3 || Difficulty > 7);
	}
	else {};

	return Difficulty;
}

// const - Funkcja, obiecuje, ¿e jeœli siê j¹ wywo³a na rzecz jakiegoœ obiektu, to nie bêdzie modyfikowaæ jego danych sk³adowych. 
// Jest to wazne w sytuacjach, gdy zamierzamy w danej klasie definiowaæ sobie obiekty typu const
