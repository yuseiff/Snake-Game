#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
using namespace std;

void Setup();
//---------------------Properties-----------------------//
enum enDirection { Top = 1, Down, Right, Left };

struct Map
{
	int Height, width, fruitX, fruitY;
};

struct Snake
{
	int HeadX, HeadY, Tail_N, Tail_X[50], Tail_Y[50];
	char Dir;
	bool Tail_P;
};

struct Player
{
	int score;
	int HighScore;
	bool lose;
};

Map Map1;
Snake Snake1;
Player Player1;
//------------------------------------------------------//

//_____________________Menu____________________________//
enum EnMenu { Play = 1, SnakeColor = 2, Exit = 3 };
enum Encolor {Red=1 ,Green, Blue,White};

unsigned short Input;
bool GameQuit = false;
bool GamePlay = false;

string SnakeColorCode = "\u001b[32m"; //Green
string FruitColorCode = "\u001b[35m"; //Magenta
string MapColorCode = "\u001b[37m"; //White

void MenuOp();
void MenuShow();


void Snakecolor()
{
	SnakeColorCode = "\u001b[32m";
	unsigned short Color;
	void Setup();
	system("cls");
	system("color 06");

	for (int i = 0; i <= 20; i++)
	{
		cout << "*";
	}

	cout<< endl
		<< "1)Red" << endl
		<< "2)Green" << endl
		<< "3)Blue" << endl
		<< "4)White" << endl;

	for (int i = 0; i <= 20; i++)
	{
		cout << "*";
	}

	cout << endl
		 << "Choice the color of the snake ";
	cin >> Color;

	//Snake color operation

	if (Color == (unsigned short)Encolor::Red)
	{
		SnakeColorCode = "\u001b[31m";
	}

	else if (Color == (unsigned short)Encolor::Green)
	{
		SnakeColorCode = "\u001b[32m";
	}

	else if (Color == (unsigned short)Encolor::Blue)
	{
		SnakeColorCode = "\u001b[34m";
	}

	else if (Color == (unsigned short)Encolor::White)
	{
		SnakeColorCode = "\u001b[37m";
	}

	else
	{
		SnakeColorCode = "\u001b[32m";
	}
}
void MenuOp()
{
	if (Input == (unsigned short)EnMenu::Play)
	{
		GamePlay = true;
	}

	else if (Input == (unsigned short)EnMenu::Exit)
	{
		GamePlay = false;
		GameQuit = true;

	}

	else if (Input == (unsigned short)EnMenu::SnakeColor)
	{
		Snakecolor();
	}

	else
	{

		MenuShow();
	}
}
void MenuShow()
{
	void Setup();
	system("cls");
	system("color 02");
	
	if (Player1.score > 0)
	{
		cout << "Player score: " << Player1.score << endl;
		cout << "Best Score: " << Player1.HighScore << endl;
	}
	
	for (int i = 0; i <= 20; i++)
	{
		cout << "*";
	}

	cout << endl
		<< "1)Play" << endl
		<< "2)Change snake color" << endl
		<< "3)Exit" << endl;

	for (int i = 0; i <= 20; i++)
	{
		cout << "*";
	}


	cout << endl
		<< "Enter Your Choice ";

	cin >> Input;
	MenuOp();
}
//------------------------------------------------------//

void Shift_Right(int arr[], int size)
{
	for (int i = size - 2; i >= 0; i--)
	{
		arr[i + 1] = arr[i];
	}
}

void Line()
{
	for (int i = 0; i <= 40; i++)
	{
		cout << "*";
	}
	//cout << endl;
}

void GenerateFruit()
{
	srand(time(NULL));
	Map1.fruitX = rand() % (Map1.width - 2) + 1;//1 to 38
	Map1.fruitY = rand() % (Map1.Height - 2) + 1;//1 to 18
}

