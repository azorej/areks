#include "Physics.hpp"

void Physics::start() {}
void Physics::stop() {}
    
Physics::Physics() 
{
    b2Vec2 gravity(0.0f, -10.0f);
    bool doSleep = true;
    _b2World_ptr.reset( new b2World(gravity) );
    _b2World_ptr->SetAllowSleeping( doSleep );
}

b2World* Physics::worldEngine()
{
    return _b2World_ptr.get();
}

void Physics::step( float dt )
{
    static int velocityIterations = 8;
    static int positionIterations = 3;
    
    _b2World_ptr->Step( dt, velocityIterations, positionIterations );
}