#include "raylib.h"

class Wall{
    public:
    int height;
    int width;
    Vector2 position;
    bool moveable = false;
    Color squr;
    Wall(int height, int width, Vector2 position, Color squr){
        this->height = height;
        this->width = width;
        this->squr = squr;
        this->position = position;
    }
    Wall(int height, int width, Vector2 position, bool moveable, Color squr){
        this->height = height;
        this->width = width;
        this->moveable = moveable;
        this->squr = squr;
        this->position = position;
    }
};