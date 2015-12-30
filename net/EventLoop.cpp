
#include "EventLoop.hpp"



EventLoop::EventLoop() :
    epoll_(new Epoll())
{
    std::cout << "EventLoop Init..." << std::endl;
}

EventLoop::~EventLoop()
{
    delete epoll_;
}

void EventLoop::loop()
{
    loopQuit_ = false;
    while ( !loopQuit_  ) {
        activeEvents_.clear();
        epoll_->epollWait(&activeEvents_);
#ifdef DEBUG
        for ( EventArray::iterator it = activeEvents_.begin();
                it != activeEvents_.end(); ++it) {
            std::cout << "test" << std::endl;
        }
#endif
        for ( EventArray::iterator it = activeEvents_.begin();
                it != activeEvents_.end(); ++it) {
            handleEvent(*it);
        }
    }
}

void EventLoop::handleEvent(Event* events)
{
    if (events) {

    }
}
