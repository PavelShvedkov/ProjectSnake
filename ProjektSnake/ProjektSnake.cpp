#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Array.h"
#include "Snake.h"

using namespace std;

//\xc9-левый верхний угол \xbb-правый верхний угол \xcd-горизонтальна€ \xba-вертикальна€
//\xc8-левый нижний угол \xbc-правый нижний угол \xcb-верхнее "т" \xca-нижнее "т" \xce-"крест"

//рисует текущий кадр пол€ с объктами
void drawWindow(Array,Array,Array);
//задаЄт координаты "€блока" в текущий момент времени
void setApple(Array&,Array);
//задаЄт направление движени€ "змейки" в соответсвии с нажатием клавиши
void setDirektionSnake(Array&);
//задаЄт координаты "змейки" в соответсвии с направлением
void movementSnake(Array&,Array,bool&);
//провер€ет координаты объекта на принадлежность полю
bool areaControl(Array, Array);
void logic();

int main()
{
	srand(time(NULL));
	Array sizeWindow(2);
	sizeWindow[0] = 40;
	sizeWindow[1] = 20;

	Array fruitCoords(2);
	fruitCoords[0] = 2;
	fruitCoords[1] = 3;

	Array snakeCoords(4);
	snakeCoords[0] = 3;
	snakeCoords[1] = 4;
	snakeCoords[2] = 0;

	bool marker = true;
	
	Snake snake();

	while (marker)
	{
		if (snakeCoords[0]== fruitCoords[0]&& snakeCoords[1] == fruitCoords[1])
		{
			setApple(fruitCoords, sizeWindow);
		}
		setDirektionSnake(snakeCoords);
		movementSnake(snakeCoords, sizeWindow, marker);
		drawWindow(sizeWindow, fruitCoords, snakeCoords);
		Sleep(50);
	}
}

void drawWindow(Array sizeWindow, Array fruitCoords, Array snakeCoords)
{
	system("cls");
	cout << "\xc9";
	for (int i = 0; i < sizeWindow[0]; i++)
	{
		cout << "\xcd";
	}
	cout << "\xbb" << endl;

	for (int i = 1; i < sizeWindow[1]; i++)
	{
		cout << "\xba";
		for (int j = 0; j < sizeWindow[0]; j++)
		{
			if (j==fruitCoords[0]&&i==fruitCoords[1])
			{
				cout << "@";
			}
			else if (j==snakeCoords[0]&&i==snakeCoords[1])
			{
				cout << "#";
			}
			else
			{
				cout << " ";
			}
		}
		cout << "\xba" << endl;
	}

	cout << "\xc8";
	for (int i = 0; i < sizeWindow[0]; i++)
	{
		cout << "\xcd";
	}
	cout << "\xbc" << endl;
}

void setApple(Array& fruitCoords, Array sizeWindow)
{
	fruitCoords[0] = rand() % sizeWindow[0]+2;
	fruitCoords[1] = rand() % sizeWindow[1]+2;

	if (!areaControl(fruitCoords,sizeWindow))
	{
		setApple(fruitCoords, sizeWindow);
	}
}

void setDirektionSnake(Array& snakeCoords)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			snakeCoords[2] = 'l';
			break;
		case 'd':
			snakeCoords[2] = 'r';
			break;
		case 'w':
			snakeCoords[2] = 'u';
			break;
		case 's':
			snakeCoords[2] = 'd';
			break;
		}
	}
}

void movementSnake(Array& snakeCoords, Array windowSize, bool& loseMarker)
{
	switch (snakeCoords[2])
	{
	case 'l':
		for (int i = 0; i < length; i++)
		{
			snakeCoords[0]--;
		}
		break;
	case 'r':
		snakeCoords[0]++;
		break;
	case 'u':
		snakeCoords[1]--;
		break;
	case 'd':
		snakeCoords[1]++;
		break;
	}

	if (!areaControl(snakeCoords, windowSize))
	{
		loseMarker = false;
	}
}

bool areaControl(Array coords, Array sizeWindow)
{
	int differenceX = abs(sizeWindow[0] - coords[0]), differenceY = abs(sizeWindow[1] - coords[1]);

	if (differenceX<sizeWindow[0]&&differenceY<sizeWindow[1])
	{
		if (differenceX>1&& differenceY>1)
		{
			return true;
		}
	}

	return false;
}

void logic()
{

}