 ///
 /// @file    Buffer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-05-10 10:54:21
 ///
 
#include "Buffer.h"
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
Buffer::Buffer(size_t sz)
: _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
, _sz(sz)
, _flag(true)
{}

bool Buffer::full()
{
	return _sz == _que.size();
}

bool Buffer::empty()
{
	return _que.empty();
}

//生产者线程要做的事
void Buffer::push(const ElemType & elem)
{
	MutexLockGuard guard(_mutex);//即使发生异常退出，也能正常解锁
	while(full())  //将if换成while, 可以避免异常唤醒
		_notFull.wait();//如果缓冲区已满，要等待_notFull的条件
	_que.push(elem);//如果缓冲区中有空闲空间，则将生产的数据添加进去

	_notEmpty.notify();//添加完之后，通知消费者取数据

}

//消费者要做的事
ElemType Buffer::pop()
{
	MutexLockGuard guard(_mutex);
	//_mutex.lock();//先加锁
	while(_flag && empty())
		_notEmpty.wait();//如果缓冲区没有数据，则等待生产者添加数据
	
	if(_flag)
	{
		ElemType tmp = _que.front();//当缓冲区中有数据时，才去取数据
		_que.pop();
		_notFull.notify();//通知生产者线程，缓冲区中有空闲空间
		return tmp;
	}else
		return NULL;
}

void Buffer::wakeup()
{
	_flag = false;
	_notEmpty.notifyall();
}

}//end of namespace wd
