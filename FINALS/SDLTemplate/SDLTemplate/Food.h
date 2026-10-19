#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Food :
    public GameObject
{
public:

    Food();

    void start() override;
    void update() override;
    void draw() override;

    void spawnAt(int pixelX, int pixelY);

private:

    SDL_Texture* texture;
};

