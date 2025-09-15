class Enemy{
    public:
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
};