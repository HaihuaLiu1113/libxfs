#include <bits/pthreadtypes.h>
#include <assert.h>
class Mutex
{
public:
	Mutex()
	{
		pthread_mutex_init(&mutex_, NULL);
	}
	~Mutex()
	{
		int ret = pthread_mutex_destroy(&mutex_);
		assert(ret == 0);
	}

	void lock()
	{
		 int ret = pthread_mutex_lock(&mutex_);
		 assert(ret == 0);
	}

	void unlock()
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
		mutex_.lock();
	}

	~MutexLock()
	{
		mutex_.unlock();
	}
private:
	Mutex& mutex_;
};