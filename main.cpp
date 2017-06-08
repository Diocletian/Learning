//
//  main.cpp
//  BullCow
//
//  Created by Brandon Gay on 5/24/17.
//  Copyright © 2017 Brandon Gay. All rights reserved.
//
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;

void PrintIntro();
FText GetGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

// instantiate a new game
FBullCowGame BCGame;

int main()
{
    // game will continue so long as user enters yes
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    
    while (bPlayAgain);
    return 0;
}

void PrintIntro()
{
    //introduction
    std::cout << "\nWelcome to Bulls and Cows, a fun word game\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

std::string GetGuess()
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid;
    do
    {
        int CurrentTry = BCGame.GetCurrentTry();
        //get a guess from player
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline (std::cin, Guess);
    
        Status = BCGame.CheckGuessValidity(Guess);
    
        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter a lowercase word.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout <<"Please enter a word without repeating letters.\n\n";
                break;
            default:
                break;
        }
    
    } while (Status != EGuessStatus::OK); //keep looping until we get valid input
    return Guess;
}


void PlayGame()
{
    BCGame.Reset();
    int MaxTries = BCGame.GetMaxTries();
    
    //loop asking for guesses while the game is NOT won
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetGuess();        //submit valid guess to game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        //print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
        
        std::cout << "Your guess was: " << Guess << std::endl;
        std::cout << std::endl;
    }
    PrintGameSummary();
    return;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? (y/n) ";
    FText Response = "";
    std::getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon() == true)
    {
        std::cout << "WELL DONE - YOU WIN!" << std::endl;
    }
    else
    {
        std::cout << "Better luck next time!" << std::endl;
    }
}

