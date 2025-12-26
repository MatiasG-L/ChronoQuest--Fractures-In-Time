# include "raylib.h" 

class Player{
    public:
    Texture2D textureBack;
    Texture2D textureWorld;
    float width = 50;
    float height = 100;
    Vector2 position;
    std::string name;
    float health = 100;
    float maxHealth = 100;
    int rank;
    float stamina = 100;
    float maxStamina = 100;
    int exp;
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
        int attack;
        int defence;
        float shieldMax;
        float shieldHealth;
        int battery;
        int maxBattery;
    }Suit;
    
    Suit suit;
    
    int weight;

    
    
    Player(int width, int height, Vector2 position, std::string name, int rank, int expRankUp, Stats stats, Suit suit){
        this->width = width;
        this->height = height;
        this->position = position;
        this->name =  name;
        this->rank = rank;
        this->expRankUp = expRankUp;
        this->stats = stats;
        this->suit = suit;
    }
    
    float specialDamageOut(){
        return (stats.specialAtk * (1 + suit.attack/2) * rank/(stats.specialAtk + suit.attack)) * ((suit.battery/suit.maxBattery) + 0.5);
    }
    
    float physicalDamageOut(){
        return (stats.physicalAtk * (1 + suit.attack/2) * rank/(stats.physicalAtk + suit.attack)) * ((stamina/maxStamina) + 0.5);
    }
    
};