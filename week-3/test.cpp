#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
/*--------------------------- local variables ------------------------------*/

	int ball[80][23];
	void gotoxy(int, int);
	int noOfCoords = 0;
	int origX;
	int origY;
	char mov1;
	char mov2;
	int x;
	int y;

/*----------------------------- user prompt --------------------------------*/

	cout << "Enter the X coordinate for the ball (between 0 and 79): ";
	cin >> origX;
	cout << endl;
	cout << "Enter the Y coordinate for the ball (between 0 and 22): ";
	cin >> origY;
	cout << endl;
	cout << "Would you like the ball to move [u]p or [d]own? ";
	cin >> mov1;
	cout << endl;
	cout << "would you like the ball to move [l]eft or [r]ight? ";
	cin >> mov2;
	cout << endl;

	system("CLS");					//clear the screen

	x = origX;					//make x and y equal the original entries	
	y = origY;

	//initialize the ball array's elements to 0
	for(int row = 0; row < 79; row++)
	{
		for(int col = 0; col < 22; col++)
			ball[row][col] = 0;
	}
	
	gotoxy(x, y);					//go to the coordinate	
	printf("O");					//print O at the coordinate	

	//change the ball element to 1 if not 0 and increase the counter
	if (ball[x][y] == 0)
	{
		ball[x][y] = 1;
		noOfCoords++;
	}//endif
	

/*------------------------- move the ball once -----------------------------*/

	if (mov1 == 'u')
	{
		if (y > 0)
		{
			y--;
		}//endif
		else
		{
			mov1 = 'd';
		}//endif
	}//endif

	if (mov1 == 'd') 
	{
		if (y < 22)
		{
			y++;
		}//endif
		else
		{
			mov1 = 'u';
		}//endif
	}//endif

	if (mov2 == 'r') 
	{
		if (x < 79)
		{
			x++;
		}//endif
		else
		{
			mov2 = 'l';
		}//endif
	}//endif

	if (mov2 == 'l') 
	{
		if (x > 0)
		{
			x--;
		}//endif
		else
		{
			mov2 = 'r';
		}//endif
	}//endif

	gotoxy(x, y);					//go to coordinate
	printf("O");					//print O at the coordinate

	//change the ball element to 1 if not 0 and increase the counter
	if (ball[x][y] == 0)
	{
		ball[x][y] = 1;
		noOfCoords++;
	}//endif
	
/*------------------------ ALGORITHM to move ball ---------------------------*/

	//while the coordinates are not the same as entered
	while ((x != origX) || (y != origY))
	{
		//move the ball in the correct direction
		if (mov1 == 'u')
		{
			if (y > 0) 
			{
				y--;
			}//endif
			else 
			{
				mov1 = 'd';
			}//endif
		}//endif


		if (mov1 == 'd') 
		{
			if (y < 22) 
			{
				y++;
			}//endif
			else 
			{
				mov1 = 'u';
			}//endif
		}//endif

		if (mov2 == 'r') 
		{
			if (x < 79) 
			{
				x++;
			}//endif
			else 
			{
				mov2 = 'l';
			}//endif
		}//endif

		if (mov2 == 'l') 
		{
			if (x > 0) 
			{
				x--;
			}//endif
			else 
			{
				mov2 = 'r';
			}//endif
		}//endif

		gotoxy(x, y);
		printf("O");

		if (ball[x][y] == 0)
		{
			ball[x][y] = 1;
			noOfCoords++;
		}//endif
		
		
		system("CLS"); 		
	}//endwhile

	//output the number of coordinates the O passed through
	cout << endl;
	cout << "The ball crossed " << noOfCoords << " unique coordinates.";
	cout << endl;

	system("PAUSE");

	return 0;
}//endmain

//gotoxy definition
void gotoxy(int eex, int eey)
{
	COORD coord;
	coord.X = eex;
	coord.Y = eey;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}//endgotoxy 