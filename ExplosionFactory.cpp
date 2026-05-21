#pragma once
#include <iostream>

#include "ParticlePrototype.cpp"
#include "ParticuleDecorator.cpp"
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
    vector<shared_ptr<IParticle>> particles;
public:
    void addParticle(shared_ptr<IParticle> particle) 
    {
        particles.push_back(particle);  
    }

    void render() 
    {
        cout << "=== Rendering Explosion ===" << endl;
        cout << "[Explosion] Rendering explosion with " << particles.size() << " particles.\n" << endl;
        for (const auto& p : particles) {
            p->render();
            cout << "\n" << endl;
        }
        cout << "=========================\n" << endl;

    }
};

// =================================================================================
// IExplosionFactory
// Interface pour la factory d'explosion
// =================================================================================
class IExplosionFactory
{
public:
    virtual Explosion create(ExplosionConfig &config) = 0;
    virtual ~IExplosionFactory() {}
};


// =================================================================================
// ExplosionFactory
// Factory pour créer des explosions à partir d'une configuration d'explosion
// =================================================================================
class ExplosionFactory: public IExplosionFactory
{
private:
    float randomSpeedFromSpread(float spread) const
    {
        return ((float)rand() / (float)RAND_MAX) * spread - (spread / 2);
    }

    float randomSizeFromSpread(float spread) const
    {
        return ((float)rand() / (float)RAND_MAX) * spread + 0.5f;
    }

    IParticle* addRandomDecoration(IParticle* base) const
    {
        int randVal = rand() % 4;

        switch (randVal) 
        {
            case 0:
                return new GlowDecorator(base);
            case 1:
                return new ShadowDecorator(base);
            case 2:
                return new FadeOutDecorator(base);
            default:
                return base;
        }
    }

public:
    ExplosionFactory() {}

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
            explosion.addParticle(shared_ptr<IParticle>(this->addRandomDecoration(dynamic_cast<IParticle*>(clonedBase))));
        }

        delete p;

        return explosion;
    }
};