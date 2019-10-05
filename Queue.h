#pragma once
#include <stdlib.h>

template<typename T>
class Queue
{
	T* m_elements;
	size_t m_capacity;
	size_t m_count;
public:
	Queue();
	Queue(size_t capacity);
	~Queue();
	void Push(T);
	T Pop();
	bool IsEmpty();
	T First();
};

template<typename T>
inline Queue<T>::Queue()
{
	m_capacity = 10;
	m_elements = (T*)malloc(sizeof(T) * m_capacity);
	m_count = 0;
}

template<typename T>
inline Queue<T>::Queue(size_t capacity)
{
	m_capacity = capacity;
	m_elements = (T*)malloc(sizeof(T) * m_capacity);
	m_count = 0;
}

template<typename T>
inline Queue<T>::~Queue()
{
	free(m_elements);
	m_elements = NULL;
}

template<typename T>
inline void Queue<T>::Push(T element)
{
	if (m_count == m_capacity)
	{
		m_capacity *= 2;
		m_elements = (T*)realloc(m_elements, sizeof(T) * m_capacity);
	}
	m_elements[m_count] = element;
	m_count++;
}

template<typename T>
inline T Queue<T>::Pop()
{
	T element;
	element = m_elements[0];
	for (int i = 1; i < m_count; ++i)
		m_elements[i - 1] = m_elements[i];
	m_count--;
	return element;
}

template<typename T>
inline bool Queue<T>::IsEmpty()
{
	return m_count == 0;
}

template<typename T>
inline T Queue<T>::First()
{
	return m_elements[0];
}
