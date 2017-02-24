#include "Condition.h"
#include "Thread.h"
#include <iostream>
#include <queue>
#include "LockQueue.h"

LockQueue<int> g_queue;

void threadFuncadd()
{
	 std::cout<<"threadFuncadd"<<std::endl;
	for (int i = 0; i < 100; ++i)
	{
		g_queue.Push(i);
		sleep(11);
	}
}

void threadFuncPop()
{
	while(1)
	{
		int t = g_queue.Pop();
		std::cout<<"[threadID:] "<<detail::GetTid()<<" : "<<t<<"[queue size:]"<<g_queue.Size()<<std::endl;

	}
}
int main(int argc, char const *argv[])
{
	Thread thadd(threadFuncadd);
	thadd.Start();
	Thread thpop1(threadFuncPop);
	thpop1.Start();
	Thread thpop2(threadFuncPop);
	thpop2.Start();
	thadd.Join();
	thpop1.Join();
	thpop2.Join();
	return 0;
}