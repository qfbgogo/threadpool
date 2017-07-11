 ///
 /// @file    Timer.h
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-15 16:34:18
 ///
#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__
#include "Noncopyable.h"
#include <functional>
using std::function;
namespace wd
{
class Timer
:private Noncopyable
{
	public:
		typedef function<void()> TimerCallBack;
		Timer(int initTime,int intervalTime,TimerCallBack cb);
		~Timer();
		void start();
		void stop();
		int creatTimerfd();
		void setTimerfd(int initTime,int intervalTime);
		void handleRead();
	private:
		bool _isStarted;
		int _fd;
		int _initTime;
		int _intervalTime;
		TimerCallBack _cb;
};
}//end of namespace wd
#endif
