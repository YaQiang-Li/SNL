
#ifndef SNL_NET_EVENTLOOP_H
#define SNL_NET_EVENTLOOP_H


#include "Epoll.hpp"
#include "TcpServer.h"



class EventLoop
{
public:
    EventLoop();
    ~EventLoop();
    void loop(int flags);

    TcpServer *getServer() const
    { return server_; }

    void setServer(TcpServer *server)
    { server_ = server; }

    void updateChannel(Epoll::CTL_TYPE type, int fd, Event ev);

private:

    void handleEvent(Event* event);
    Epoll* epoll_;
    bool loopDone_;
    EventArray activeEvents_;
    TcpServer* server_;
};

#endif  // SNL_NET_EVENTLOOP_H
