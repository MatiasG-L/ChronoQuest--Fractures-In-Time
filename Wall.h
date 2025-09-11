#include "raylib.h"

class Wall{
    public:
    int height;
    int width;
    Vector2 position;
    Wall(int height, int width, Vector2 position){
        this->height = height;
        this->width = width;
        this->position = position;
    }
};