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
	void upgrade();
	void deleteBullet(Bullet* bulletToDelete);
	bool GetIsAlive();

	int level;


private:

	SDL_Texture* texture;
	int speed;

	Mix_Chunk* sound;

	int speedBoost;
	int defaultSpeed;
	int powerUpTimer;
	int maxPowerUpTime;

	float reloadTime;
	float currentReloadTime;
	float wingRT;
	float currentWingRT;

	bool isAlive;

	std::vector<Bullet*> bullets;
};