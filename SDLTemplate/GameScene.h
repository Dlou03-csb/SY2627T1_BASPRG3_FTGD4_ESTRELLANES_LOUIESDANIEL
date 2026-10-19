#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "powerUP.h"
#include "Boss.h"

class GameScene : public Scene
{
public:

	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();

private:
	void spawnEnemy(int count);
	void DeSpawnEnemy(Enemy* enemy);

	void DoSpawnLogic();
	void DoCollisionLogic();

	Player* player;
	Boss* boss;

	int points;
	int bossPointSpawn;
	float currentSpawnTime;
	float spawnTime;
	float powerUpSpawnTime;
	float currentPowerUpSpawnTime;

	bool isBossFight;

	std::vector<Enemy*> enemies;
	std::vector<powerUP*> powerups;

	SDL_Texture* background;

};

