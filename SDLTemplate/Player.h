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
	void DoDeath();
	bool GetIsAlive();


private:

	SDL_Texture* texture;
	int speed;

	Mix_Chunk* sound;

	int speedBoost;
	int defaultSpeed;

	float reloadTime;
	float currentReloadTime;
	float wingRT;
	float currentWingRT;

	bool isAlive;

	std::vector<Bullet*> bullets;
};