#include <iostream>

#include "Explosion.cpp"
#include "ExplosionFactory.cpp"
#include "ExplosionCacheProxy.cpp"
#include "ExplosionFacade.cpp"

using namespace std;

int main() 
{
    ExplosionBuilder builder;
    
    shared_ptr<ExplosionConfig> config1 = builder
        .withPosition(10, 10)
        .withColor("red")
        .withCount(5)
        .withSpread(10.0f)
        .build();
    
    shared_ptr<ExplosionConfig> config2 = builder
        .withPosition(10, 10)
        .withColor("red")
        .withCount(5)
        .withSpread(10.0f)
        .build();


    shared_ptr<ExplosionConfig> config3 = builder
        .withPosition(20, 20)
        .withColor("yellow")
        .withCount(10)
        .withSpread(10.0f)
        .build();

    ExplosionFacade::getInstance()
        ->triggerExplosion(*config1);

    ExplosionFacade::getInstance()
        ->triggerExplosion(*config2);

    ExplosionFacade::getInstance()
        ->triggerExplosionWithoutProxy(*config3);

    return 0;
}

