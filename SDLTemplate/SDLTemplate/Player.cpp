#include "Player.h"

Player::Player()
{

	headTexture = NULL;
	bodyTexture = NULL;
	tailTexture = NULL;
	dirX = 1;
	dirY = 0;
	nextDirX = 1;
	nextDirY = 0;
	moveDelay = 8;
	moveTimer = 0;
	isAlive = true;
	shouldGrow = false;

}

Player::~Player()
{
	parts.clear();
}

void Player::start()
{

	headTexture = loadTexture("gfx/snake_head.png");
	bodyTexture = loadTexture("gfx/snake_body.png");
	tailTexture = loadTexture("gfx/snake_tail.png");

	width = Grid::TILE_SIZE;
	height = Grid::TILE_SIZE;

	moveDelay = 8;

	reset();

}

void Player::reset()
{

	parts.clear();

	int startCol = Grid::COL / 2;
	int startRow = Grid::ROW / 2;
	int startX = Grid::OFFX + (startCol * Grid::TILE_SIZE);
	int startY = Grid::OFFY + (startRow * Grid::TILE_SIZE);

	parts.push_back({ startX, startY });
	parts.push_back({ startX - Grid::TILE_SIZE, startY });
	parts.push_back({ startX - (Grid::TILE_SIZE * 2), startY });

	x = parts[0].x;
	y = parts[0].y;

	dirX = 1;
	dirY = 0;
	nextDirX = 1;
	nextDirY = 0;

	moveTimer = moveDelay;
	isAlive = true;
	shouldGrow = false;


}

void Player::update()
{

	if (!isAlive)
	{
		return;
	}

	if (app.keyboard[SDL_SCANCODE_W] && dirY != 1)
	{
		nextDirX = 0;
		nextDirY = -1;
	}
	else if (app.keyboard[SDL_SCANCODE_S] && dirY != -1)
	{
		nextDirX = 0;
		nextDirY = 1;
	}
	else if (app.keyboard[SDL_SCANCODE_A] && dirX != 1)
	{
		nextDirX = -1;
		nextDirY = 0;
	}
	else if (app.keyboard[SDL_SCANCODE_D] && dirX != -1)
	{
		nextDirX = 1;
		nextDirY = 0;
	}

	if (moveTimer > 0)
	{
		moveTimer--;
	}
	else
	{
		move();
		moveTimer = moveDelay;
	}

}

void Player::move()
{

	dirX = nextDirX;
	dirY = nextDirY;

	SnakePart oldTail = parts.back();

	for (int i = (int)parts.size() - 1; i > 0; i--)
	{
		parts[i] = parts[i - 1];
	}

	parts[0].x += dirX * Grid::TILE_SIZE;
	parts[0].y += dirY * Grid::TILE_SIZE;

	x = parts[0].x;
	y = parts[0].y;

	if (shouldGrow)
	{
		parts.push_back(oldTail);
		shouldGrow = false;
	}

}

void Player::draw()
{

	for (int i = 0; i < (int)parts.size(); i++)
	{
		double angle = getPartsAngle(i);

		if (i == 0)
		{
			blitRotate(headTexture, parts[i].x, parts[i].y, angle);
		}
		else if (i == (int)parts.size() - 1)
		{
			blitRotate(tailTexture, parts[i].x, parts[i].y, angle);
		}
		else
		{
			blitRotate(bodyTexture, parts[i].x, parts[i].y, angle);
		}
	}

}

double Player::getPartsAngle(int index)
{

	int dx = 0;
	int dy = 0;

	if (index == 0)
	{
		dx = dirX;
		dy = dirY;
	}
	else
	{
		dx = parts[index - 1].x - parts[index].x;
		dy = parts[index - 1].y - parts[index].y;
	}

	if (dy < 0) 
		return 0;
	if (dx > 0) 
		return 90;
	if (dy > 0) 
		return 180;
	if (dx < 0) 
		return 270;

	return 0;

}

void Player::grow()
{
	shouldGrow = true;
}

void Player::doDeath()
{
	isAlive = false;
}

bool Player::getIsAlive()
{
	return isAlive;
}

bool Player::checkWallCollision()
{

	return 
	(
		x < Grid::OFFX ||
		x >= Grid::OFFX + Grid::WIDTH ||
		y < Grid::OFFY ||
		y >= Grid::OFFY + Grid::HEIGHT

	);

}

bool Player::checkSelfCollision()
{

	for (int i = 1; i < (int)parts.size(); i++)
	{
		int collision = checkCollision
		(
			x, y, width, height,
			parts[i].x, parts[i].y, width, height
		);

		if (collision == 1)
		{
			return true;
		}
	}

	return false;

}

bool Player::isOccupyingTile(int tileX, int tileY)
{

	int pixelX = Grid::OFFX + (tileX * Grid::TILE_SIZE);
	int pixelY = Grid::OFFY + (tileY * Grid::TILE_SIZE);

	for (int i = 0; i < (int)parts.size(); i++)
	{
		if (parts[i].x == pixelX && parts[i].y == pixelY)
		{
			return true;
		}
	}

	return false;

}