
#ifndef SNL_NET_EPOLL_H
#define SNL_NET_EPOLL_H

#include "EventDefine.h"
#include <vector>
#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>

class Epoll {
    public:
        Epoll();
        virtual ~Epoll();
        int epollWait(EventArray* activeEvents);
        int epollUpdate();
        int epollAdd();
        int epollDelete();
        int epollModify();


    private:
        int foreachEventsGetData(int eventNum, EventArray* eventArray);
        int epollFd_;
        EventArray events_;
};

#endif  // SNL_NET_EPOLL_H

/*
class Event {

}
*/
