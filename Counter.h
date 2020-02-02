#pragma once
#include "pch.h"


class Counter
{
public:
	Counter() { }
	explicit Counter(int useCount, int weakCount = 0) : m_useCount(useCount), m_weakCount(weakCount) { }
	Counter(const Counter& counter) : m_useCount(counter.m_useCount), m_weakCount(counter.m_weakCount) { }
	Counter(Counter&& counter) : m_useCount(std::move(counter.m_useCount)), m_weakCount(std::move(counter.m_weakCount)) { }
	~Counter() { m_useCount = 0; m_weakCount = 0; }

	Counter& operator=(const Counter& counter);
	Counter& operator=(Counter&& counter);

	int GetUseCount() const { return m_useCount; }
	int GetWeakCount() const { return m_weakCount; }

	void IncrementUseCount() { ++m_useCount; }
	void DecrementUseCount();

	void IncrementWeakCount() { ++m_weakCount; }
	void DecrementWeakCount();

private:
	int m_useCount = 0;
	int m_weakCount = 0;
};

