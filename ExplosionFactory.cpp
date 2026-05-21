#pragma once
#include <iostream>

#include "ParticlePrototype.cpp"
#include "FlyweightFactory.cpp"
#include "Explosion.cpp"

using namespace std;

// =================================================================================
// Explosion
// Contient une collection de particules créées à partir d'une configuration d'explosion
// =================================================================================
class Explosion
{
private:
    vector<ParticlePrototype> particles;
public:
    void addParticle(const ParticlePrototype &particle) 
    {
        particles.push_back(particle);  
    }
};

// =================================================================================
// ExplosionFactory
// Factory pour créer des explosions à partir d'une configuration d'explosion
// =================================================================================
class ExplosionFactory
{
private:
    ExplosionFactory() {}

    float randomSpeedFromSpread(float spread) const
    {
        return ((float)rand() / (float)RAND_MAX) * spread - (spread / 2);
    }

    float randomSizeFromSpread(float spread) const
    {
        return ((float)rand() / (float)RAND_MAX) * spread + 0.5f;
    }

public:
    Explosion create(ExplosionConfig &config) 
    {
        FlyweightFactory *flyweightFactory = FlyweightFactory::getInstance();
        Explosion explosion;

        ParticleFlyweight *prototype = flyweightFactory->getParticle(config.getType());

        ParticlePrototype *p = new ParticlePrototype(
            this->randomSizeFromSpread(config.getSpread()), 
            config.getColor(), 
            this->randomSpeedFromSpread(config.getSpread()), 
            config.getX(), 
            config.getY(), 
            prototype->getTexture(), 
            prototype->getShader(), 
            prototype->getPhysics()
        );

        for (int i = 0; i < config.getParticleCount(); i++) 
        {
            IParticlePrototype* clonedBase = p->clone();
            explosion.addParticle(* dynamic_cast<ParticlePrototype*>(clonedBase));
        }

        delete p;

        return explosion;
    }
};