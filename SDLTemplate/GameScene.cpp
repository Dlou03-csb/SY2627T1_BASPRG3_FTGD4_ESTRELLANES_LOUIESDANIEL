#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);
	
}

GameScene::~GameScene()
{

	delete player;

}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	spawnTime = 120;
	currentSpawnTime = spawnTime;

}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

	if (currentSpawnTime > 0)
	{
		currentSpawnTime--;
	}
	else
	{
		spawnEnemy(2);
		currentSpawnTime = spawnTime;
	}

}

void GameScene::spawnEnemy(int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy* enemy = new Enemy(player);
		this->addGameObject(enemy);
		enemies.push_back(enemy);
	}

}
