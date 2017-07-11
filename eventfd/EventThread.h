 ///
 /// @file    EventThread.h
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-15 20:39:15
 ///
#ifndef __WD_EVENTTHREAD_H__
#define __WD_EVENTTHREAD_H__
#include "Thread.h"
#include "Event.h"
namespace wd
{
class EventThread
{
	public:
		typedef function<void()> EventCallBack;
		EventThread(EventCallBack cb);
		void start();
		void stop();
		void wakeup();
	private:
		Event _event;
		Thread _thread;
};
}//end of namespace wd
#endif
