#pragma once
#include <chrono>
#include <thread>
class CTask
{
public:

	CTask() :m_data(0) {}
	CTask(int _data) :m_data(_data) {}
	~CTask();

	virtual void operator()()
	{
		DoWork();
	}

	virtual void DoWork()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((rand() % 100) + 50));
		printf("Task %i complete\n", m_data);
	}

private:

	int m_data;

};

