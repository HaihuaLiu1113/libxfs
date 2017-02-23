#include "Thread.h"
#include <iostream>
namespace detail
{
	struct ThreadData
	{
		typedef Thread::ThreadFunc ThreadFunc;
		ThreadData(std::shared_ptr<pid_t> tid,ThreadFunc func):wkptr_(tid),
									callback_(func)
		{
		}

		std::weak_ptr<pid_t> wkptr_;
		ThreadFunc callback_;
	};

	pid_t GetTid()
	{
		return syscall(SYS_gettid);
	}

	void* ThreadRun(void* arg)
	{
		pid_t tid = getpid();
		ThreadData* data = static_cast<ThreadData*>(arg);
		try
		{
			std::shared_ptr<pid_t> threadId = data->wkptr_.lock();
			if (threadId)
			{
				*threadId = tid;
				threadId.reset();
			}
			data->callback_();
		}
		catch(const std::exception& ex)
		{
			fprintf(stderr, "ex.what: %s\n", ex.what());
		}
		delete data;
		return NULL;
	}
}


void Thread::Start()
{
	threadStatus_ = Thread::THREAD_STATUS_RUNNING;
	detail::ThreadData* data = new detail::ThreadData(tid_, callBack_);
	pthread_create(&pth_, NULL, &detail::ThreadRun,data);
}

pid_t Thread::GetTid()
{
	return *tid_;
}


Thread::Thread(ThreadFunc func):tid_(std::make_shared<pid_t>(0)),
					callBack_(func)
						
{
}

void Thread::Join()
{
	pthread_join(pth_, NULL);
}

Thread::~Thread()
{
	threadStatus_ = Thread::THREAD_STATUS_END;
	pthread_detach(pth_);
}

int Thread::GetStatus()
{
	return threadStatus_;
}