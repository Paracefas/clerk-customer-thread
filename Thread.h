#pragma once
#include <Windows.h>
#include <process.h>

struct IRunnable
{
	virtual void Run() = 0;
};

class Thread : public IRunnable
{
	HANDLE m_handle;
	static unsigned int __stdcall call(void*);
public:
	Thread();
	virtual ~Thread();
	unsigned GetId();
	virtual void Run() = 0;
	void Join();
	void Start();
};