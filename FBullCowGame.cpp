//
//  FBullCowGame.cpp
//  BullCow
//
//  Created by Brandon Gay on 6/1/17.
//  Copyright © 2017 Brandon Gay. All rights reserved.
//
#pragma once 

#include "FBullCowGame.hpp"
#include <string>
#include <map>
#define TMap std::map 

//const makes it so that these methods cannot change variables esatablished within the class
int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int FBullCowGame::GetHiddenWordLength() const { return (int)MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int FBullCowGame::GetMaxTries() const
{
    TMap<int, int> WordLengthToMaxTries { {3,5}, {4,7}, {5,10}, {6,15}, {7,20} };
    return WordLengthToMaxTries[(int)MyHiddenWord.length()];
}

FBullCowGame::FBullCowGame() { Reset(); }

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (GetHiddenWordLength() != Guess.length())
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    //loop through all letters in the hidden word
    int WordLength = (int)MyHiddenWord.length();
    for (int i = 0; i < WordLength; i++)
    {
        //compare letters against the guess
        for (int j = 0; j < WordLength; j++)
        {
            //if they match
            if (Guess[j] == MyHiddenWord[i])
            {
                //if they're in the same place
                if (i == j)
                {
                    BullCowCount.Bulls++; //incriment bulls
                }
                else
                {
                    BullCowCount.Cows++; //incriment cows
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength)
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
    for (auto Letter : Word) //for all letters of the word
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter])
        {
            return false;
        }
        else
        {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
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
