
#include "Epoll.hpp"

#include <sys/epoll.h>
#include <unistd.h>

Epoll::Epoll()
    : epollFd_(::epoll_create(256))
{

}

Epoll::~Epoll()
{
    close(epollFd_);
}

int Epoll::epollWait(EventArray* activeEvents)
{
    int eventNum = epoll_wait(epollFd_,
                          &*events_.begin(),static_cast<int>(events_.size()),timeoutMs);
    if (eventNum > 0) {
        std::cout << "eventNum is " << eventNum << std::endl;
        foreachEventsGetData(eventNum, activeEvents);
    } else if( eventNum == 0 ) {
        std::cout << "no things happened.." << std::endl;
    } else{
        std::cerr << "epoll_wait() error..." << std::endl;
    }
    //TODO: return timestamp!!!FIXME
    return 0;
}

int Epoll::foreachEventsGetData(int eventNum, EventArray* activeEvents)
{
    for (int i = 0; i < eventNum; i++) {
#ifdef DEBUG
    int fd = events_[i].data.fd;
#endif
        activeEvents->push_back(events_[i]);
    }
}
