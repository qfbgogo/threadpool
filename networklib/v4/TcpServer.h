 ///
 /// @file    TcpServer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2015-11-07 10:19:27
 ///

#ifndef _WD_TCPSERVER_H
#define _WD_TCPSERVER_H

#include "InetAddress.h"
#include "Acceptor.h"
#include "EpollPoller.h"

namespace wd
{

class TcpServer
{
public:
	typedef TcpConnection::TcpConnectionCallback TcpServerCallback;

	TcpServer(unsigned short port);
	TcpServer(const char * pIp, unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);

private:
	Acceptor acceptor_;
	EpollPoller epollfd_;

	TcpServerCallback onConnectionCb_;
	TcpServerCallback onMessageCb_;
	TcpServerCallback onCloseCb_;
};

}// end of namespace wd

#endif
