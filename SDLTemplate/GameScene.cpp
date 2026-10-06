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

	background = loadTexture("gfx/background.png");

	initFonts();
	points = 0;

	spawnTime = 120;
	currentSpawnTime = spawnTime;

}

void GameScene::draw()
{
	int bgWidth;
	int bgHeight;

	blitScale(background, 0, 0, &bgWidth, &bgHeight, 3);

	Scene::draw();

	drawText
	(
		110, 20,
		255, 255, 255,
		TEXT_CENTER,
		"POINTS: %03d" , points
	);

	if (!player->GetIsAlive())
	{
		drawText
		(
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
			255, 255, 255,
			TEXT_CENTER,
			"GAME OVER"
		);
	}
}

void GameScene::update()
{
	Scene::update();

	DoSpawnLogic();
	DoCollisionLogic();

	for (int i = enemies.size() - 1; i >= 0; i--)
	{
		if (enemies[i]->isExploding && enemies[i]->explodeTime <= 0)
		{
			DeSpawnEnemy(enemies[i]);
		}

	}

}


void GameScene::DoSpawnLogic()
{

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

void GameScene::DoCollisionLogic()
{

	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);
		if (bullet != NULL)
		{
			if (bullet->GetSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision
				(
					bullet->GetX(), bullet->GetY(), bullet->GetWidth(), bullet->GetHeight(),
					player->GetX(), player->GetY(), player->GetWidth(), player->GetHeight()

				);

				if (collision == 1)
				{
					std::cout << "Damn you!" << std::endl;
					player->DoDeath();
					break;
				}
			}
			else if (bullet->GetSide() == Side:: PLAYER_SIDE)
			{
				for (int i = 0; i < enemies.size(); i++)
				{
					Enemy* enemy = enemies[i];

					if (enemy->isExploding) continue;

					int collision = checkCollision
					(
						bullet->GetX(), bullet->GetY(), bullet->GetWidth(), bullet->GetHeight(),
						enemy->GetX(), enemy->GetY(), enemy->GetWidth(), enemy->GetHeight()

					);

					if (collision == 1)
					{
						std::cout << "Mongrel Hit" << std::endl;
						enemy->explode();
						points++;
						break;
					}

				}
			}
		}
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

void GameScene::DeSpawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemy == enemies[i])
		{
			index = i;
			break;
		}
	}

	if (index >= 0)
	{
		enemies.erase(enemies.begin() + index);
		delete enemy;
	}


}