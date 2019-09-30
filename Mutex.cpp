#include "Mutex.h"

#ifdef DEBUG
#include <iostream>
#endif

Mutex::Mutex()
{
	m_handle = (HANDLE)CreateMutex(NULL, FALSE, NULL);
}

Mutex::~Mutex()
{
	if(m_handle) ReleaseMutex(m_handle);
}

void Mutex::Lock()
{
	if(m_handle) WaitForSingleObject(m_handle, INFINITY);
#ifdef DEBUG
	std::cout << "Lock\n";
#endif

}

void Mutex::Unlock()
{
	if(m_handle) ReleaseMutex(m_handle);
#ifdef DEBUG
	std::cout << "Unlock\n";
#endif 
}
