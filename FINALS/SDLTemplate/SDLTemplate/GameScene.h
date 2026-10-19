#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Food.h"
#include "text.h"
#include "util.h"
#include "Grid.h"
#include "SoundManager.h"
#include <vector>

class GameScene : public Scene
{

public:

	GameScene();

	void start() override;
	void draw() override;
	void update() override;

private:

	void doSpawnLogic();
	void doCollisionLogic();
	void restartGame();



	Player* player;
	Food* food;
	Mix_Chunk* eatSound;
	Grid* grid;
	SDL_Texture* BG;

	int points;
	int highScore;

};