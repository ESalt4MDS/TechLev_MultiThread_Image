//************************************************************************
//Bachelor of Software Engineering
//Media Design School
//Auckland
//New Zealand
//
//File Name : [CThreadPool.h]
//Description : [handles the threads in the pool]
//Author : [Elijah Salt]
//Email : [elijah.salt@mds.ac.nz]
//
//(c) Elijah Salt
//************************************************************************

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

	/*
	* submit any type of task with any amount of variables
	Parameters:
	- F&& _func: reference to a function
	- Args&& ..._args: to a number of variables
	Returns:
	- auto: returns a future of any return type
	*/
	template <class F, class ...Args>
	auto Submit(F&& _func, Args&& ..._args);

	/*
	* the number of tasks the pool is handling
	Parameters:

	Returns:
	- int: the number of tasks
	*/
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
