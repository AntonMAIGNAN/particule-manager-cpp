#include <iostream>

#include "Explosion.cpp"
#include "ExplosionFactory.cpp"
#include "ExplosionCacheProxy.cpp"

using namespace std;

int main() 
{
    ExplosionCacheProxy proxy;
    ExplosionBuilder builder;
    ExplosionFactory factory;
    
    shared_ptr<ExplosionConfig> config1 = builder
        .withPosition(10, 10)
        .withColor("red")
        .withCount(5)
        .withSpread(10.0f)
        .build();
    Explosion exp1 = proxy.create(*config1);
    exp1.render();
    
    shared_ptr<ExplosionConfig> config2 = builder
        .withPosition(10, 10)
        .withColor("red")
        .withCount(5)
        .withSpread(10.0f)
        .build();
    Explosion exp2 = proxy.create(*config2);
    exp2.render();
    
    shared_ptr<ExplosionConfig> config3 = builder
        .withPosition(20, 20)
        .withColor("yellow")
        .withCount(10)
        .withSpread(10.0f)
        .build();
    Explosion exp3 = factory.create(*config3);
    exp3.render();

    return 0;
}