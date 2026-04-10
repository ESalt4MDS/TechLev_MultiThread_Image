#pragma once
#include <vector>
#include <thread>
#include "CTask.h"
#include "CWorkQueue.h"

class CThreadPool
{
public:

	CThreadPool();
	~CThreadPool();

	void Submit(CTask _task);
	void Stop();

	int TasksProcessed();

private:

	void WorkerThread();

	std::vector<std::thread> m_threads;
	CWorkQueue<CTask> m_taskQueue;

	std::atomic_bool m_finished;
	std::atomic_int m_tasksProcessed;
	unsigned int m_numThreads;

};

