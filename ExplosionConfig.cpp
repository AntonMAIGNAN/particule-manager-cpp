#include <iostream>
using namespace std;

// =================================================================================
// ExplosionConfig - IMMUABLE
// Configuration d'une explosion 
// (position, couleur, nombre de particules, rayon d'explosion, durée de vie)
// =================================================================================
class ExplosionConfig
{
private:
    float x, y;
    string color; 
    int particleCount;
    float spread; 
    float lifetime; 

public:
    ExplosionConfig(float x, float y, const string &color, int particleCount, float spread, float lifetime) 
    {
        this->x = x;
        this->y = y;
        this->color = color;
        this->particleCount = particleCount;
        this->spread = spread;
        this->lifetime = lifetime;
    }
};