#include <iostream>
#include "atomic.h"

using namespace std;
int main(int argc, char const *argv[])
{
	Atomic<int32_t> val;
	cout<<val.GetAndAdd(10)<<endl;
	cout<<val.AddAndGet(20)<<endl;
	cout<<val.Get()<<endl;
	cout<<val.GetAndSet(50)<<endl;
	cout<<val.Get()<<endl;
	return 0;
}