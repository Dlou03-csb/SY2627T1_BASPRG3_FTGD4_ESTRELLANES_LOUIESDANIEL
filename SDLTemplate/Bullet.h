#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

enum class Side
{
	PLAYER_SIDE,
	ENEMY_SIDE
};

class Bullet : public GameObject
{
public:
	Bullet(int positionX, int positionY, float directionX, float directionY, int speed, Side side);
	void start() override;
	void update() override;
	void draw() override;
	Side GetSide();

private:

	SDL_Texture* texture;
	SDL_Texture* texture2;
	int speed;

	float directionX;
	float directionY;

	Side side;
};
