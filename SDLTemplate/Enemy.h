#pragma once
#include "GameObject.h"
#include "util.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Player.h"
#include <vector>

class Enemy :
    public GameObject
{
public:
    Enemy(Player* player);
    ~Enemy();
    void start() override;
    void update() override;
    void draw() override;

private:
    int x;
    int y;
    int height;
    int width;

    SDL_Texture* texture;
    Mix_Chunk* sound;

    int speed;
    int directionX;
    int directionY;
    float directionChangeTime;
    float currentDirectionChangeTime;

    float reloadTime;
    float currentReloadTime;

    std::vector <Bullet*> bullets;

    Player* targetPlayer;

};



