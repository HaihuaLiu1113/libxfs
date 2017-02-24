#ifndef Condition_H
#define Condition_H
#include <pthread.h>
#include "Mutex.h"
#include <sys/time.h>
class Condition
{
public:
	Condition(Mutex& mutex):mutex_(mutex)
	{
		//assert()
		pthread_cond_init(&cond_, NULL);
	}
	~Condition()
	{
		pthread_cond_destroy(&cond_);
	}

	void Notify()
	{
		pthread_cond_broadcast(&cond_);
	}

	void Wait()
	{
		pthread_cond_wait(&cond_, mutex_.GetMutex());
	}

	bool timedwait(int secends)
	{
		struct timeval now;
		struct timespec abstime;
		::gettimeofday(&now, NULL);
		abstime.tv_sec = now.tv_sec + secends;
		abstime.tv_nsec = now.tv_usec * 1000;
		int ret = pthread_cond_timedwait(&cond_, mutex_.GetMutex(), &abstime);
		if (ret < 0)
		{
			return -1;
		}
		return 0;
	}
private:
	Mutex& mutex_;
	pthread_cond_t cond_;
};
#endif /*Condition_H*/