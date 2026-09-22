#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

class Player : public GameObject
{
public:
	~Player();
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
	int speed;

	Mix_Chunk* sound;

	int speedBoost;
	int defaultSpeed;

	float reloadTime;
	float currentReloadTime;
	float wingRT;
	float currentWingRT;

	std::vector<Bullet*> bullets;
};