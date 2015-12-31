//
// Created by shiyang on 15/12/30.
//

#include "TcpConnection.h"


TcpConnection::TcpConnection()
{

}

TcpConnection::~TcpConnection()
{

}


void TcpConnection::handleRead(int receiveTime)
{
    //loop_->assertInLoopThread();
    int savedErrno;
    int n;
    //ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
    if (n > 0)
    {
        messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
    }
    else if (n == 0)
    {
        handleClose();
    }
    else
    {
        // check savedErrno
    }
}

void TcpConnection::handleWrite()
{

}

void TcpConnection::handleClose()
{

}

void TcpConnection::handleError()
{
    //int err = sockets::getSocketError(channel_->fd());
    //std::cout << "TcpConnection::handleError [" << name_
    //<< "] - SO_ERROR = " << err << " " << strerror_tl(err);
}

//void newConnection(int sockfd/* const InetAddress& peerAddr*/) {
//
//    Socket *socket = new Socket();
//    //TcpConnectionPtr conn(
//    //new TcpConnection(ioLoop, connName, sockfd, localAddr, peerAddr));
//
//    connections_[connName] = conn;
//    conn->setConnectionCallback(connectionCallback_);
//    conn->setMessageCallback(messageCallback_);
//    conn->setWriteCompleteCallback(writeCompleteCallback_);
//    conn->setCloseCallback(&TcpServer::removeConnection);
//}
