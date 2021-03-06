#include "Loop.hpp"

#include "master.hpp"

#include "ObjectManager.hpp"
#include "Objects\ObjectInterfaces.hpp"

void Loop::start()
{
    this->resumeGame();
}

void Loop::stop() 
{ 
    this->pauseGame();
}

Loop::Loop()
{
    using namespace cocos2d;

    cc::CCDirector::sharedDirector()->setScheduler(this);

    cc::CCScheduler::scheduleSelector( schedule_selector(TimeLoop_t::tick), &_time_loop, 1.f, true);
    cc::CCScheduler::scheduleUpdateForTarget( &_view_loop, 0, true);
}

void Loop::resumeTime()
{
    cc::CCScheduler::resumeTarget(&_time_loop);
}

void Loop::pauseTime()
{
    cc::CCScheduler::pauseTarget(&_time_loop);
}

void Loop::resumeGame()
{
    cc::CCScheduler::resumeTarget(&_view_loop);
    this->resumeTime();
}

void Loop::pauseGame()
{
    cc::CCScheduler::pauseTarget(&_view_loop);
    this->pauseTime();
}

void Loop::TimeLoop_t::tick(float t)
{
    auto objects = master_t::subsystem<ObjectManager>().getDynamicObjects();
    auto it = objects.begin();
    auto end = objects.end();
    
    for( ; it != end; ++it )
    {
        (*it)->updateState( t );
    }
}

void Loop::ViewLoop_t::update( float t )
{
    master_t::subsystem<Physics>().step( float dt );
    
    auto objects = master_t::subsystem<ObjectManager>().getObjects();
    auto it = objects.begin();
    auto end = objects.end();
    
    for( ; it != end; ++it )
    {
        (*it)->draw();
    }
}
