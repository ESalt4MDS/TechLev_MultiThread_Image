#pragma once
#include <queue>

template <typename T>
class CWorkQueue
{
public:

	CWorkQueue();
	~CWorkQueue();

	void Push(const T& _item);
	bool Pop(T& _item);

	void BlockPop(T& _item);
	int Count() const;

private:

	std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_cv;

};

