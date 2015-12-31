//
// Created by shiyang on 15/12/30.
//

#ifndef SNL_NET_TCPCONNECTION_H
#define SNL_NET_TCPCONNECTION_H
#include <string>

class TcpConnection;
class Buffer;
class Timestamp;

typedef void (*ConnectionCallback)(const TcpConnection & conn);

typedef void (*CloseCallback)(const TcpConnection* &);

typedef void (*WriteCompleteCallback)(const TcpConnection* &);

typedef void (*MessageCallback)(const TcpConnection* &,
                              Buffer*,
                              Timestamp);

//typedef void (*readCallback)(const TcpConnection & conn);
//typedef void (*writeCallback)(const TcpConnection & conn);
//typedef void (*closeCallback)(const TcpConnection & conn);
//typedef void (*errorCallback)(const TcpConnection & conn);

class TcpConnection {

public:
    TcpConnection();
    ~TcpConnection();
    //void setConnectionCallback(ConnectionCallback cb);

    //void setReadCallback(readCallback cb)
    //{ readCallBack_ = cb; }
    //void setWriteCallback(writeCallback cb)
    //{ writeCallBack_ = cb; }
    //void setCloseCallBack_(closeCallback cb)
    //{ closeCallBack_ = cb; }
    //void setErrorCallBack_(errorCallback cb)
    //{ errorCallBack_ = cb; }

    static void handleRead();
    static void handleWrite();
    static void handleClose();
    static void handleError();

    void setConnectionCallback(ConnectionCallback cb)
    { connectionCallback_ = cb; }

    void setMessageCallback(MessageCallback cb)
    { messageCallback_ = cb; }

    void setWriteCompleteCallback(WriteCompleteCallback cb)
    { writeCompleteCallback_ = cb; }

    void setCloseCallback(CloseCallback cb)
    { closeCallback_ = cb; }

    const std::string &getName() const
    { return name_; }

    void setName(const std::string &name_)
    { TcpConnection::name_ = name_; }

private:
    //Buffer inputBuffer_;
    //Buffer outputBuffer_;

    enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };

    MessageCallback messageCallback_;
    CloseCallback closeCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    ConnectionCallback connectionCallback_;


private:
    std::string name_;

    //readCallback readCallBack_;
    //writeCallback writeCallBack_;
    //closeCallback closeCallBack_;
    //errorCallback errorCallBack_;
};


#endif //SNL_NET_TCPCONNECTION_H
