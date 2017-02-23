#include "Thread.h"
#include <iostream>
using namespace std;
void run(int a)
{
	cout<<detail::GetTid()<<endl;
	cout<<"run a thread "<< a <<endl;
}
int main(int argc, char const *argv[])
{
	Thread th(bind(run,10));
	th.Start();

	th.Join();
	//cout<<th.GetTid()<<" thread is running"<<endl;
	return 0;
}