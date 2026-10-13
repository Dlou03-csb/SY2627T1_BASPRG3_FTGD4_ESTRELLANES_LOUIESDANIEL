#include "powerUP.h"

powerUP::powerUP(int startX, int startY)
{
	x = startX;
	y = startY;

}

void powerUP::start()
{
	
	texture = loadTexture("gfx/KOB.png");
	width = 0;
	height = 0;
	speed = 2;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

}

void powerUP::update()
{
	y += speed;
}

void powerUP::draw()
{
	blit(texture, x, y);
}
