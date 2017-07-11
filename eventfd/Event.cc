 ///
 /// @file    Event.cc
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-15 19:54:51
 ///
#include "Event.h"
#include <unistd.h>
#include <poll.h>
#include <sys/eventfd.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
namespace wd
{
Event::Event(EventCallBack cb)
:_fd(createEventfd())
,_cb(cb)
,_isStarted(false)
{
}
Event::~Event()
{
	if(_isStarted)
		stop();
}
void Event::start()
{
	_isStarted=true;
	struct pollfd pfd;
	pfd.fd=_fd;
	pfd.events=POLLIN;
	while(_isStarted)
	{
		int nready=poll(&pfd,1,5000);
		if(nready==-1)
		{
			if(errno==EINTR)
				continue;
			else
				perror("poll error");
		}else if(nready==0){
			cout<<">poll timeout"<<endl;
		}else{
			handleRead();
			if(_cb)
				_cb();
		}
	}
}
void Event::stop()
{
	if(_isStarted)
		_isStarted=false;
}
int Event::createEventfd()
{
	int fd=eventfd(0,0);
	if(fd==-1)
		perror("eventfd error");
	return fd;
}
void Event::handleRead()
{
	uint64_t howmany;
	int ret=read(_fd,&howmany,sizeof(howmany));
	if(ret!=sizeof(howmany))
		perror("read error");
}
void Event::wakeup()
{
	uint64_t one;
	int ret=write(_fd,&one,sizeof(one));
	if(ret!=sizeof(one))
		perror("write error");
}
}//end of namespace wd
