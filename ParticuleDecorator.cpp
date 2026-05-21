#pragma once
#include <iostream>

using namespace std;

class ParticlePrototype;

// =================================================================================
// IParticle
// Interface de base pour rendre les particules.
// =================================================================================
class IParticle
{
public:
    virtual void render() = 0;
    virtual ~IParticle() {}
};

// =================================================================================
// IParticleDecorator
// Classe de base pour les décorateurs de particules.
// Abstraite car le render n'a pas de comportenement concret
// =================================================================================
class IParticleDecorator: public IParticle
{
protected:
    IParticle* decoratedParticle;
public:
    IParticleDecorator(IParticle* particle)
    {
        decoratedParticle = particle;
    }

    virtual void render() override
    {
        if (decoratedParticle)
        {
            decoratedParticle->render();
        }
    }
    
    virtual ~IParticleDecorator() { delete decoratedParticle; }
};

// =================================================================================
// Decorators concrets
// =================================================================================
class GlowDecorator : public IParticleDecorator
{
public:
    GlowDecorator(IParticle* particle) : IParticleDecorator(particle) {}

    void render() override
    {
        IParticleDecorator::render();
        cout << " -> Applying Glow Effect" << endl;
    }
};

class ShadowDecorator : public IParticleDecorator
{
public:
    ShadowDecorator(IParticle* particle) : IParticleDecorator(particle) {}

    void render() override
    {
        IParticleDecorator::render();
        cout << " -> Applying Shadow Effect" << endl;
    }
};

class FadeOutDecorator : public IParticleDecorator
{
public:
    FadeOutDecorator(IParticle* particle) : IParticleDecorator(particle) {}

    void render() override
    {
        IParticleDecorator::render();
        cout << " -> Applying FadeOut Effect" << endl;
    }
};