#include "Boss.h"
#include "GameScene.h"

Boss::Boss(Player* targetPlayer)
{
	player = targetPlayer;
}

void Boss::start()
{

	texture = loadTexture("gfx/enemy.png");
	width = 0;
	height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	int hitboxWidth = width * 2;
	int hitboxHeight = height * 2;

	width = hitboxWidth;
	height = hitboxHeight;

	x = (SCREEN_WIDTH / 2) - (width / 2);
	y = 50;

	hp = 50;
	isExploding = false;
	explodeTime = 0;

	pattern = 1;
	maxPatternTime = 300;
	patternTimer = maxPatternTime;

	currentReloadTime = 0;
	speedX = 3.0f;
	speedY = 0.0f;

}

void Boss::update()
{

	if (isExploding)
	{
		explodeTime--;
		return;
	}

	patternTimer--;
	if (patternTimer <= 0)
	{
		pattern = (pattern == 1) ? 2 : 1;
		patternTimer = maxPatternTime;
	}

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (pattern == 1)
	{
		PatternOne();
	}
	else
	{
		PatternTwo();
	}

	if (x <= 0 || x >= SCREEN_WIDTH - width)
	{
		speedX = -speedX;
	}

}

void Boss::PatternOne()
{

	x += speedX * 1.5f;

	if (currentReloadTime <= 0)
	{
		float dx = (player->GetX() + (player->GetWidth() / 2)) - (x + (width / 2));
		float dy = (player->GetY() + (player->GetHeight() / 2)) - (y + height);
		float length = sqrt((dx * dx) + (dy * dy));


		if (length != 0) { dx /= length; dy /= length; }

		Bullet* b = new Bullet(x + (width / 2), y + height, dx, dy, 7, Side::ENEMY_SIDE);
		getScene()->addGameObject(b);

		currentReloadTime = 20;

	}

}

void Boss::PatternTwo()
{

	x += speedX * 0.5f;

	if (currentReloadTime <= 0)
	{
		float spread[5] = { -0.8f, -0.4f, 0.0f, 0.4f, 0.8f };

		for (int i = 0; i < 5; i++)
		{
			Bullet* b = new Bullet(x + (width / 2), y + height, spread[i], 1.0f, 5, Side::ENEMY_SIDE);
			getScene()->addGameObject(b);
		}
		currentReloadTime = 45;
	}

}

void Boss::draw()
{
	if (!isExploding)
	{
		int drawH, drawW;

		blitScale(texture, x, y, &drawW, &drawH, 2);
	}
}

void Boss::takeDamage()
{

	hp--;
	if (hp <= 0 && !isExploding)
	{
		isExploding = true;
		explodeTime = 30;
	}

}

bool Boss::isDead()
{
	return isExploding && explodeTime <= 0;
}