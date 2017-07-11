 ///
 /// @file    Event.h
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-15 19:47:08
 ///
#ifndef __WD_EVENT_H__
#define __WD_EVENT_H__
#include "Noncopyable.h"
#include <functional>
using std::function;
namespace wd
{
class Event
:private Noncopyable
{
	public:
		typedef function<void()> EventCallBack;
		Event(EventCallBack cb);
		~Event();
		void start();
		void stop();
		void handleRead();
		void wakeup();
	private:
		int createEventfd();
	private:
		int _fd;
		int _isStarted;
		EventCallBack _cb;
};
}//end of namespace wd
#endif
