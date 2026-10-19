#include "GameScene.h"

using namespace std;

GameScene::GameScene()
{

	grid = new Grid();
	this->addGameObject(grid);

	food = new Food();
	this->addGameObject(food);

	player = new Player();
	this->addGameObject(player);

	eatSound = NULL;
	points = 0;
	highScore = 0;
	BG = NULL;

}


void GameScene::start()
{

	Scene::start();

	initFonts();

	BG = loadTexture("gfx/BG.png");

	eatSound = SoundManager::loadSound("sfx/eat.mp3");
	if (eatSound != NULL)
	{
		eatSound->volume = 80;
	}

	points = 0;

	doSpawnLogic();

}

void GameScene::update()
{
	if (player->getIsAlive())
	{
		Scene::update();
		doCollisionLogic();
	}
	else
	{
		if (app.keyboard[SDL_SCANCODE_SPACE])
		{
			restartGame();
		}
	}
}

void GameScene::draw()
{
	blit(BG, 0, 0);

	Scene::draw();

	drawText
	(
		Grid::OFFX, 26,
		0, 0, 0,
		TEXT_LEFT,
		"POINTS: %03d", points
	);

	drawText
	(
		SCREEN_WIDTH - Grid::OFFX, 26,
		0, 0, 0,
		TEXT_RIGHT,
		"HIGH SCORE: %03d", highScore
	);

	if (!player->getIsAlive())
	{

		drawText
		(
			SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 35,
			255, 80, 80,
			TEXT_CENTER,
			"GAME OVER"
		);

		drawText
		(
			SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 15,
			255, 255, 255,
			TEXT_CENTER,
			"PRESS SPACE TO RESTART"
		);
	}
}


void GameScene::doSpawnLogic()
{

	vector<SDL_Point> freeTiles;

	for (int row = 0; row < Grid::ROW; row++)
	{
		for (int col = 0; col < Grid::COL; col++)
		{
			if (!player->isOccupyingTile(col, row))
			{
				freeTiles.push_back({ col, row });
			}
		}
	}


	if (!freeTiles.empty())
	{
		int randomIndex = rand() % freeTiles.size();
		int pixelX = Grid::OFFX + (freeTiles[randomIndex].x * Grid::TILE_SIZE);
		int pixelY = Grid::OFFY + (freeTiles[randomIndex].y * Grid::TILE_SIZE);

		food->spawnAt(pixelX, pixelY);
	}
}

void GameScene::doCollisionLogic()
{

	if (player->checkWallCollision())
	{
		player->doDeath();
		return;
	}

	if (player->checkSelfCollision())
	{
		player->doDeath();
		return;
	}

	int collision = checkCollision
	(
		player->getX(), player->getY(), player->getW(), player->getH(),
		food->getX(), food->getY(), food->getW(), food->getH()
	);

	if (collision == 1)
	{
		SoundManager::playSound(eatSound);
		points++;

		if (points > highScore)
		{
			highScore = points;
		}

		player->grow();
		doSpawnLogic();
	}
}

void GameScene::restartGame()
{
	points = 0;
	player->reset();
	doSpawnLogic();
}
