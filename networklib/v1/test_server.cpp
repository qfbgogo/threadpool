
#include "SocketUtil.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include "Acceptor.h"
#include "TcpConnection.h"

#include <string>
using std::string;

int main(int argc, char const *argv[])
{

	wd::InetAddress addr("192.168.23.129", 9999);
	wd::Acceptor acceptor(wd::createSocketFd(), addr);
	acceptor.ready();

    int peerfd = acceptor.accept();
	wd::TcpConnection conn(peerfd);
	conn.send("welcom to chat server!");

    while(1)
    {
		string msg = conn.receive();
		conn.send(msg);
    }
    return 0;
}
