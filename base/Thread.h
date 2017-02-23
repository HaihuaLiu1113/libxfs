#include <pthread.h>
#include <functional>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/syscall.h>
#include <exception>

namespace detail
{
	struct ThreadData;
	pid_t GetTid();
	void* ThreadRun(void* arg);
}

class Thread
{
public:
	typedef std::function<void (void)> ThreadFunc;

	enum THREADSTATUS
	{
		THREAD_STATUS_NEW = 0,
		THREAD_STATUS_RUNNING,
		THREAD_STATUS_END
	};

	Thread(ThreadFunc func);
	~Thread();

	void Start();
	pid_t GetTid();
	void Join();
	int GetStatus();

private:

	pthread_t pth_;
	std::shared_ptr<pid_t> tid_;
	int threadStatus_;
	ThreadFunc callBack_;
};