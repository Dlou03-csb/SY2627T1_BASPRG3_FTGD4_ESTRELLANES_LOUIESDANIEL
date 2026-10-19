#include "Food.h"
#include "Grid.h"

Food::Food()
{
	texture = NULL;
}

void Food::start()
{

	texture = loadTexture("gfx/Apple.png");
	width = Grid::TILE_SIZE;
	height = Grid::TILE_SIZE;


}

void Food::update()
{
}

void Food::draw()
{
	blit(texture, x, y);
}

void Food::spawnAt(int pixelX, int pixelY)
{

	x = pixelX;
	y = pixelY;

}
