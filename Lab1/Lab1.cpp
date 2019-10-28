#include "pch.h"
#include "space.h"
#include <iostream>

using namespace std;

int main()
{
	int const x = 11, y = 11, ballsCount = 16, pocketsCount = 6;

	// pockets generating
	Pocket pockets[pocketsCount];
	pockets[0] = Pocket(0, 0);
	pockets[1] = Pocket(0, (y - 1) / 2);
	pockets[2] = Pocket(0, y - 1);
	pockets[3] = Pocket(x - 1, 0);
	pockets[4] = Pocket(x - 1, (y - 1) / 2);
	pockets[5] = Pocket(x - 1, y - 1);

	// balls generating
	Ball balls[ballsCount];
	for (int i = 0; i < ballsCount; i++)
		balls[i].SetUniqueCoords(balls, ballsCount, x, y);

	// game starting
	bool isBallsVisible = true;
	while (isBallsVisible)
	{
		// billiard table creation
		for (int i = 0; i < y + 2; i++)
		{
			for (int j = 0; j < x + 2; j++)
			{
				// pockets creation
				bool isPocketPosition = false;
				for (int k = 0; k < pocketsCount; k++)
				{
					Pocket & curPocket = pockets[k];
					if (curPocket.GetX() == j - 2 &&
						curPocket.GetY() == i - 2)
					{
						cout << "\xfe";
						isPocketPosition = true;
						break;
					}
				}

				if (isPocketPosition)
					continue;

				// balls creation
				bool isBallPosition = false;
				for (int k = 0; k < ballsCount; k++)
				{
					Ball & curBall = balls[k];
					if (curBall.IsVisible() &&
						curBall.GetX() == j - 2 &&
						curBall.GetY() == i - 2)
					{
						cout << "O";
						isBallPosition = true;
						break;
					}
				}

				if (isBallPosition)
					continue;

				// table creation
				if ((i == 0 || i == 1) && (j == 0 || j == 1))
					cout << " ";

				// column number
				else if (i == 0)
					if ((j - 2) / 10 == 0)
						cout << " ";
					else
						cout << (j - 2) / 10;

				else if (i == 1)
					cout << (j - 2) % 10;

				// row number
				else if (j == 0)
					if ((i - 2) / 10 == 0)
						cout << " ";
					else
						cout << (i - 2) / 10;

				else if (j == 1)
					cout << (i - 2) % 10;

				// table borders
				else
				{
					if ((j == 2 || j == x + 1) && i != 2 && i != y + 1 && i != (y + 1) / 2 + 1)
						cout << "|";
					else
						if (i == 2 || i == y + 1)
							cout << "-";
						else
							cout << " ";
				}
			}
			cout << "\n";
		}

		int ballRow, ballCol, dirRow, dirCol = 0;

		cout << "Enter the ball coordinates (row and column): \n";
		cin >> ballRow;
		cin >> ballCol;

		cout << "Enter the direction point to strike (row and column): \n";
		cin >> dirRow;
		cin >> dirCol;

		Cue().CheckDirection(Position((int)ballCol, (int)ballRow), Position((int)dirCol, (int)dirRow),
			balls, pockets,
			ballsCount, pocketsCount,
			x, y);

		isBallsVisible = false;
		for (int i = 0; i < ballsCount; i++)
			if (balls[i].IsVisible())
			{
				isBallsVisible = true;
				break;
			}
	}

	cout << "All balls were pocketed!\n";
}