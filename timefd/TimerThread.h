 ///
 /// @file    TimerThread.h
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-15 17:21:11
 ///
#ifndef __WD_TIMETHREAD_H__
#define __WD_TIMERTHRED_H__
#include "Thread.h"
#include "Timer.h"
namespace wd
{
class TimerThread
{
	private:
		Timer _timer;
		Thread _thread;
	public:
		typedef function<void()> TimerCallBack;
		TimerThread(int initTime,int intervalTime,TimerCallBack cb);
		void start();
		void stop();
};
}//end of namespace wd
#endif
