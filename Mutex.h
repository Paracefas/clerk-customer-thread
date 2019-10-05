#pragma once
#include <Windows.h>
#include <process.h>

class Mutex
{
	HANDLE m_handle;
public:
	Mutex();
	~Mutex();
	void Lock();
	void Unlock();
};