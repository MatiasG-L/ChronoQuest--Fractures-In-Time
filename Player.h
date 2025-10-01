# include "raylib.h"

class Player{
    public:
    Texture2D textureBack;
    Texture2D textureWorld;
    int width = 50;
    int height = 100;
    Vector2 position;
    std::string name;
    float health;
    float maxHealth;
    int rank;
    int exp;
    int artificialAnomaly;
    int expRankUp;
    typedef struct{
        int physicalAtk;
        int specialAtk;
        int defence;
        int specialDefence;
        int speed;
        int stamina;
        int health;
    }Stats;

    Stats stats;
    
    typedef struct{
        int upgradeThreshold;
        float shieldMax;
        float shieldHealth;
        int robustness;
        int strength;
        int battery;
        int maxBattery;
    }Suit;
    
    Suit suit;
    
    typedef struct{
        int Attack;
        int Defence;
        int Speed;
    }SuitStats;
    
    SuitStats suitStats;
    
    int weight;

    
    
    Player(int width, int height, Vector2 position, std::string name, int rank, int expRankUp, Stats stats, Suit suit, SuitStats suitStats){
        this->width = width;
        this->height = height;
        this->position = position;
        this->name =  name;
        this->rank = rank;
        this->expRankUp = expRankUp;
        this->stats = stats;
        this->suit = suit;
        this->suitStats = suitStats;
    }
    
    Vector2 Velocity = {0,0};
};