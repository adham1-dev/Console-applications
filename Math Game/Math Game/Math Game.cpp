#include <iostream>
using namespace std;

enum enLevel {easy =1 , med = 2 , hard = 3 , mix =4};
enum enOpType {Add =1 , Sub= 2 , Mul= 3 , Div =4, Mix=5};

struct stGameInfo
{
	int NumberOfQuestion = 0;
	enLevel Level;
	enOpType OpType;
};

struct stQuizz
{
	bool Answer = true;
	int Number1 = 0;
	int Number2 = 0;
	int AnswerCollect = 0;
	int Right = 0;
	int Wrong = 0;
};

int RandomNumber(int From, int To)
{
	//Function to generate a random number
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

short ReadHowManyQuestion()
{
	short num = 1;
	do
	{
		cout << "How Many Question : ";
		cin >> num;
	} while (num < 1 );

	return num;
}

enLevel NumberOfLevel()
{
	short num = 1;
	do
	{
		cout << "Enter Level: easy[1] , Med[2] , Hard[3] , Mix[4] : ";
		cin >> num;
	} while (num < 1 || num >4 );

	return (enLevel)num;
}

enOpType ReadOpType()
{
	short num = 1;
	do
	{
		cout << "Enter Level: Add[1] , Sub[2] , Mul[3] , Div[4] , Mix[5] : ";
		cin >> num;
	} while (num < 1 || num > 5);

	return (enOpType)num;
}

stGameInfo CollectStartInfo()
{
	stGameInfo GameInfo;
	GameInfo.NumberOfQuestion = ReadHowManyQuestion();
	GameInfo.Level=NumberOfLevel();
	GameInfo.OpType = ReadOpType();
	return GameInfo;
}

string OpSympol(enOpType OpType , stQuizz &Quizz)
{
	if (OpType == 5)
		OpType = (enOpType)RandomNumber(1, 4);

	switch (OpType)
	{
	case enOpType::Add:
		Quizz.AnswerCollect = Quizz.Number1 + Quizz.Number2;
		return "+";
	case enOpType::Sub:
		Quizz.AnswerCollect = Quizz.Number1 - Quizz.Number2;
		return "-";
	case enOpType::Mul:
		Quizz.AnswerCollect = Quizz.Number1 * Quizz.Number2;
		return "*";
	case enOpType::Div:
		Quizz.AnswerCollect = Quizz.Number1 / Quizz.Number2;
		return "/";
	default:
		Quizz.AnswerCollect = Quizz.Number1 + Quizz.Number2;
		return "+";
	}
}

int NumberHardness(enLevel Level)
{
	if (Level == 4)
		Level = (enLevel)RandomNumber(1, 3);
	switch (Level)
	{
	case easy:
		return RandomNumber(1, 5);
	case med:
		return RandomNumber(5,10 );
	case hard:
		return RandomNumber(10, 20);
	default:
		return RandomNumber(1, 5);
	}
}

void screenColor(bool Answer)
{
	if (Answer)
		system("color 2F");
	else
		system("color 4F");
}

void PrintQuizz(stGameInfo GameInfo , stQuizz &Quizz)
{
	Quizz.Number1 = NumberHardness(GameInfo.Level);
	Quizz.Number2 = NumberHardness(GameInfo.Level);
	string Sympol = OpSympol(GameInfo.OpType, Quizz);

	cout << endl;
	cout << Quizz.Number1<<endl;
	cout << Quizz.Number2 << "      " << Sympol <<endl;
	cout << "___________________" << endl;
	
	int PlayerAnswer;
	cin >> PlayerAnswer;

	Quizz.Answer = PlayerAnswer == Quizz.AnswerCollect;

	if (Quizz.Answer)
	{
		cout << endl << "True Answer (-:" << endl;
		Quizz.Right++;
	}

	else
	{
		cout << endl << "Wrong Answer )-:" << endl << "Right Answer Is : " << Quizz.AnswerCollect << endl;
		Quizz.Wrong++;
	}
		screenColor(Quizz.Answer);

}

void PlayGame(stGameInfo GameInfo, stQuizz &Quizz)
{
	for (int Question = 0; Question < GameInfo.NumberOfQuestion; Question++)
	{
		cout << "\nQuestion [" << Question + 1 << "] : \n";
		PrintQuizz(GameInfo , Quizz);
	}
}

void RestScreen()
{
	system("cls");
	system("Color 0F");
}

string LevelName(enLevel Level)
{
	string LevelName[4] = { "Easy" , "Med" , "Hard" , "Mix" };
	return LevelName[Level - 1];
}

string OpTyeName(enOpType OpType)
{
	string OpTyeName[5] = { "Add" , "Sub" , "Mul" , "Div" , "Mix"};
	return OpTyeName[OpType - 1];
}

void FinalScreen(stGameInfo GameInfo, stQuizz Quizz)
{
	cout << "\n_______________________________\n";
	cout << "        Final Result Is ";
	bool IsPassed = Quizz.Right > (GameInfo.NumberOfQuestion/2);
	if (IsPassed)
		cout << "Pass\n";
	else
		cout << "Fail\n";
	screenColor(IsPassed);
	cout << "\n_______________________________\n";
	cout << endl << "Number Of Question : " << GameInfo.NumberOfQuestion << endl;
	cout << endl << "Question Level : " << LevelName(GameInfo.Level) << endl;
	cout << endl << "Operation Type : " << OpTyeName(GameInfo.OpType) << endl;
	cout << endl << "Number Of Right : " << Quizz.Right << endl;
	cout << endl << "Number Of Wrong : " << Quizz.Wrong << endl;
	cout << "__________________________________\n";
}

void StartGame()
{
	string PlayAgain = "Y";
	do
	{
	    stQuizz Quizz;
		RestScreen();
		stGameInfo  GameInfo = CollectStartInfo();
		PlayGame(GameInfo , Quizz);

		FinalScreen(GameInfo, Quizz);

		cout << "Do you Want To play again Y/N : ";
			cin >> PlayAgain;

	} while (PlayAgain == "Y" || PlayAgain == "y");
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();
}
 
