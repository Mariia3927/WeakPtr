#include "pch.h"
#include "Counter.h"

Counter & Counter::operator=(const Counter & counter)
{
	if (this == &counter)
		return *this;

	m_useCount = counter.m_useCount;
	m_weakCount = counter.m_weakCount;

	return *this;
}

Counter & Counter::operator=(Counter && counter)
{
	m_useCount = counter.m_useCount;
	m_weakCount = counter.m_weakCount;

	counter.m_useCount = 0;
	counter.m_weakCount = 0;

	return *this;
}

void Counter::DecrementUseCount()
{
	if (m_useCount > 0)
		--m_useCount;

	if (m_useCount == 0)
		m_weakCount = 0;
}

void Counter::DecrementWeakCount()
{
	if (m_weakCount > 0)
		--m_weakCount;
}
