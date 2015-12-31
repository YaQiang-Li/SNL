//
// Created by shiyang on 15/12/30.
//

#include "TcpServer.h"
#include "TcpConnection.h"
#include "EventLoop.hpp"

//FIXME: check_not_null is not implement
#define CHECK_NOTNULL

TcpServer::TcpServer(EventLoop* loop)
    :loop_(CHECK_NOTNULL(loop)),
     listenfd_(socket(AF_INET,SOCK_STREAM,0))
                     //const InetAddress& listenAddr,
                     //const string& nameArg)
{
    loop_->setServer(this);

    //struct sockaddr_in clientaddr;
    //struct sockaddr_in serveraddr;
    //int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    //把socket设置为非阻塞方式
    //setnonblocking(listenfd);
    //设置与要处理的事件相关的文件描述符
    accpetEvent_.data.fd = listenfd_;
    accpetEvent_.events = EPOLLIN|EPOLLET;

    //ev.data.fd=listenfd_;
    //设置要处理的事件类型
    //ev.events=

    loop_->updateChannel();
    //注册epoll事件
    //epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    char *local_addr="127.0.0.1";
    inet_aton(local_addr,&(serveraddr.sin_addr));//htons(portnumber);
    serveraddr.sin_port=htons(portnumber);


    bind(listenfd_,(sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(listenfd_, 20);

    maxi = 0;
}

TcpServer::~TcpServer()
{

}


void TcpServer::EventRead()
{
    //TcpConnection * conn = new TcpConnection();
    TcpConnection * conn = findConnection();

    if (conn){
        newConnection(0);
    } else {
        conn->handleRead(0);
    }
}

void TcpServer::EventWrite()
{
    TcpConnection * conn = nullptr;
    conn->handleWrite();
}

void TcpServer::EventClose()
{
    TcpConnection * conn = nullptr;
    conn->handleClose();
}

void TcpServer::EventError()
{
    TcpConnection * conn = nullptr;
    conn->handleError();
}

void TcpServer::newConnection(int sockfd/*,const InetAddress& peerAddr*/)
{
    char buf[32];
    std::cout << buf << sizeof buf << hostport_ << nextConnId_ << std::endl;

    ++nextConnId_;
    std::string connName = name_ + buf;

    std::cout << "TcpServer::newConnection [" << name_
    << "] - new connection [" << connName
    << "] from " << peerAddr.toHostPort();


    //InetAddress localAddr(sockets::getLocalAddr(sockfd));

    // FIXME poll with zero timeout to double confirm the new connection
    TcpConnection* conn = new TcpConnection();

    //TcpConnectionPtr conn(
    //        new TcpConnection(ioLoop, connName, sockfd, localAddr, peerAddr));

    connections_[connName] = conn;
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    conn->setCloseCallback(&TcpServer::removeConnection);

    //        boost::bind(&TcpServer::removeConnection, this, _1));


    //ioLoop->runInLoop(boost::bind(&TcpConnection::connectEstablished, conn));
}

void TcpServer::removeConnection(const TcpConnection* & conn)
{
    connections_.erase(conn->getName());
    delete conn;
}

TcpConnection* TcpServer::findConnection()
{
    return nullptr;
}
