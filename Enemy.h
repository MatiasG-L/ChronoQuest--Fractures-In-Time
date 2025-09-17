#include "raylib.h"

class Enemy{
    public:
    Texture2D spriteBack;
    Texture2D spriteWorld;
    int width;
    int height;
    Vector2 position;
    std::string name;
    float health;
    float maxHealth;
    int threatLevel;
    int Anomaly;
    typedef struct{
        int physicalAtk;
        int specialAtk;
        int defence;
        int specialDefence;
        int speed;
    }Stats;
    
    Stats stats;
    
    Enemy(int width, int height, Vector2 position, std::string name, float maxHealth, int threatLevel, Stats stats){
        this->width = width;
        this->height = height;
        this->position = position;
        this->name = name;
        this->maxHealth = maxHealth;
        this->threatLevel = threatLevel;
        this->stats = stats;
    }
};