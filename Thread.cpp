#include "Thread.h"
#include <iostream>

unsigned int __stdcall Thread::call(void* _this)
{
	((Thread*)_this)->Run();
	return 0;
}

Thread::Thread()
{
	m_handle = (HANDLE)_beginthreadex(0, 0, &call, this, CREATE_SUSPENDED, 0);
}

Thread::~Thread()
{
	if (m_handle) CloseHandle(m_handle);
}

unsigned Thread::GetId()
{
	return m_handle ? GetThreadId(m_handle) : 0;
}

void Thread::Join()
{
	if (m_handle) WaitForSingleObject(m_handle, INFINITE);
}

void Thread::Start()
{
	if (m_handle) ResumeThread(m_handle);
}
