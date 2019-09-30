#include <windows.h>
#include <iostream>
#include "UniqueLock.h"
#include "Thread.h"
#define THREADCOUNT 2

int j = 0;

#define MAX 10

struct Dec : public Thread
{
private:
	Mutex m_mtx;
public:
	void Run()
	{
		for (int i = 0; i < MAX; ++i)
		{
			UniqueLock lock(&m_mtx);
			j--;
			printf("Thread %d j = %d\n",
				GetCurrentThreadId(), j);
		}
	}
};

struct Inc : public Thread
{
private:
	Mutex m_mtx;
public:
	void Run()
	{
		for (int i = 0; i < MAX; ++i)
		{
			UniqueLock lock(&m_mtx);
			j++;
			printf("Thread %d j = %d\n",
				GetCurrentThreadId(), j);
		}
	}
};

int main(void)
{
	Thread* aThread[] =
	{
		new Inc, new Dec
	};

	aThread[0]->Start();
	aThread[1]->Start();

	aThread[0]->Join();
	aThread[1]->Join();

	std::cout << "j = " << j << '\n';

	for (int i = 0; i < THREADCOUNT; ++i) delete aThread[i];
	return 0;
}