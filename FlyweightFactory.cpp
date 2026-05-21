#pragma once
#include <iostream>
#include <mutex>

using namespace std;

// =================================================================================
// ParticleFlyweight 
// Base shape (texture, shader, physics) partagée entre les particules du même type.
// =================================================================================
class ParticleFlyweight
{
private:
    string texture;
    string shader;
    string physics;

public:
    ParticleFlyweight(const string &particuleType)
    {
        // Devrait avoir un fichier JSON répertoire pour récupérer 
        // les données de chaque type de particule. (ici on simule juste avec des strings)
        this->texture = "texture_" + particuleType;
        this->shader = "shader_" + particuleType;
        this->physics = "physics_" + particuleType;
    }

    // GETTERS
    string getTexture()
    {
        return texture;
    }

    string getShader()
    {
        return shader;
    }

    string getPhysics()
    {
        return physics;
    }
};

// =====================================================================================
// FlyweightFactory 
// Méthodes :
// - getInstance() : Retourne l'instance singleton de la factory.
// - getParticle(const string &particleType) : Retourne une instance de ParticleFlyweight
// ======================================================================================
class FlyweightFactory
{
private:    
    FlyweightFactory() {}

    static FlyweightFactory* instance;

    // Mutex pour protéger l'accès à l'instance singleton
    static mutex factoryMutex;

    // Map pour stocker les instances de ParticleFlyweight partagées
    unordered_map<string, shared_ptr<ParticleFlyweight>> Particles;

    ~FlyweightFactory() {}

public:
    static FlyweightFactory* getInstance()
    {
        lock_guard<mutex> lock(factoryMutex);

        if (instance == nullptr) {
            instance = new FlyweightFactory();
        }

        return instance;
    }

    ParticleFlyweight* getParticle(const string &particleType)
    {
        if (Particles.find(particleType) == Particles.end())
        {
            Particles[particleType] = make_shared<ParticleFlyweight>(particleType);
        }

        return Particles[particleType].get();
    }
};

FlyweightFactory* FlyweightFactory::instance = nullptr;
mutex FlyweightFactory::factoryMutex;