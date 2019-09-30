#pragma once
#include "UniqueLock.h"

template<class T>
class monitor
{
public:
	monitor() {}
	struct monitor_helper
	{
		monitor_helper(monitor* mon) : m_mon(mon), m_ul(mon->m_lock) {}
		T* operator->() { return &m_mon->m_cl; }
		monitor* m_mon;
		UniqueLock m_ul;
	};
	monitor_helper operator->() { return monitor_helper(this); }
	monitor_helper ManuallyLock() { return monitor_helper(this); }
	T& GetThreadUnsafeAccess() { return m_cl; }
private:
	T           m_cl;
	Mutex  m_lock;
};