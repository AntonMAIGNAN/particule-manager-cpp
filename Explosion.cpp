#pragma once
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
    string type;

public:
    ExplosionConfig(float x, float y, const string &color, int particleCount, float spread, float lifetime, const string &type = "default") 
    {
        this->x = x;
        this->y = y;
        this->color = color;
        this->particleCount = particleCount;
        this->spread = spread;
        this->lifetime = lifetime;
        this->type = type;
    }

    // GETTERS
    float getX() 
    { 
        return x; 
    }

    float getY()  
    {
        return y;
    }

    string getColor()  
    { 
        return color; 
    }
    
    int getParticleCount()  
    { 
        return particleCount;
    }

    float getSpread()  
    { 
        return spread; 
    }

    float getLifetime()  
    { 
        return lifetime; 
    }
    
    string getType() 
    {
        return type;
    }
};

// =================================================================================
// ExplosionBuilder - BUILDER
// Méthodes :
// - withPosition(x,y)
// - withColor(Color c)
// - withCount(int n)
// - withSpread(float s)
// - withLifetime(float t)
// - build(): retourne un ExplosionConfig. 
// =================================================================================

class ExplosionBuilder 
{
private: 
    float x, y;
    string color; 
    int particleCount;
    float spread; 
    float lifetime; 
    string type;

public: 
    ExplosionBuilder() { reset(); }
    void reset() { 
        x = 0;
        y = 0;
        color = "no-color";
        particleCount = 1;
        spread = 0;
        lifetime = 0;
        type = "default";
    }

    ExplosionBuilder& withPosition(float x, float y) 
    {
        this->x = x;
        this->y = y;
        return *this;
    }

    ExplosionBuilder& withColor(const string &color) 
    {
        this->color = color;
        return *this;
    }

    ExplosionBuilder& withCount(int count) 
    {
        this->particleCount = count;
        return *this;
    }

    ExplosionBuilder& withSpread(float spread) 
    {
        this->spread = spread;
        return *this;
    }

    ExplosionBuilder& withLifetime(float lifetime) 
    {
        this->lifetime = lifetime;
        return *this;
    }

    ExplosionBuilder& withType(const string &type) 
    {
        this->type = type;
        return *this;
    }

    shared_ptr<ExplosionConfig> build() 
    {
        shared_ptr<ExplosionConfig> result = make_shared<ExplosionConfig>(x, y, color, particleCount, spread, lifetime, type);
        reset();
        return result;
    }
};