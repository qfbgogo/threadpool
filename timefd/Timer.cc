 ///
 /// @file    Timer.cc
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-15 16:46:25
 ///
#include "Timer.h"
#include <errno.h>
#include <unistd.h>
#include <poll.h>
#include <sys/timerfd.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
namespace wd
{
Timer::Timer(int initTime,int intervalTime,TimerCallBack cb)
:_initTime(initTime)
,_intervalTime(intervalTime)
,_fd(creatTimerfd())
,_cb(cb)
,_isStarted(false)
{
}
Timer::~Timer()
{
	if(_isStarted)
		stop();
}
int Timer::creatTimerfd()
{
	int fd=timerfd_create(CLOCK_REALTIME,0);
	if(-1==fd)
	{
		perror("error timerfd_create");
	}
	return fd;
} 
void Timer::setTimerfd(int initTime,int intervalTime)
{
	struct itimerspec value;
	value.it_value.tv_sec=initTime;
	value.it_value.tv_nsec=0;
	value.it_interval.tv_sec=intervalTime;
	value.it_interval.tv_nsec=0;
	int ret=timerfd_settime(_fd,0,&value,NULL);
	if(-1==ret)
	{
		perror("error timerfd_settime");
	}
}
void Timer::start()
{
	_isStarted=true;
	setTimerfd(_initTime,_intervalTime);
	struct pollfd pfd;
	pfd.fd=_fd;
	pfd.events=POLLIN;
	while(_isStarted)
	{
		int nready=poll(&pfd,1,5000);
		if(-1==nready)
		{
			if(errno==EINTR)
				continue;
			perror("poll error");
		}else if(0==nready){
			cout<<">poll timeout"<<endl;
		}else{
			if(pfd.fd==_fd&&pfd.events==POLLIN)
			{
				//对定时器作超时处理
				handleRead();
				if(_cb)
					_cb();
			}
		}
	}
}
void Timer::stop()
{
	if(_isStarted)
	{
		setTimerfd(0,0);
		_isStarted=false;
		cout<<"Timer::stop()"<<endl;
		return;
	}
}
void Timer::handleRead()
{
	uint64_t howmany;
	int ret=read(_fd,&howmany,sizeof(howmany));
	if(ret!=sizeof(howmany))
	{
		perror("read error");
	}
}
}//end of namespase wd
