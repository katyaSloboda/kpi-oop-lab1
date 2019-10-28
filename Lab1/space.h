#ifndef __SPACE_H
#define __SPACE_H

class Position
{
public:
	int X, Y;

	explicit Position(int Coord1 = 0, int Coord2 = 0) { X = Coord1; Y = Coord2; }
	virtual ~Position() { }
	void Init(int Coord1, int Coord2) { X = Coord1; Y = Coord2; }
	int GetX() { return X; }
	int GetY() { return Y; }

	bool operator==(Position& other) { return X == other.GetX() && Y == other.GetY(); }
};

class Ball : public Position
{
public:
	bool Visible;

	Ball() : Position(), Visible(true) { }
	Ball(int Coord1, int Coord2) : Position(Coord1, Coord2), Visible(true) { };
	virtual ~Ball() { }

	bool IsVisible() { return Visible; }
	virtual void Show();
	virtual void Blind();
	virtual void Jump(int Next1, int Next2);
	virtual void SetUniqueCoords(Ball balls[], int ballsCount, int x, int y);
};

class Pocket : public Position
{
public:
	explicit Pocket(int Coord1 = 0, int Coord2 = 0) : Position(Coord1, Coord2) { }
	virtual ~Pocket() { }
};

class Cue
{
public:
	Cue() {};
	virtual ~Cue() {};
	virtual void CheckDirection(Position ballPos, Position dirPos,
		Ball balls[], Pocket pockets[],
		int ballsCount, int pocketsCount,
		int x, int y);
};

#endif //__SPACE_H