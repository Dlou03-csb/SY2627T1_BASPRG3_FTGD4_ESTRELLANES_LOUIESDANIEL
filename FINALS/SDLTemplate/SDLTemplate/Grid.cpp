#include "Grid.h"

void Grid::draw()
{

	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);

	for (int col = 0; col <= COL; col++)
	{
		int lineX = OFFX + (col * TILE_SIZE);
		SDL_RenderDrawLine(app.renderer, lineX, OFFY, lineX, OFFY + HEIGHT);

	}

	for (int row = 0; row <= ROW; row++)
	{
		int lineY = OFFY + (row * TILE_SIZE);
		SDL_RenderDrawLine(app.renderer, OFFX, lineY, OFFX + WIDTH, lineY);

	}
	

}
