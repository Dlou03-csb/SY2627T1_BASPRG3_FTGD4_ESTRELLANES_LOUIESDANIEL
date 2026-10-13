#include "Enemy.h"
#include "GameScene.h"

Enemy::Enemy(Player* player)
{
	targetPlayer = player;
	x = rand() % (SCREEN_WIDTH - 50);
	y = -50;

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
	sound->volume = 64;

	width = 0;
	height = 0;

	speed = 2;
	directionX = 1;
	directionY = 1;
	directionChangeTime = 120;
	currentDirectionChangeTime = directionChangeTime;

	reloadTime = 60;
	currentReloadTime = 0;

	isExploding = false;
	explodeTime = 20;
	explosion = loadTexture("gfx/explosion.png");

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Enemy::update()
{

	if (isExploding == true)
	{
		explodeTime--;
		return;
	}


	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->GetY() > SCREEN_HEIGHT)
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
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (x < 0 || x > SCREEN_WIDTH - height)
	{
		directionX = -directionX;
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
			targetPlayer->GameObject::GetX(), targetPlayer->GameObject::GetY(), x, y, &bulletDirectionX, &bulletDirectionY
		);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet
		(
			x,
			y + (height / 2) - 5,
			bulletDirectionX,
			bulletDirectionY,
			5,
			Side::ENEMY_SIDE
		);

		getScene()->addGameObject(bullet);
		bullets.push_back(bullet);

		currentReloadTime = reloadTime;
	}
}

void Enemy::explode()
{
	isExploding = true;
}

void Enemy::draw()
{
	if (isExploding == true)
	{
		blit(explosion, x, y);
	}
	else
	{
		blit(texture, x, y);
	}

}



