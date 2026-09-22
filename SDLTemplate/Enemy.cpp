#include "Enemy.h"
#include "GameScene.h"

Enemy::Enemy(Player* player)
{
	targetPlayer = player;
	x = SCREEN_WIDTH + (rand() % 200);
	y = rand() % SCREEN_HEIGHT;

}

Enemy::~Enemy()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
}

void Enemy::start()
{
	texture = loadTexture("gfx/enemy.png");
	sound = SoundManager::loadSound("sound/enemyShot.ogg");

	width = 0;
	height = 0;

	speed = 2;
	directionX = -1;
	directionY = 1;
	directionChangeTime = 120;
	currentDirectionChangeTime = directionChangeTime;

	reloadTime = 60;
	currentReloadTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Enemy::update()
{

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->GetX() < 0)
		{
			Bullet* bulletToDelete = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToDelete;

			break;
		}
	}


	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--;
	}
	else
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	x += directionX * speed;
	y += directionY * speed;

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}
	else
	{

		float bulletDirectionX;
		float bulletDirectionY;

		calcSlope(
			targetPlayer->GetX(), targetPlayer->GetY(), x, y, &bulletDirectionX, &bulletDirectionY
		);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet
		(
			x, 
			y + (height / 2) - 5, 
			bulletDirectionX, 
			bulletDirectionY, 
			5
		);

		getScene()->addGameObject(bullet);
		bullets.push_back(bullet);

		currentReloadTime = reloadTime;
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

