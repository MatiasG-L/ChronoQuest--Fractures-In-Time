#include "raylib.h"

class Npc{
    public:
    int width = 50;
    int height = 100;
    Vector2 position;
    std::string name;
    Texture2D sprite;
    std::string line;
    char state;
    Npc(int width, int height, Vector2 position, std::string name, std::string line, char state){
        this-> width = width;
        this-> height = height;
        this-> position = position;
        this-> name = name;
        this-> line = line;
        this-> width =  state;
    }
};
class ImpNpc : public Npc{
    
};
class QGNpc : public Npc{
    
};