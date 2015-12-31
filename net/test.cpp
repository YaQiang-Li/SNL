//
// Created by shiyang on 15/12/30.
//

#include <iostream>

#include "EventLoop.hpp"
#include "TcpServer.h"
#include "TcpConnection.h"

void onConnection(const TcpConnection* & conn)
{
    std::cout << "onConnection" << std::endl;
    return ;
    /*
    if (conn->connected())
    {
        conn->setTcpNoDelay(true);
    }*/
}

void onMessage(const TcpConnection* & conn, Buffer* buf, Timestamp)
{
    std::cout << "onMessage" << std::endl;
    return ;
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cerr << "Usage: server <address> <port> <threads>" << std::endl;
    }
    else
    {
        std::cout << "pid = " << getpid() << ", tid = " << std::endl;

        const char* ip = argv[1];
        uint16_t port = static_cast<uint16_t>(atoi(argv[2]));

        //InetAddress listenAddr(ip, port);
        //int threadCount = atoi(argv[3]);







        EventLoop loop;

        //TcpServer server(&loop, listenAddr, "PingPong");
        TcpServer server(&loop);

        server.setConnectionCallback(onConnection);
        server.setMessageCallback(onMessage);

        //server.start();

        loop.loop(0);
    }
}
