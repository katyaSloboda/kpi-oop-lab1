#include "pch.h"
#include "space.h"
#include <iostream>

using namespace std;

void Ball::Show()
{
	Visible = true;
}

void Ball::Blind()
{
	Visible = false;
}

void Ball::Jump(int Next1, int Next2)
{
	Init(Next1, Next2);
}

void Ball::SetUniqueCoords(Ball balls[], int ballsCount, int x, int y)
{
	bool isUnique = false;
	while (!isUnique)
	{
		int coord1 = 1 + rand() % (x - 2);
		int coord2 = 1 + rand() % (y - 2);

		isUnique = true;
		for (int j = 0; j < ballsCount; j++)
			if (balls[j].IsVisible() &&
				balls[j].GetX() == coord1 &&
				balls[j].GetY() == coord2)
			{
				isUnique = false;
				break;
			}

		if (isUnique)
			Jump(coord1, coord2);
	}
}

void Cue::CheckDirection(Position ballPos, Position dirPos,
	Ball balls[], Pocket pockets[],
	int ballsCount, int pocketsCount,
	int x, int y)
{
	// check ball position
	bool isBallExist = false;
	int ballNum = -1;
	for (int i = 0; i < ballsCount; i++)
		if (ballPos == balls[i])
		{
			isBallExist = true;
			ballNum = i;
			break;
		}

	if (!isBallExist)
		return;

	// check probability
	int ballHitProbability = rand() % 2;
	if (ballHitProbability == 0)
		return;

	// check direction
	bool isBallHit = false;
	for (int i = 0; i < pocketsCount; i++)
		if (dirPos == pockets[i])
		{
			isBallHit = true;
			break;
		}

	if (isBallHit)
		balls[ballNum].Blind();
	else
		balls[ballNum].SetUniqueCoords(balls, ballsCount, x, y);
}