
#ifndef SNL_NET_EVENTLOOP_H
#define SNL_NET_EVENTLOOP_H


#include "Epoll.hpp"


class EventLoop
{
public:
    EventLoop();
    ~EventLoop();
    void loop(int flags);
private:
    void handleEvent(Event* events);

    Epoll* epoll_;
    bool loopDone_;
    EventArray activeEvents_;
};

#endif  // SNL_NET_EVENTLOOP_H
