 /// @file    testEvent.cc
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-15 21:00:43
 ///
#include "EventThread.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;
using namespace wd;
class Producer
{
	public:
		void make()
		{
			srand(time(NULL));
			int number=rand()%100;
			cout<<"Produce a number: "<<number<<endl;
		}
};
int main()
{
	EventThread event(std::bind(&Producer::make,Producer()));
	event.start();
	int loop=20;
	while(loop--)
	{
		event.wakeup();
		sleep(1);
	}
	event.stop();
	return 0;
}
