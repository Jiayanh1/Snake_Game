#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver; 
const int width = 30; // boader
const int height = 20; // boader
int x, y, fruitX, fruitY, m, n, score; // x, y are the head
int tailX[100], tailY[100]; // index of tails
int bombX[30], bombY[30];
int nTail, nBomb; // length of the tail
int counter;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void SetUp()
{
	gameOver = false;
	dir = STOP;
	x = width / 2; 
	y = height / 2; //start at the center
	m = rand() % width;
	n = rand() % height; // bomb appears randomely on the map
	bombX[0] = m;
	bombY[0] = n;
	fruitX = rand() % width;
	fruitY = rand() % height; // fruit appears radomly on the map
	score = 0;
	nBomb = 1;
	counter = 1;
	nTail = 0;
}

void Input() {
	if (_kbhit()) // check if the keyboard is being pressed -> true (yes), false(no)
	{
		switch (_getch()) // return the ascii value of the key being pressed
		{
		case'a':
				dir = LEFT;
				break;
		case'd': 
				dir = RIGHT;
				break;
		case's':
				dir = DOWN;
				break;
		case'w':
				dir = UP;
				break;
		case'x':
				gameOver = true;
				break;
		}
	}
}

void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i]; // current position
		prev2Y = tailY[i];
		tailX[i] = prevX; 
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0) // game terminate when head hits the boader 
		gameOver = true;
	for (int i = 0; i < nTail; i++)//when the head eat its tail
	{
		if (x == tailX[i] && y == tailY[i])
			gameOver = true;
	}

	if (x == fruitX && y == fruitY) // when the head eat the fruit
	{
		nTail++; // increase tail numbers
		score += 10;
		fruitX = rand() % width; // fruit randomly placed on the map
		fruitY = rand() % height;

		//place bomb everywhere
		m = rand() % width;
		n = rand() % height;
		if (m == fruitX && n == fruitY)// bomb != fruit
		{
			m = rand() % width;
			n = rand() % height;
		}
		nBomb++;
		bombX[counter] = m; 
		bombY[counter] = n;
		counter++;
	}

	for (int i = 0; i < nBomb; i++) //when head eat a bomb
	{
		if (x == bombX[i] && y == bombY[i])
		{
			nTail = nTail + 2;
			score -= 5;
		}
	}
}

void Winning()
{
	//Displaying new screen
	const int newWidth = 20;
	const int newHeight = 3;

	cout << endl;
	for (int i = 0; i < newWidth+1; i++) // top line
		cout << "#";
	cout << endl;
	for (int i = 0; i < newHeight; i++)
	{
		for (int j = 0; j <= newWidth; j++)
		{
			if (i == (newHeight / 2))
			{
				cout << "     YOU WON!!     ";
				break;
			}
			if (j == 0 || j == newWidth)
				cout << "#";
			else
				cout << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < newWidth +1; i++) // bottum line
		cout << "#"; 
	gameOver = true;
}

void Draw()
{
	// Draw the boader
	system("cls"); // clear the screen

	for (int i = 0; i < width+2; i++)//top wall
		cout << "-";
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width+2; j++)
		{
			bool printed = false;

			if (j == 0 || (j == width))
				cout << "|";

			if (i == y && j == x)
			{
				cout << "@";
				printed = true;
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "*"; // fruit
				printed = true;
			}
			else
			{
				//going through evey element and draw it
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						printed = true;
					}
				}
			}

			if(printed == false)
			{
				for (int k = 0; k < nBomb; k++)
				{
					if (bombX[k] == j && bombY[k] == i)
					{
						cout << "B";
						printed = true;
					}
				}
			}

			if (printed == false)
				cout << " ";	
		}
		cout << endl;
	}
	for (int i = 0; i < width+2; i++) // bottom wall
		cout << "-";
	cout << "\nScore: " << score << "\nRules: ";
	cout << "\n1. Eatting a fruit(*) + 10 points to score";
	cout << "\n2. Eating a bomb(B) - 5 points and add 2 tails";
	cout << "\n3. Eating a tail or hitting the boarder will die ";
	cout << "\n      YOU WIN WHEN YOU HIT 100 PTS !!			";
}

int main() {
	SetUp();
	while (!gameOver)
	{
		Draw();
		if (score > 100)
		{
			Winning();
		}
		Input();
		Logic();
		Sleep(10);
		
	}
	return 0;
}
