#include "TcpServer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



class Task
{
public:
	void execute()
	{
		//执行具体的查询，得到结果msg之后，再交给ＩＯ线程进行发送
		
		conn->sendInLoop(msg);
	}
private:
	TcpConnectionPtr conn;
	string query;
};


void onConnection(const wd::TcpConnectionPtr &conn)
{
    printf("\n> %s has connected!\n", conn->toString().c_str());
    conn->send("hello, welcome to Chat Server.\n");
}

void onMessage(const wd::TcpConnectionPtr &conn)
{
	//1.接收客户端的数据
    std::string s(conn->receive());

	//2.根据该数据抽象出一个任务task
	//  然后将task添加到线程池threadpool中去
	//  该task由线程池完成，完成之后的处理结果
	//  再交还给IO线程(loop()循环所在的线程)
	//  发送给的客户端
	
	Task task(s, conn);//在Task之中，有一个方法execute()，
					   //当execute方法执行完任务之后，获取
					   //了要返回给客户端的数据responseMsg,
					   //在发送一定要知道是哪一个连接conn要发送
					   //数据,但是不能直接调用conn的send方法进行
					   //发送;如果这样做，就相当于直接在计算线程
					   //之中把数据发送出去了; 所以是不行的,conn
					   //连接(本身是在计算线程之中)还需要通知
					   //IO线程去发送数据
	
	threadpool.addTask(task);
}

void onClose(const wd::TcpConnectionPtr &conn)
{
    printf("> %s has closed. \n", conn->toString().c_str());
}

int main(int argc, char const *argv[])
{
	wd::TcpServer server("192.168.23.129", 9999);

    server.setConnectionCallback(&onConnection);
    server.setMessageCallback(&onMessage);
    server.setCloseCallback(&onClose);

    server.start();

    return 0;
}
