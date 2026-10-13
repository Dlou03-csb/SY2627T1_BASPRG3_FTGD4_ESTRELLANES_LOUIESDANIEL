#pragma once
#include "GameObject.h"
#include "draw.h"


class powerUP :
    public GameObject
{

public:
    powerUP(int startX, int startY);
    void start() override;
    void update() override;
    void draw() override;

private:
    SDL_Texture* texture;
    int speed;

};

