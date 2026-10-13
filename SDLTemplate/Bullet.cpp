#include "Bullet.h"

Bullet::Bullet(int positionX, int positionY, float directionX, float directionY, int speed, Side side, int bulletTexture)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
	this->side = side;
	this->bulletTexture = bulletTexture;
}

void Bullet::start()
{
	// Load texture
	// This only supports jpeg, png, and bitmaps

	if (side == Side::ENEMY_SIDE)
	{
		texture = loadTexture("gfx/alienBullet.png");
	}
	else
	{
		
		switch (bulletTexture)
		{
		case 1:
			texture = loadTexture("gfx/I_Sword.png");
			break;

		case 2:
			texture = loadTexture("gfx/G_Sword.png");
			break;

		case 3:
			texture = loadTexture("gfx/E_Sword.png");
			break;

		case 4:
			texture = loadTexture("gfx/H_Sword.png");
			break;
		}

	}

	// Initialize to avoid garbage values
	width = 0;
	height = 0;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Bullet::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void Bullet::draw()
{
	blit(texture, x, y);
}

Side Bullet::GetSide()
{
	return side;
}
