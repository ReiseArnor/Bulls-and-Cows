#include "FBullsandCows.hpp"

/*
FBullsandCows::FBullsandCows()
{
    Reset();
}
*/

int32 FBullsandCows::GetMaxTries() const{ return MaxTries; }
int32 FBullsandCows::GetCurrentTry() const{ return CurrentTry; }
int32 FBullsandCows::GetHiddenWordLength() const{ return HiddenWord.length(); }
bool FBullsandCows::GameWon(FString Guess) const{ return Guess == HiddenWord; }

void FBullsandCows::Reset()
{
    constexpr int32 MAX_TRIES = 8;
    MaxTries = MAX_TRIES;
    HiddenWord = SelectHiddenWord();
    CurrentTry = 1;
    return;
}

EWords FBullsandCows::GuessValidity(FString Guess) const
{
    if(!IsIsogram(Guess))
    {
        return EWords::Not_Isogram;
    }
    else if (false)
    {
        return EWords::Not_Valid_Char;
    }
    else if(!IsLowercase(Guess))
    {
        return EWords::Not_Lowercase;
    }
    else if (GetHiddenWordLength() != Guess.length())
    {
        return EWords::Wrong_Length;
    }
    else
    {
        return EWords::OK;
    }
}

FBullsCowsCount FBullsandCows::SubmitGuess(FString Guess)
{
    CurrentTry++;
    FBullsCowsCount FBullsCowsCount;
    int32 HiddenWordLength = HiddenWord.length();

    for(int32 HDChar = 0; HDChar < HiddenWordLength; HDChar++)
    {
        for(int32 GSChar = 0; GSChar < HiddenWordLength; GSChar++)
        {
            if(Guess[GSChar] == HiddenWord[HDChar]){

                if(HDChar == GSChar){
                    FBullsCowsCount.Bulls++;
                }
                else
                {
                    FBullsCowsCount.Cows++;
                }
             } 
        }
    }

    return FBullsCowsCount;
}

bool FBullsandCows::IsIsogram(FString Guess) const
{
    if(Guess.length() <= 1) { return true; }
    TMap<char, bool> LetterSeen;

    for(auto letter : Guess)
    {
        letter = tolower(letter);
        if(LetterSeen[letter])
        {
            return false;
        }
        else
        {
            LetterSeen[letter] = true;
        }
        
    }
    return true;
}

bool FBullsandCows::IsLowercase(FString Guess) const
{
    for(auto letter : Guess)
    {
        if(letter != tolower(letter))
        {
            return false;
        }
    }
    return true;
}

void FBullsandCows::SetHiddenWords()
{
    if (HiddenWords.size() > 0)
    {
        return;
    }
    else
    {
        HiddenWords[0] = "camp";
        HiddenWords[1] = "world";
        HiddenWords[2] = "sword";
        HiddenWords[3] = "champ";
        HiddenWords[4] = "space";
        HiddenWords[5] = "cowboy";
    }
}

FString FBullsandCows::SelectHiddenWord()
{
    SetHiddenWords();
    srand (time(NULL));
    return HiddenWords[rand() % HiddenWords.size() - 1];
}

void FBullsandCows::AddHiddenWord(FText Word)
{
    FString newWord = Word;
    int32 newN = HiddenWords.size();
    HiddenWords[newN] = newWord;
}