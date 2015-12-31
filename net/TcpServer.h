//
// Created by shiyang on 15/12/30.
//

#ifndef SNL_NET_TCPSERVER_H
#define SNL_NET_TCPSERVER_H
#include "TcpConnection.h"
#include <string>
#include <map>
#include <iostream>


class TcpServer {

public:
    TcpServer();
    virtual ~TcpServer();

    /// Starts the server if it's not listenning.
    ///
    /// It's harmless to call it multiple times.
    /// Not thread safe.
    void start();

    /// Set connection callback.
    /// Not thread safe.
    void setConnectionCallback(const ConnectionCallback& cb)
    { connectionCallback_ = cb; }

    /// Set message callback.
    /// Not thread safe.
    void setMessageCallback(const MessageCallback& cb)
    { messageCallback_ = cb; }

    /// Set write complete callback.
    /// Not thread safe.
    void setWriteCompleteCallback(const WriteCompleteCallback& cb)
    { writeCompleteCallback_ = cb; }


private:
    void newConnection(int sockfd/* const InetAddress& peerAddr*/);

    void removeConnection(const TcpConnection* & conn);


    typedef std::map<std::string, TcpConnection*> ConnectionMap;
    ConnectionMap connections_;
    std::string name_;
    std::string hostport_;
    int nextConnId_;
    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
};


#endif //SNL_NET_TCPSERVER_H
