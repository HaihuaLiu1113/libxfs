#ifndef Atomic_H
#define Atomic_H
#include <stdint.h>
template <typename T>
class Atomic
{
public:
	Atomic():val_(0){}
	~Atomic(){}
	T Get()
	{
		return __sync_val_compare_and_swap(&val_, 0, 0);
	}

	T GetAndAdd(T t)//t++;
	{
		return __sync_fetch_and_add(&val_, t);
	}

	T AddAndGet(T t)//++t
	{
		return __sync_add_and_fetch(&val_, t);
	}

	T GetAndSet(T t)
	{
		return __sync_lock_test_and_set(&val_, t);
	}

private:
volatile T val_;
};

#endif /*Atomic_H*/