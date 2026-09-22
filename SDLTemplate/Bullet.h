#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Bullet : public GameObject
{
public:
	Bullet(int positionX, int positionY, float directionX, float directionY, int speed);
	void start() override;
	void update() override;
	void draw() override;
	int GetX();
	int GetY();

private:
	int x;
	int y;
	int width;
	int height;
	SDL_Texture* texture;
	SDL_Texture* texture2;
	int speed;

	float directionX;
	float directionY;
};
