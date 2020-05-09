#ifndef my_class_bc
#define my_class_bc
#include <string>
#include <iostream>
#include <map>
#include <time.h>
#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullsCowsCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EWords
{
    Invalid,
    OK,
    Not_Isogram,
    Not_Valid_Char,
    Wrong_Length,
    Not_Lowercase
};

class FBullsandCows
{
public:
    FBullsandCows();
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool GameWon(FString Guess) const;
    void Reset();
    EWords GuessValidity(FString Guess) const;
    FBullsCowsCount SubmitGuess(FString Guess);

private:
    int32 CurrentTry;
    int32 MaxTries;
    FString HiddenWord;
    TMap<int32, FString> HiddenWords;
    void SetHiddenWords();
    FString SelectHiddenWord();
    bool IsIsogram(FString guess) const;
    bool IsLowercase(FString guess) const;

};

#endif