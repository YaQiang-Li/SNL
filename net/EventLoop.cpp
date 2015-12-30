
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

void EventLoop::loop(int flags)
{
    loopDone_ = flags & EVLOOP_ONESHOT;
    do {
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
        callPending();
    } while( !loopDone_ );
}

void EventLoop::handleEvent(Event* events)
{
    int flag = events->events;
    if (flag & EPOLLRDHUP) {

    }

    if (flag & EPOLLIN) {

    }

    if (flag & EPOLLOUT) {

    }

    if (flag & (EPOLLPRI | EPOLLERR | EPOLLHUP)){

    }
}

void EventLoop::callPending()
{

}
