
#ifndef SNL_NET_EVENTLOOP_H
#define SNL_NET_EVENTLOOP_H


#include "Epoll.hpp"


class EventLoop
{
public:
    EventLoop();
    ~EventLoop();
    void loop();
private:
    void handleEvent(Event* events);

    Epoll* epoll_;
    bool loopQuit_;
    EventArray activeEvents_;
};

#endif  // SNL_NET_EVENTLOOP_H
