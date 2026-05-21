#pragma once
#include <iostream>
#include <mutex>
#include "ExplosionCacheProxy.cpp"
#include "ExplosionFactory.cpp"

using namespace std;


class ExplosionFacade
{
private:
    ExplosionFacade() {}

    static ExplosionFacade* instance;

    static mutex facadeMutex;

    ExplosionCacheProxy cacheProxy;

    ExplosionFactory factory;

public:
    static ExplosionFacade* getInstance() 
    {
        lock_guard<mutex> lock(facadeMutex);

        if (instance == nullptr) 
        {
            instance = new ExplosionFacade();
        }

        return instance;
    }

    void triggerExplosionWithoutProxy(const ExplosionConfig& config)
    {
        Explosion explosion = factory.create(const_cast<ExplosionConfig&>(config));
        explosion.render();
    };

    void triggerExplosion(const ExplosionConfig& config)
    {
        Explosion explosion = cacheProxy.create(const_cast<ExplosionConfig&>(config));
        explosion.render();
    };
};

ExplosionFacade* ExplosionFacade::instance = nullptr;
mutex ExplosionFacade::facadeMutex;