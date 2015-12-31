//
// Created by shiyang on 15/12/30.
//

#include "TcpServer.h"
#include "TcpConnection.h"

TcpServer::TcpServer()
{

}

TcpServer::~TcpServer()
{

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
