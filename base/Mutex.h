#ifndef Mutex_H
#define Mutex_H
#include <bits/pthreadtypes.h>
#include <assert.h>
#include <iostream>
class Mutex
{
public:
	Mutex()
	{
		int ret = pthread_mutex_init(&mutex_, NULL);
		assert(ret == 0);
	}
	~Mutex()
	{
		int ret = pthread_mutex_destroy(&mutex_);
		assert(ret == 0);
	}

	void Lock()
	{
		 int ret = pthread_mutex_lock(&mutex_);
		 assert(ret == 0);
	}

	void Unlock()
	{
		int ret = pthread_mutex_unlock(&mutex_);
		assert(ret == 0);
	}

	pthread_mutex_t* GetMutex()
	{
		return &mutex_;
	}
private:
	pthread_mutex_t mutex_;
};

class MutexLock
{
public:
	MutexLock(Mutex& mutex):mutex_(mutex)
	{
		mutex_.Lock();
	}

	~MutexLock()
	{
		mutex_.Unlock();
	}
private:
	Mutex& mutex_;
};

#endif /*Mutex_H*/