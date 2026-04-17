//************************************************************************
//Bachelor of Software Engineering
//Media Design School
//Auckland
//New Zealand
//
//File Name : [CWorkQueue.h]
//Description : [handles thread pool queues]
//Author : [Elijah Salt]
//Email : [elijah.salt@mds.ac.nz]
//
//(c) Elijah Salt
//************************************************************************

#pragma once
#include <queue>
#include <mutex>

template <typename T>
class CWorkQueue
{
public:
	CWorkQueue() {}
	~CWorkQueue() {}

	/*
	* push tasks to queue
	Parameters:

	Returns:
	- void
	*/
	void Push(const T& _item);
	bool Pop(T& _item);

	/*
	* 
	Parameters:

	Returns:
	- void
	*/
	bool BlockPop(T& _item);

	/*
	* number of tasks the pool is handling
	Parameters:

	Returns:
	- int: the number of tasks
	*/
	int Count() const;

	/*
	*
	Parameters:

	Returns:
	- void
	*/
	void UnblockAll();


private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_cv;
	std::atomic_bool m_escape;

	int m_count = 0;

};

template<typename T>
inline void CWorkQueue<T>::Push(const T& _item)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_queue.push(_item);
	m_count++;
	m_cv.notify_one();
}

template<typename T>
inline bool CWorkQueue<T>::Pop(T& _item)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (m_queue.empty())
	{
		return false;
	}
	_item = std::move(m_queue.front());
	m_queue.pop();
	return true;
}

template<typename T>
inline bool CWorkQueue<T>::BlockPop(T& _item)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_cv.wait(lock, [this] { return (m_queue.empty() == false || m_escape); });

	if (!m_escape)
	{
		_item = std::move(m_queue.front());
		m_queue.pop();
	}
	return !m_escape;
}

template<typename T>
inline int CWorkQueue<T>::Count() const
{
	return m_count;
}

template<typename T>
inline void CWorkQueue<T>::UnblockAll()
{
	m_escape = true;
	m_cv.notify_all();
}
