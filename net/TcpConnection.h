//
// Created by shiyang on 15/12/30.
//

#ifndef SNL_NET_TCPCONNECTION_H
#define SNL_NET_TCPCONNECTION_H


class TcpConnection;
typedef void (*ConnectionCallback)(const TcpConnection & conn);

//typedef void (*readCallback)(const TcpConnection & conn);
//typedef void (*writeCallback)(const TcpConnection & conn);
//typedef void (*closeCallback)(const TcpConnection & conn);
//typedef void (*errorCallback)(const TcpConnection & conn);

class TcpConnection {

public:
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

    void setConnectionCallback()
    { }

    void setMessageCallback()
    { }

    void setWriteCompleteCallback()
    { }

    void setCloseCallback()
    { }

private:
    //Buffer inputBuffer_;
    //Buffer outputBuffer_;

    enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };
    //readCallback readCallBack_;
    //writeCallback writeCallBack_;
    //closeCallback closeCallBack_;
    //errorCallback errorCallBack_;
};


#endif //SNL_NET_TCPCONNECTION_H
