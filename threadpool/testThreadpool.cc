 ///
 /// @file    testThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-05-09 16:14:59
 ///


#include "Threadpool.h"
#include "Task.h"
#include <functional>


int main(void)
{
	wd::Threadpool threadpool(10, 4);
	threadpool.start();

	size_t cnt = 20;
	while(cnt--)
	{
		threadpool.addTask(std::bind(&Task::execute, Task()));
	}
	threadpool.stop();
	return 0;
}
