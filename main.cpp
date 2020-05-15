#include "FBullsandCows.hpp"

void PrintIntro();
FText getValidGuess();
void PlayGame();
bool AskToPlay();
void GameWinLoseScreen(bool status);

FBullsandCows BCGAME;

int main()
{
    bool play = true;
    do{
        PrintIntro();
        PlayGame();
        play = AskToPlay();
        std::cout << std::endl;
    }while(play == true);

    return 0;
}

bool AskToPlay()
{
    FText res = "";
    std::cout << "do you want to play again? (y/n): ";
    getline(std::cin, res);
    return (res[0] == 'y') || (res[0] == 'Y');
}


void PlayGame()
{
    BCGAME.Reset();
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
        }else if (BCGAME.GameWon(Guess) && CurrentTry <= MaxTries) 
        { 
            gamestat = true; 
        }else if (BCGAME.GameWon(Guess) && CurrentTry > MaxTries) 
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
