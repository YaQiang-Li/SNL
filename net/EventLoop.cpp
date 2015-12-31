
#include "EventLoop.hpp"
#include "TcpServer.h"


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
        //callPending();
    } while( !loopDone_ );
}

void EventLoop::handleEvent(Event* events)
{
    int flag = events->events;
    if (flag & EPOLLRDHUP) {
        server_->EventClose();
    }

    if (flag & EPOLLIN) {
        server_->EventRead();
    }

    if (flag & EPOLLOUT) {
        server_->EventWrite();
    }

    if (flag & (EPOLLPRI | EPOLLERR | EPOLLHUP)){
        server_->EventError();
    }
}

void EventLoop::updateChannel()
{
    int a;
    epoll_->epollAdd();
    epoll_->epollModify();
    epoll_->epollDelete();
    epoll_->epollUpdate();
}
void EventLoop::callPending()
{

}
