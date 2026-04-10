#pragma once
#include <queue>
#include <atomic>
#include <mutex>

template <typename T>
class CWorkQueue
{
public:

	CWorkQueue() {}
	~CWorkQueue() {}

	void Push(const T& _item)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.push(_item);
		m_cv.notify_one();
	}
	bool Pop(T& _item);

	bool BlockPop(T& _item)
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		m_cv.wait(lock, [this] {
			return (m_queue.empty() == false || m_escape);
			});

		if (!m_escape)
		{
			_item = std::move(m_queue.front());
			m_queue.pop();
		}

		return !m_escape;
	}
	void UnblockAll()
	{
		m_escape = true;
		m_cv.notify_all();
	}
	int Count() const;

private:

	std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_cv;
	std::atomic_bool m_escape;

};

