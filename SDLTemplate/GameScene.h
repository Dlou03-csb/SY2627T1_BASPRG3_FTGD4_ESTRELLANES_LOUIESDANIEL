#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"

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

	int points;
	float currentSpawnTime;
	float spawnTime;

	std::vector<Enemy*> enemies;

};

