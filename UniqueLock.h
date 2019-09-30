#pragma once
#include "Mutex.h"

class UniqueLock
{
	Mutex* m_mtx;
public:
	UniqueLock(Mutex*);
	~UniqueLock();
};
