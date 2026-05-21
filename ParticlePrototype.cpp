#pragma once
#include <iostream>

#include "ParticuleDecorator.cpp"

using namespace std;

// =================================================================================
// IParticlePrototype 
// interface de clonage pour les particules.
// =================================================================================
class IParticlePrototype
{
public:
    virtual IParticlePrototype* clone() const = 0;

    virtual ~IParticlePrototype() {}
};

// =================================================================================
// ParticlePrototype
// Particule concrète représentant une particule
// =================================================================================
class ParticlePrototype : public IParticlePrototype, public IParticle
{
private:
    float size;
    string color;
    float speed;
    float x, y;
    string texture;
    string shader;
    string physics;

public:
    ParticlePrototype(float size, const string &color, float speed, float x, float y, const string &texture, const string &shader, const string &physics) 
    {
        this->size = size;
        this->color = color;
        this->speed = speed;
        this->x = x;
        this->y = y;
        this->texture = texture;
        this->shader = shader;
        this->physics = physics;
    }

    IParticlePrototype* clone() const override
    {
        return new ParticlePrototype(*this);
    }

    void render() override
    {
        cout << "Rendering particle at (" << x << ", " << y << ") with size " << size << ", color " << color << ", speed " << speed 
             << ", texture " << texture << ", shader " << shader << ", physics " << physics << "." << endl;
    }
};
