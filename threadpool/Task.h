 ///
 /// @file    Task.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-05-12 09:59:20
 ///
 
#ifndef __WD_TASK_H__
#define __WD_TASK_H__

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;


class Task
{
public:
	void execute()
	{
		::srand(time(NULL));
		int number = ::rand() % 100;
		cout << "produce a number: " << number << endl;
		sleep(1);
	}
};


#endif
