#ifndef LockQueue_H
#define LockQueue_H
#include "Mutex.h"
#include "Condition.h"
#include <queue>
#include <utility>

template<typename T>
class LockQueue
{
public:
	LockQueue()
	: mutex_(),
	  cond_(mutex_),
	  queue_()
	{
	}
	void Push(const T& t)
	{
		//std::cout<<"Push"<<std::endl;
		MutexLock lock(mutex_);
		queue_.push(t);
		cond_.Notify();
	}

	void Push(const T&& t)
	{
		MutexLock lock(mutex_);
		queue_.push(std::move(t));
		cond_.Notify();
	}

	T Pop()
	{
		MutexLock lock(mutex_);
		while(queue_.empty())
		{
			cond_.Wait();
		}

		T t = queue_.front();
		queue_.pop();
		return t;
	}
	size_t Size()const
	{
		MutexLock lock(mutex_);
		return queue_.size();
	}
private:

mutable Mutex mutex_;
Condition cond_;
std::queue<T> queue_;

};

#endif /*LockQueue_H*/