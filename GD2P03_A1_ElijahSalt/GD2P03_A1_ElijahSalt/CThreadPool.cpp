#include "CThreadPool.h"

CThreadPool::CThreadPool(int _threadCount) : m_threadCount(_threadCount)
{
	m_tasksDone = 0;
	for (int i = 0; i < m_threadCount; i++)
	{
		m_threads.push_back(std::thread(&CThreadPool::WorkerThread, this));
	}
}

CThreadPool::~CThreadPool()
{
	Stop();
}

void CThreadPool::Start()
{
	m_finished = false;
}

void CThreadPool::Stop()
{
	m_finished = true;
	m_taskQueue.UnblockAll();
	for (int i = 0; i < m_threadCount; i++)
	{
		if (m_threads[i].joinable())
		{
			m_threads[i].join();
		}
	}
}

int CThreadPool::TasksDone()
{
	return m_tasksDone;
}

int CThreadPool::GetNumTasks()
{
	return m_taskQueue.Count();
}

void CThreadPool::WorkerThread()
{
	while (!m_finished)
	{
		std::function<void()> task;
		if (m_taskQueue.BlockPop(task))
		{
			task();
			m_tasksDone++;
		}
	}
}

