 ///
 /// @file    TcpServer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2015-11-07 10:23:57
 ///

#include "TcpServer.h"
#include "SocketUtil.h"

namespace wd
{

TcpServer::TcpServer(unsigned short port)
	: acceptor_(createSocketFd(), InetAddress(port)),
	  epollfd_(acceptor_)
{
	acceptor_.ready();
}


TcpServer::TcpServer(const char * pIp, unsigned short port)
	: acceptor_(createSocketFd(), InetAddress(pIp, port)),
	  epollfd_(acceptor_)
{
	acceptor_.ready();
}

void TcpServer::start()
{
	epollfd_.loop();
}

void TcpServer::stop()
{
	epollfd_.unloop();
}

void TcpServer::setConnectionCallback(TcpServerCallback cb)
{
	epollfd_.setConnectionCallback(cb);
}

void TcpServer::setMessageCallback(TcpServerCallback cb)
{
	epollfd_.setMessageCallback(cb);
}

void TcpServer::setCloseCallback(TcpServerCallback cb)
{
	epollfd_.setCloseCallback(cb);
}

}//end of namespace wd
