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
	Bullet(int positionX, int positionY, float directionX, float directionY, int speed, Side side, int bulletTexture = 0);
	void start() override;
	void update() override;
	void draw() override;
	Side GetSide();

private:

	SDL_Texture* texture;
	int speed;
	int bulletTexture;

	float directionX;
	float directionY;

	Side side;
};
