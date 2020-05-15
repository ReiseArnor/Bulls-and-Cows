#include "FBullsandCows.hpp"

void PrintIntro();
FText getValidGuess();
void PlayGame();
bool Ask(FString AskThis);
void AskToSetWords();
void GameWinLoseScreen(bool status);

FBullsandCows BCGAME;

int main()
{
    bool play = true;

    do{
        AskToSetWords();
        PrintIntro();
        PlayGame();
        play = Ask("do you want to play again?");
        std::cout << std::endl;
    }while(play == true);

    return 0;
}

bool Ask(FString AskThis)
{
    FText res = "";
    std::cout << AskThis << " (y/n): ";
    getline(std::cin, res);
    return (res[0] == 'y') || (res[0] == 'Y');
}

void AskToSetWords()
{
    if (Ask("do you want to set the words?"))
    {
        bool Adding = true;
        FText AddWord = "";

        while (Adding)
        {
            std::cout << "write the word: ";
            getline(std::cin, AddWord);
            EWords status = EWords::Invalid;
            status = BCGAME.GuessValidity(AddWord);

            switch(status)
            {
                case EWords::Not_Isogram:
                    std::cout << "\nERROR. please enter a Isogram word.\n";
                    break;
                case EWords::Not_Lowercase:
                    std::cout << "\nERROR. please use lowercase only.\n";
                    break;
                case EWords::Not_Valid_Char:
                    std::cout << "\nERROR. please do not use special characters.\n";
                    break;
                default:
                    BCGAME.AddHiddenWord(AddWord);
                    std::cout << "\nWord added!!!\n";
                    break;
            }

            Adding = Ask("do you want to add another word?");
        }
        BCGAME.Reset();
    }
    else
    {
        BCGAME.Reset();
        return;
    }
}

void PlayGame()
{
    int32 CurrentTry = BCGAME.GetCurrentTry();
    int32 MaxTries = BCGAME.GetMaxTries();
    FText Guess = "";
    bool gamestat;

    while(!BCGAME.GameWon(Guess) && CurrentTry <= MaxTries)
    {
        Guess = getValidGuess();
        FBullsCowsCount FBullsCowsCount = BCGAME.SubmitGuess(Guess);
        std::cout << "Bulls " << FBullsCowsCount.Bulls;
        std::cout << ". Cows " << FBullsCowsCount.Cows << "\n\n"; 

        if(!BCGAME.GameWon(Guess) && CurrentTry > MaxTries)
        { 
            gamestat = false; 
        }
        else if (BCGAME.GameWon(Guess) && CurrentTry <= MaxTries) 
        { 
            gamestat = true; 
        }
        else if (BCGAME.GameWon(Guess) && CurrentTry > MaxTries) 
        { 
            gamestat = false; 
        }

        CurrentTry = BCGAME.GetCurrentTry();
    }
    GameWinLoseScreen(gamestat);
    return;
}


FText getValidGuess()
{
    EWords status = EWords::Invalid;
    do{
        int32 CurrentTry = BCGAME.GetCurrentTry();
        FText Guess = "";
        std::cout << "Try " << CurrentTry << ". Enter your guess: "; 
        getline(std::cin, Guess);
        status = BCGAME.GuessValidity(Guess);

        switch(status)
        {
            case EWords::Wrong_Length:
                std::cout << "\nplease enter a " << BCGAME.GetHiddenWordLength() << " letter word.\n";
                break;
            case EWords::Not_Isogram:
                std::cout << "\nplease enter a Isogram word.\n";
                break;
            case EWords::Not_Lowercase:
                std::cout << "\nplease use lowercase only.\n";
                break;
            case EWords::Not_Valid_Char:
                std::cout << "\nplease do not use special characters.\n";
                break;
            default:
                status = EWords::OK;
                return Guess;
        }
    }while (status != EWords::OK);
    
}

void PrintIntro()
{
    std::cout << "welcome to bulls and cows!" << std::endl;
    std::cout << "can you guess the " << BCGAME.GetHiddenWordLength();
    std::cout << " letters word isogram im thinking of?" << std::endl;
    return;
}

void GameWinLoseScreen(bool status)
{
    if(status) std::cout << "CONGRATULATIONS YOU WON!!!" << std::endl;
    if(!status) std::cout << "Sorry, better luck next time..." << std::endl;
    return;
}