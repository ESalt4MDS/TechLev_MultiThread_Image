#pragma once
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
		
	}

private:

	int m_data;

};

