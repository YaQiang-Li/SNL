//
// Created by shiyang on 15/12/30.
//

#include <iostream>

#include "EventLoop.hpp"
#include "TcpServer.h"
#include "TcpConnection.h"

void onConnection(const TcpConnectionPtr& conn)
{
    if (conn->connected())
    {
        conn->setTcpNoDelay(true);
    }
}

void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp)
{
    conn->send(buf);
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

        TcpServer server(&loop, listenAddr, "PingPong");

        server.setConnectionCallback(onConnection);
        server.setMessageCallback(onMessage);

        server.start();

        loop.loop(0);
    }
}
