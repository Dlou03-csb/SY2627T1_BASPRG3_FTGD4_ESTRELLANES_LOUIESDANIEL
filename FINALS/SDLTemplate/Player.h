#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "util.h"
#include "Grid.h"
#include <vector>

using namespace std;

struct SnakePart
{
	int x;
	int y;
};

class Player : 
	public GameObject
{

public:

	Player();

	void start() override;
	void update() override;
	void draw() override;

	void grow();
	void doDeath();
	void reset();
	bool getIsAlive();

	bool checkWallCollision();
	bool checkSelfCollision();
	bool isOccupyingTile(int tileX, int tileY);

private:

	void move();
	double getPartsAngle(int index);

	SDL_Texture* headTexture;
	SDL_Texture* bodyTexture;
	SDL_Texture* tailTexture;

	vector<SnakePart> parts;

	int dirX;
	int dirY;
	int nextDirX;
	int nextDirY;

	int moveDelay;
	int moveTimer;

	bool isAlive;
	bool shouldGrow;
};