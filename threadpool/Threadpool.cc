 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-05-10 15:25:49
 ///
 
#include "Threadpool.h"
#include "Thread.h"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

Threadpool::Threadpool(size_t buffsize, size_t threadNum)
: _buffsize(buffsize)
, _threadNum(threadNum)
, _buffer(_buffsize)
, _isExit(false)
{}

Threadpool::~Threadpool()
{
	if(!_isExit)
		stop();
}

void Threadpool::start()
{
	for(size_t idx = 0; idx != _threadNum; ++idx)
	{
		shared_ptr<Thread> sp(new Thread(std::bind(&Threadpool::threadFunc, this)));
		_threads.push_back(sp);
		sp->start();
	}
}

void Threadpool::stop()
{
	cout << "Threadpool::stop()" << endl;
	if(!_isExit)
	{
		while(!_buffer.empty())
		{
			sleep(1);//等待缓冲区中的任务执行结束
		}

		_isExit = true;//将线程池退出标志位设置为true
		_buffer.wakeup();//如果没有这一个方法，每个子线程都阻塞在getTask方法上，
						 //从而导致主线程阻塞在join()方法之上

		for(auto & elem : _threads)
		{
			elem->join();
		}
	}
}

void Threadpool::addTask(Task task)
{
	_buffer.push(task);
}

Threadpool::Task Threadpool::getTask()
{
	return _buffer.pop();
}

//如果缓冲区中没有任务时，所有的子线程都会阻塞在getTask方法之上,
//无法回到while开头,即使将_isExit设置为true之后，每个线程也不会
//正常退出
void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		Task task = getTask();
		if(task)
			task();
	}
}

}// end of namespace wd
