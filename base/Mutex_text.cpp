#include <iostream>
#include <vector>
#include <functional>
#include "Mutex.h"
#include "Thread.h"

Mutex g_mutex;
std::vector<int> g_vec;
int g_cout = 0;
void func()
{
	std::cout<<detail::GetTid()<<std::endl;
	for (int i = 0; i < 10000* 10000; ++i)
	{
		MutexLock mutex(g_mutex);
		g_vec.push_back(i);
		g_cout++;
	}
}

int main(int argc, char const *argv[])
{
	std::vector<Thread*> vthread;
	for (int i = 0; i < 20; ++i)
	{
		vthread.push_back(new Thread(std::bind(func)));
		vthread.back()->Start();
	}
	for (int i = 0; i < 20; ++i)
	{
		vthread[i]->Join();
	}
	// for(int i = 0;i<5;i++)
	// {
	// 	delete vthread[i];
	// }
	std::cout<<g_cout<<std::endl;
	return 0;
}