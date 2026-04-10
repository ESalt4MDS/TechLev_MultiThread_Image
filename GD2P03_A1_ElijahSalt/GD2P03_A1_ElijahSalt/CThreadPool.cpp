#include "CThreadPool.h"

CThreadPool::CThreadPool()
{
	m_numThreads = std::thread::hardware_concurrency();
	m_tasksProcessed = 0;
	for (unsigned int i = 0; i < m_numThreads; i++)
	{
		m_threads.push_back(std::thread(&CThreadPool::WorkerThread, this));
	}
}

CThreadPool::~CThreadPool()
{
	/*for (int i = 0; i < m_numThreads; i++)
	{
		m_threads[i].join();
	}
	m_finished = true;*/

	Stop();
}

void CThreadPool::Submit(CTask _task)
{
	m_taskQueue.Push(_task);
}

void CThreadPool::Stop()
{
	m_finished = true;
	m_taskQueue.UnblockAll();
	for (unsigned int i = 0; i < m_numThreads; i++)
	{
		if (m_threads[i].joinable())
		{
			m_threads[i].join();
		}
	}
}

int CThreadPool::TasksProcessed()
{
	return m_tasksProcessed;
}

void CThreadPool::WorkerThread()
{
	CTask task;
	while (!m_finished)
	{
		if (m_taskQueue.BlockPop(task))
		{
			task.DoWork();
			m_tasksProcessed++;
		}
	}
}
