#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "draw.h"

class Boss : public GameObject
{
public:
	Boss(Player* targetPlayer);
	void start() override;
	void update() override;
	void draw() override;

	void takeDamage();
	bool isDead();
	bool isExploding;
	int explodeTime;

private:
	SDL_Texture* texture;
	Player* player;

	int hp;
	int pattern;
	int patternTimer;
	int maxPatternTime;

	float reloadTime;
	float currentReloadTime;

	float speedX;
	float speedY;

	void PatternOne();
	void PatternTwo();

};