#include "Player.h"
#include "GameScene.h"

Player::~Player()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}

	bullets.clear();
}

void Player::start()
{
	// Load texture
	// This only supports jpeg, png, and bitmaps
	texture = loadTexture("gfx/KING.png");
	sound = SoundManager::loadSound("sound/gilgameshlaugh.mp3");
	sound->volume = 64;

	// Initialize Variables
	x = (SCREEN_WIDTH / 2) - (width / 2) - 40;
	y = SCREEN_HEIGHT - 100;
	width = 0;
	height = 0;
	speed = 1;
	speedBoost = 5;
	defaultSpeed = 1;

	isAlive = true;

	reloadTime = 8; // 0.16sec (8/60)
	currentReloadTime = 0;
	wingRT = 15;
	currentWingRT = 0;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	level = 1;
	powerUpTimer = 0;
	maxPowerUpTime = 400;
}

void Player::update()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->GetY() < 0)
		{
			Bullet* bulletToDelete = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToDelete;

			break;
		}
	}

	if (level > 1)
	{

		if (powerUpTimer > 0)
		{
			powerUpTimer--;
		}
		else
		{
			level--;

			if (level > 1)
			{
				powerUpTimer = maxPowerUpTime;
			}

		}

	}


	if (!isAlive)
	{
		return;
	}

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}


	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime <= 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet
		(
			x + (width / 2) - 15,
			y + height - 100,
			0,
			-1,
			5,
			Side::PLAYER_SIDE,
			1
		);
		getScene()->addGameObject(bullet);
		bullets.push_back(bullet);

		if (level >= 2)
		{
			Bullet* bullet2 = new Bullet
			(
				x + (width / 2) - 40,
				y + height - 100,
				0,
				-1,
				5,
				Side::PLAYER_SIDE,
				3
			);
			getScene()->addGameObject(bullet2);
			bullets.push_back(bullet2);

			Bullet* bullet3 = new Bullet
			(
				x + (width / 2) + 10,
				y + height - 100,
				0,
				-1,
				5,
				Side::PLAYER_SIDE,
				4
			);
			getScene()->addGameObject(bullet3);
			bullets.push_back(bullet3);

		}

		currentReloadTime = reloadTime;
	}

	if (app.keyboard[SDL_SCANCODE_G] && currentWingRT <= 0)
	{
		SoundManager::playSound(sound);
		Bullet* leftBullet = new Bullet
		(
			x + (width / 2) - 70,
			y + height - 70,
			0,
			-1,
			5,
			Side::PLAYER_SIDE,
			2
		);
		getScene()->addGameObject(leftBullet);
		bullets.push_back(leftBullet);

		currentWingRT = wingRT;

		Bullet* rightBullet = new Bullet
		(
			x + (width / 2) + 50,
			y + height - 70,
			0,
			-1,
			5,
			Side::PLAYER_SIDE,
			2
		);
		getScene()->addGameObject(rightBullet);
		bullets.push_back(rightBullet);

		currentWingRT = wingRT;

	}

	if (currentWingRT > 0)
	{
		currentWingRT--;
	}

	if (app.keyboard[SDL_SCANCODE_W]) 
	{
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = speedBoost;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = defaultSpeed;
	}

}

void Player::draw()
{
	if (isAlive)
	{
		blit(texture, x, y);
	}

}

void Player::DoDeath()
{
	isAlive = false;
}

void Player::upgrade()
{

	if (level < 3)
	{
		level++;
	}
	powerUpTimer = maxPowerUpTime;

}

void Player::deleteBullet(Bullet* bulletToDelete)
{

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i] == bulletToDelete)
		{
			bullets.erase(bullets.begin() + i);
			delete bulletToDelete;
			break;
		}
	}

}

bool Player::GetIsAlive()
{
	return isAlive;
}