void Setup()
{

	Map1.width= 40;
	Map1.Height = 20;
	GenerateFruit();
	//-----------------------------------------------------------//

	Snake1.HeadX = Map1.width / 2;
	Snake1.HeadY = Map1.Height / 2;
	Snake1.Tail_N = 0;

	//------------------------------------------------------------//
	Player1.score = 0;
	Player1.lose = false;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < Map1.Height; i++)
	{
		for (int j = 0; j < Map1.width; j++)
		{
			if (i == 0 || i == Map1.Height - 1)
			{
				cout << MapColorCode <<"*"<< FruitColorCode;
			}

			else if (j == 0 || j == Map1.width - 1)
			{
				cout << MapColorCode << "*" << FruitColorCode;
			}

			else if (i == Snake1.HeadY && j == Snake1.HeadX)
			{
				cout <<SnakeColorCode<< "O" << FruitColorCode;
			}

			else if (i == Map1.fruitY && j == Map1.fruitX)
			{
				cout <<"$";
			}

			else
			{

				Snake1.Tail_P = false;
				for (int z = 0; z < Snake1.Tail_N; z++)
				{

					if (Snake1.Tail_X[z] == j && Snake1.Tail_Y[z] == i)
					{
						cout << SnakeColorCode << "o" << FruitColorCode;
						Snake1.Tail_P = true;
						break;
					}
				}

				if (!Snake1.Tail_P)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	cout << MapColorCode <<"Player score: " << Player1.score << FruitColorCode <<endl;
}

void GameInput()
{
	if (_kbhit())
	{
		char c = _getch();
		switch (c)
		{
		case'w':
			Snake1.Dir = Top;
			break;

		case 'a':
			Snake1.Dir = Left;
			break;

		case'd':
			Snake1.Dir = Right;
			break;

		case 's':
			Snake1.Dir = Down;
			break;

		case 'x':
			cout << "\u001b[32m";
			GamePlay = false;
			break;
		}
	}
}

void GameOver()
{
	system("cls");

	Line();
	cout << "\tGame over\t";
	Line();
	cout << endl;

	system("color 4F");
	cout << "Your Score Is " << Player1.score;
	cout << endl << endl;
	Player1.lose = true;
}

void Move()
{
	Shift_Right(Snake1.Tail_X, 50);
	Shift_Right(Snake1.Tail_Y, 50);
	Snake1.Tail_X[0] = Snake1.HeadX;
	Snake1.Tail_Y[0] = Snake1.HeadY;


	switch (Snake1.Dir)
	{
	case Top:
		Snake1.HeadY--;
		break;

	case Down:
		Snake1.HeadY++;
		break;

	case Left:
		Snake1.HeadX--;
		break;

	case Right:
		Snake1.HeadX++;
		break;
	}

	if (Snake1.HeadX == 0 || Snake1.HeadX == Map1.width)
	{
		GameOver();
	}

	else if (Snake1.HeadY == 0 || Snake1.HeadY == Map1.Height)
	{
		GameOver();
	}

	if (Snake1.HeadX == Map1.fruitX && Snake1.HeadY == Map1.fruitY)
	{
		GenerateFruit();
		Player1.score = Player1.score + 1;

		if (Player1.score > Player1.HighScore)
		{
			Player1.HighScore = Player1.score;
		}

		Snake1.Tail_N++;
	}

	for (int y = Snake1.Tail_N; y >= 3; y--)
	{

		if (Snake1.HeadX == Snake1.Tail_X[y] && Snake1.HeadY == Snake1.Tail_Y[y])
		{
			GameOver();
		}
	}
}





int main()
{

	while (GameQuit == false)
	{
		cout << "\u001b[32m";
		system("pause");
		MenuShow();

		if (GamePlay == true)
		{
			system("Pasue");

			system("color 0a");
			Setup();
			while (Player1.lose == false)
			{
				Draw();
				GameInput();
				Move();
				Sleep(80);
				if (GamePlay == false)
				{
					break;
				}
			}
		}
		if (GameQuit == true)
		{
			break;
		}
	}
}