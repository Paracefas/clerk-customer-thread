#include "UniqueLock.h"

UniqueLock::UniqueLock(Mutex* mtx)
{
	m_mtx = mtx;
	m_mtx->Lock();
}

UniqueLock::~UniqueLock()
{
	m_mtx->Unlock();
}
