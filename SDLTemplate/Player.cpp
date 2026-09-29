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
	x = 100;
	y = 100;
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
}

void Player::update()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->GetX() > SCREEN_WIDTH)
		{
			Bullet* bulletToDelete = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToDelete;

			break;
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
			x + width - 5,
			y + (height / 2) - 5,
			1,
			0,
			5,
			Side::PLAYER_SIDE
		);
		getScene()->addGameObject(bullet);
		bullets.push_back(bullet);

		currentReloadTime = reloadTime;
	}

	if (app.keyboard[SDL_SCANCODE_G] && currentWingRT <= 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet
		(
			x + width - 3,
			y + (height / 2) - 27,
			1,
			0,
			5,
			Side::PLAYER_SIDE
		);
		getScene()->addGameObject(bullet);
		bullets.push_back(bullet);

		currentWingRT = wingRT;

		SoundManager::playSound(sound);
		Bullet* bullet2 = new Bullet
		(
			x + width - 3,
			y + (height / 2) - -22,
			1,
			0,
			5,
			Side::PLAYER_SIDE
		);
		getScene()->addGameObject(bullet2);
		bullets.push_back(bullet2);

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

bool Player::GetIsAlive()
{
	return isAlive;
}