//
//  FBullCowGame.hpp
//  BullCow
//
//  Created by Brandon Gay on 6/1/17.
//  Copyright © 2017 Brandon Gay. All rights reserved.
//

#define FBullCowGame_hpp

#pragma once 
#include <stdio.h>
#include <string>

using FString = std::string;

struct FBullCowCount
{
    int Bulls = 0;
    int Cows = 0;
};

enum class EGuessStatus 
{
    Invalid,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame
{
public:
    FBullCowGame();  //constructor
    
    int GetHiddenWordLength() const;
    int GetMaxTries() const;
    int GetCurrentTry() const;
    
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(std::string) const;
    
    void Reset();
    FBullCowCount SubmitValidGuess(FString);
    
    // try to ignore this and focus on what's above ^^
private:
    int MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};

/* FBullCowGame_hpp */
