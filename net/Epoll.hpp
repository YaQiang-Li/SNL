
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
        //int epollUpdate(int fd, const Event &ev);
        int epollAdd(int fd, const Event &ev);
        int epollDelete(int fd, const Event &ev);
        int epollModify(int fd, const Event &ev);

    enum CTL_TYPE { ADD, MOD, DEL, UPD };

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
