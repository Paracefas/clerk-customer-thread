#include <windows.h>
#include <iostream>
#include "UniqueLock.h"
#include "Thread.h"
#include "Queue.h"

void gotoxy(COORD c) 
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

struct Customer : public Thread
{
private:
	Mutex m_mtx;
public:
	enum { AWAIT_TO_BE_ATENDED, ON_SERVICE } State;
	Customer()
	{
		State = AWAIT_TO_BE_ATENDED;
	}
	void Run()
	{
		UniqueLock lock(&m_mtx);
		State = ON_SERVICE;
		std::cout << "Customer [" << GetId() << "] is on service\n";
		Sleep(1000);
		std::cout << "Customer [" << GetId() << "] leave service\n";
		State = AWAIT_TO_BE_ATENDED;
	}
};

struct Clerk : public Thread
{
private:
	Mutex m_mtx;
public:
	enum { WAIT_TO_ATTEND, ON_SERVICE } State;
	Clerk()
	{
		State = WAIT_TO_ATTEND;
	}
	void Run()
	{
		UniqueLock lock(&m_mtx);
		State = ON_SERVICE;
		std::cout << "Clerk [" << GetId() << "] is on service\n";
		Sleep(1000);
		std::cout << "Clerk [" << GetId() << "] leave service\n";
		State = WAIT_TO_ATTEND;
	}
};

class ServiceMonitor : public Thread
{
	Mutex m_OnService;
	Mutex m_C;
	Clerk** m_clerks;
	Queue<Customer*> m_Q;
	size_t m_clerksCount;
	
	void init()
	{
		m_clerks = new Clerk*[m_clerksCount];
		for (size_t i = 0; i < m_clerksCount; ++i)
			m_clerks[i] = new Clerk();
	}

public:
	ServiceMonitor()
	{
		m_clerksCount = 5;
		init();
	}
	~ServiceMonitor()
	{
		for (size_t i = 0; i < m_clerksCount; ++i)
			delete m_clerks[i];
		delete[] m_clerks;
	}
	ServiceMonitor(size_t clerksCount)
	{
		m_clerksCount = clerksCount;
		init();
	}
	void EnterToService(Clerk* clerk, Customer* customer)
	{
		m_OnService.Lock();
		clerk->Start();
		customer->Start();
	}
	void LeaveService(Clerk* clerk, Customer* customer)
	{
		delete clerk;
		delete customer;
		clerk = NULL;
		m_OnService.Unlock();
	}
	void ResetClerk(size_t i)
	{
		delete m_clerks[i];
		m_clerks[i] = new Clerk();
	}
	void Run()
	{
		while (1)
		{
			if (GetAsyncKeyState(0x43) & 0x7FFF)
			{
				m_C.Lock();

				for (size_t i = 0; i < m_clerksCount; ++i)
					std::cout << m_clerks[i]->State;
				Customer* newCustomer = new Customer();
				m_Q.Push(newCustomer);
				while (!m_Q.IsEmpty())
				{
					for (int i = 0; i < m_clerksCount; ++i)
					{
						if (m_clerks[i]->State == Clerk::WAIT_TO_ATTEND)
						{
							Customer* customer = m_Q.Pop();
							if (customer->State == Customer::AWAIT_TO_BE_ATENDED)
							{
								EnterToService(m_clerks[i], customer);
								LeaveService(NULL, NULL);
								break;
							}
						}
					}
				}
				m_C.Unlock();

			}
		}
	}
};

int main(void)
{
	Thread* monitor = new ServiceMonitor();
	monitor->Start();
	monitor->Join();
	delete monitor;
	return 0;
}