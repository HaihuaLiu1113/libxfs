#include "Thread.h"
#include "Singleton.h"
#include <iostream>
#include <vector>
using namespace std;
class MyClass
{
	public:
		MyClass()
		{
			cout<<" MyClass()"<<endl;
		}
		~MyClass()
		{
			cout<<"~MyClass()"<<endl;
		}
		void set(int a){a_ = a;}
		int get(){return a_;}
	private:
		int a_;

};
void run(int a)
{
	Singleton<MyClass>::GetInstance()->set(a);
	cout<<"[threadID]"<<detail::GetTid()<<"  "<<Singleton<MyClass>::GetInstance()->get()<<endl;
}
int main(int argc, char const *argv[])
{

	std::vector<Thread*> vec;
	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(new Thread(bind(run,i)));
		vec[i]->Start();
	}

	for (int i = 0; i < 10; ++i)
	{
		vec[i]->Join();
	}

	return 0;
}