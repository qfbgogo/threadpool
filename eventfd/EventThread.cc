 ///
 /// @file    EventThread.cc
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-15 20:50:15
 ///
#include "EventThread.h"
#include <iostream>
using std::cout;
using std::endl;
namespace wd
{
EventThread::EventThread(EventCallBack cb)
:_event(cb)
,_thread(std::bind(&Event::start,&_event))
{
}
void EventThread::start()
{
	_thread.start();
}
void EventThread::stop()
{
	cout<<"EventThread::stop()"<<endl;
	_event.stop();
	_thread.join();
}
void EventThread::wakeup()
{
	_event.wakeup();
}
}//end of namespace wd
