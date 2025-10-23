#include raylib.h

class Npc{
    public:
    int width = 50;
    int height = 100;
    Vector2 position;
    std::string name;
    Texture2D sprite;
    std::string line;
    char state;
}