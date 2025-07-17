#include <iostream>
using namespace std;

enum enChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player1 = 1, Computer = 2, NoOne = 3 };

struct stRoundInfo
{
	short RoundNumber=0;
	enChoice PlayerChoice;
	enChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResult
{
    short GameRounds=0;
    short Player1WinTimes=0;
    short ComputerWinTimes=0;
    short DrawTimes=0;
    enWinner GameWinner;
	string WinnerName = "";
};

short ReadHowManyRounds()
{
	short num = 1;
	do
	{
		cout << "How Many Rounds 1 To 10 : ";
		cin >> num;
	} while (num < 1 || num >10);

	return num;
}

int RandomNumber(int From, int To)
{
	//Function to generate a random number
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::NoOne;
	}
	else if ((((int)RoundInfo.PlayerChoice % 3) + 1) == (int)RoundInfo.ComputerChoice)
	{
		return enWinner::Computer;
	} 
	else
	{
		return enWinner::Player1;
	}
}

string ChoiceName(int Choice)
{
	string Choices [3] = {"Stone", "Paper", "Scissor "};
	return Choices[Choice - 1];
}

enChoice ReadPlayerChoice()
{
	short Choice = 1;
	do
	{
		cout << "Your Choise: Stone[1] , Paper[2]  , Scissor[3] : ";
		cin >> Choice;
	} while (Choice < 1 || Choice >3);

	return (enChoice)Choice;

}

enChoice GetComputerChoice()
{

	return (enChoice)RandomNumber(1, 3);

}

string WinnerName(enWinner Winner)
{
	string Winners[3] = { "[Player1]", "[Computer]", "[No Winner]" };
	return Winners[Winner - 1];

}

enWinner WhoWinTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (Player1WinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::NoOne;
}

stGameResult FillGameResult(short GameRounds, short DrawTimes, short Player1WinTimes, short ComputerWinTimes)
{
	stGameResult GameResult;
	GameResult.GameRounds = GameRounds;
	GameResult.Player1WinTimes = Player1WinTimes;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes= DrawTimes;
	GameResult.GameWinner = WhoWinTheGame(GameResult.Player1WinTimes, GameResult.ComputerWinTimes);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);
	return GameResult;
}

void setWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case  enWinner::Computer: 
		system("color 4f");
		cout << "\a";
		break;

	case  enWinner::Player1:
		system("color 2f");
		break;

	default:
		system("color 6f");
		break;
	}

}

void PrintRoundResult(stRoundInfo RoundInfo)
{

	cout << "\n___________Round [" << RoundInfo.RoundNumber << "] ___________\n\n";
	cout << "Player Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner: " << RoundInfo.WinnerName << endl;
	cout << "________________________________\n\n";

	setWinnerScreenColor(RoundInfo.Winner);
}

stGameResult Playgame(int HowManyRounds)
{
	stRoundInfo RoundInfo;

	int DrawTimes = 0, Player1WinTimes = 0, ComputerWinTimes = 0;

	for (int GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins :\n" ;
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Computer)
		{

			ComputerWinTimes++;
		}
		else if (RoundInfo.Winner == enWinner::Player1)
		{

			Player1WinTimes++;
		}
		else
		{

			DrawTimes++;
		}

		PrintRoundResult(RoundInfo);
	}

	return FillGameResult(HowManyRounds, DrawTimes, Player1WinTimes, ComputerWinTimes);




}

void ReserScreen()
{
	system("cls");
	system("color 0F");
}

string Tabs(int NumberOfTaps)
{
	string tap = "";
	for (int i = 0; i < NumberOfTaps; i++)
	{
		tap += "\t";
	}
	return tap;
}

void ShowGameOverScreen()
{
	cout << Tabs(3) << "______________________________________________________________________________\n\n";
	cout << Tabs(3) << "                           +++  G a m e O v e r  +++\n";
	cout << Tabs(3) << "______________________________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResult GameResult)
{
	cout << Tabs(3) << "________________________________ [Game Result]________________________________" << endl << endl;
	cout << Tabs(3) << "Game Rounds        : " << GameResult.GameRounds << endl;
	cout << Tabs(3) << "Player1 Won Times  : " << GameResult.Player1WinTimes<< endl;
	cout << Tabs(3) << "Computer Won Times : " << GameResult.ComputerWinTimes << endl;
	cout << Tabs(3) << "Draw times         : " << GameResult.DrawTimes << endl;
	cout << Tabs(3) << "Final Winner       : " << GameResult.WinnerName << endl;
	cout << Tabs(3) << "______________________________________________________________________________" << endl << endl;

	setWinnerScreenColor(GameResult.GameWinner);
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ReserScreen();
		stGameResult GameResult = Playgame(ReadHowManyRounds());

		ShowGameOverScreen();

		ShowFinalGameResults(GameResult);

		cout << endl << Tabs(3) << "Do You want to play again ? Y/N ?";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}



int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));

	StartGame();

}