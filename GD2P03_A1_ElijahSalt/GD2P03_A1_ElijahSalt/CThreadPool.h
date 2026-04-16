#pragma once
#include <vector>
#include <thread>
#include <atomic>
#include <future>
#include "CWorkQueue.h"

class CThreadPool
{
public:

	CThreadPool(int _threadCount);
	~CThreadPool();

	void Start();
	void Stop();

	int TasksDone();

	template <class F, class ...Args>
	auto Submit(F&& _func, Args&& ..._args);

	int GetNumTasks();

private:

	void WorkerThread();

	std::vector<std::thread> m_threads;
	CWorkQueue<std::function<void()>> m_taskQueue;

	std::atomic_bool m_finished;
	std::atomic_int m_tasksDone;
	const int m_threadCount;

};

template<class F, class ...Args>
inline auto CThreadPool::Submit(F&& _func, Args && ..._args)
{
	using return_type = decltype(_func(_args...));
	std::packaged_task<return_type()> task(std::bind(_func, _args...));

	auto taskPtr = std::make_shared<std::packaged_task<return_type()>>(std::move(task));
	m_taskQueue.Push([taskPtr]() {(*taskPtr)(); });

	std::future<return_type> future = taskPtr->get_future();
	return future;
}
