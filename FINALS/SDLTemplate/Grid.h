#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h"


class Grid :
    public GameObject
{
public:

    static const int TILE_SIZE = 40;
    static const int COL = 30;
    static const int ROW = 15;
    static const int OFFX = 40;
    static const int OFFY = 80;
    static const int WIDTH = TILE_SIZE * COL;
    static const int HEIGHT = TILE_SIZE * ROW;

    void draw() override;

};

