#pragma once
#include <iostream>

#include "ExplosionFactory.cpp"

using namespace std;

class ExplosionCacheProxy: public IExplosionFactory
{
private:
    IExplosionFactory* realFactory;
    unordered_map<std::string, Explosion> cache;

    string generateKey(ExplosionConfig& config)
    {
        return config.getType() + "_" + 
            config.getColor() + "_" + 
            to_string(config.getParticleCount()) + "_" + 
            to_string(config.getSpread()) + "_" +
            to_string(config.getLifetime()) + "_" +
            to_string(config.getX()) + "_" +
            to_string(config.getY());
    }

public:
    ExplosionCacheProxy() 
    {
        realFactory = new ExplosionFactory();
    }

    ~ExplosionCacheProxy() 
    {
        delete realFactory;
    }

    Explosion create(ExplosionConfig &config) override
    {
       string key = generateKey(config);

        if (cache.find(key) == cache.end()) 
        {
            cout << "[Proxy] Cache MISS" << endl;
            cache[key] = realFactory->create(config);
        } 
        else 
        {
            cout << "[Proxy] Cache HIT" << endl;
        }

        return cache[key];
    }
};
