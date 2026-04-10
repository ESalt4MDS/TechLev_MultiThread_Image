#include "CWorkQueue.h"

//template<typename T>
//inline CWorkQueue<T>::CWorkQueue()
//{
//}
//
//template<typename T>
//inline CWorkQueue<T>::~CWorkQueue()
//{
//}

//template<typename T>
//inline void CWorkQueue<T>::Push(const T& _item)
//{
//	std::lock_guard<std::mutex> lock(m_mutex);
//	m_queue.push(_item);
//	m_cv.notify_one();
//}

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

//template<typename T>
//inline bool CWorkQueue<T>::BlockPop(T& _item)
//{
//	std::unique_lock<std::mutex> lock(m_mutex);
//
//	m_cv.wait(lock, [this] {
//		return (m_queue.empty() == false || m_escape);
//		});
//
//	if (!m_escape)
//	{
//		_item = std::move(m_queue.front());
//		m_queue.pop();
//	}
//
//	return !m_escape;
//}

//template<typename T>
//inline void CWorkQueue<T>::UnblockAll()
//{
//	m_escape = true;
//	m_cv.notify_all();
//}

template<typename T>
inline int CWorkQueue<T>::Count() const
{
	return 0;
}
