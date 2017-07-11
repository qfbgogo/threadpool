#include "SocketUtil.h"
#include "TcpConnection.h"
#include "Acceptor.h"
#include "EpollPoller.h"
#include <iostream>

using std::cout;
using std::endl;

void onConnection(const wd::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
    conn->send("hello, welcome to Chat Server.\r\n");
}

void onMessage(const wd::TcpConnectionPtr &conn)
{
    std::string s(conn->receive());
    conn->send(s);
}

void onClose(const wd::TcpConnectionPtr &conn)
{
    printf("%s close\n", conn->toString().c_str());
}

int main(int argc, char const *argv[])
{
	wd::InetAddress addr("192.168.23.129", 9999);
	wd::Acceptor acceptor(wd::createSocketFd(), addr);
	acceptor.ready();

	wd::EpollPoller poller(acceptor);
    poller.setConnectionCallback(&onConnection);
    poller.setMessageCallback(&onMessage);
    poller.setCloseCallback(&onClose);

    poller.loop();

    return 0;
}
