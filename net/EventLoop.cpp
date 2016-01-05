
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

void EventLoop::handleEvent(Event* event)
{
    int flag = event->events;
    int fd = event->data.fd;

    if (flag & EPOLLRDHUP) {
        server_->EventClose();
    }

    if (flag & EPOLLIN) {
        server_->EventRead(fd);
    }

    if (flag & EPOLLOUT) {
        server_->EventWrite();
    }

    if (flag & (EPOLLPRI | EPOLLERR | EPOLLHUP)){
        server_->EventError();
    }
}

void EventLoop::updateChannel(Epoll::CTL_TYPE type,int fd, Event ev)
{
    switch (type){
        case Epoll::CTL_TYPE::ADD:
            epoll_->epollAdd(fd,ev);
            break;
        case Epoll::CTL_TYPE::DEL:
            epoll_->epollDelete(fd,ev);
            break;
        case Epoll::CTL_TYPE::MOD:
            epoll_->epollModify(fd,ev);
            break;
        //case Epoll::CTL_TYPE::UPD:
        //    epoll_->epollUpdate(fd);
        //    break;
        default:
            std::cerr << "ctlType error:" << type << std::endl;
            break;
    }
}

void EventLoop::callPending()
{

}
