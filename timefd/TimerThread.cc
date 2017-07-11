 ///
 /// @file    TimerThread.cc
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-15 17:29:18
 ///
#include "TimerThread.h"
#include <iostream>
using std::cout;
using std::endl;
namespace wd
{
TimerThread::TimerThread(int initTime,int intervalTime,TimerCallBack cb)
:_timer(initTime,intervalTime,cb)
,_thread(std::bind(&Timer::start,&_timer))
{
}
void TimerThread::stop()
{
	cout<<"TimerThread stop"<<endl;
	_timer.stop();
	_thread.join();
}
void TimerThread::start()
{
	_thread.start();
}
}//end of namespace wd
