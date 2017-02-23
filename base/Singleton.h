#include <pthread.h>
#include <stdlib.h>
 #include <assert.h>
template<typename T>
class Singleton
{
public:
	static T* GetInstance();

private:
	Singleton(){}
	~Singleton(){}

	static void init();
	static void Destroy_();
	static pthread_once_t onceCtrl_;
	static T* singleton_t;
};

template<typename T>
T* Singleton<T>::singleton_t = NULL;

template<typename T>
pthread_once_t Singleton<T>::onceCtrl_ = 0;

template<typename T>
T* Singleton<T>::GetInstance()
{
	pthread_once(&onceCtrl_, Singleton::init);
	assert(singleton_t != NULL);
	return singleton_t;
}

template<typename T>
void Singleton<T>::init()
{
	singleton_t = new T();
	::atexit(Destroy_);
}

template<typename T>
void Singleton<T>::Destroy_()
{
	typedef char type_must_be_complete[sizeof(T) ? 1:-1];
	(void)sizeof(type_must_be_complete);
	delete singleton_t;
	singleton_t = NULL;
}