 ///
 /// @file    testTimer.cc
 /// @author  lisa(1980254245@qq.com)
 /// @date    2017-05-15 17:40:49
 ///
#include "TimerThread.h"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;
class Producer
{
	public:
		void make()
		{
			srand(time(NULL));
			int number=rand()%100;
			cout<<"produce a number: "<<number<<endl;
		}
};
using namespace std;
int main()
{
	wd::TimerThread timer(1,3,bind(&Producer::make,Producer()));
	timer.start();
	sleep(30);
	timer.stop();
	return 0;
}
