#pragma once
#include "pch.h"


template <typename T>
class WeakPtr
{
public:
	WeakPtr() {}
	WeakPtr(const WeakPtr<T>& ptr);
	WeakPtr(const std::shared_ptr<T>& ptr) : m_pointer(new T(*ptr.get())), m_counter(new Counter(ptr.use_count())) { m_counter->IncrementWeakCount(); m_shared.push_back(ptr.get()); }
	WeakPtr(WeakPtr<T>&& ptr) : m_pointer(std::move(ptr.m_pointer)), m_counter(std::move(m_counter)), m_shared(std::move(ptr.m_shared)) { }
	~WeakPtr();

	WeakPtr<T>& operator=(const WeakPtr<T>& ptr);
	WeakPtr<T>& operator=(const std::shared_ptr<T>& ptr);
	WeakPtr<T>& operator=(WeakPtr<T>&& ptr);

	T& operator->() { return m_pointer; }

	int GetUseCount() const { return m_counter != nullptr ? m_counter->GetUseCount() : 0; }
	int GetWeakCount() const { return m_counter != nullptr ? m_counter->GetWeakCount() : 0; }

	void Reset();
	bool Expired() const { return m_pointer == nullptr ? true : false; }
	std::shared_ptr<T> Lock();

private:
	void Assign(const WeakPtr<T>& ptr);
	void CheckUseCountNumber();

private:
	std::unique_ptr<T> m_pointer;
	std::unique_ptr<Counter> m_counter;
	std::vector<T*> m_shared;
};

template <typename T>
void WeakPtr<T>::Assign(const WeakPtr<T>& ptr)
{
	if (ptr.m_pointer)
	{
		m_pointer = std::make_unique<T>(*ptr.m_pointer);
	}
	if (ptr.m_counter)
	{
		m_counter = std::make_unique<Counter>(*ptr.m_counter);
		m_counter->IncrementWeakCount();
	}

	m_shared.clear();
	m_shared = ptr.m_shared;
}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr<T>& ptr) 
{ 
	Assign(ptr);
}

template <typename T>
WeakPtr<T>::~WeakPtr() 
{
	Reset();
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& ptr)
{
	if (this == &ptr)
		return *this;

	Assign(ptr);

	return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const std::shared_ptr<T>& ptr)
{
	m_pointer = std::make_unique<T>(*ptr.get());

	m_counter = std::make_unique<Counter>(ptr.use_count());
	if (m_counter)
		m_counter->IncrementWeakCount();

	m_shared.clear();
	m_shared.push_back(ptr.get());

	return *this;
}

template <typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& ptr)
{
	if (this == &ptr)
		return *this;

	m_pointer = std::move(ptr.m_pointer);
	m_counter = std::move(ptr.m_counter);
	m_shared = std::move(ptr.m_shared);

	return *this;
}

template <typename T>
void WeakPtr<T>::Reset()
{
	m_pointer.reset();
	m_counter.reset();
	m_shared.clear();
}

template <typename T>
std::shared_ptr<T> WeakPtr<T>::Lock()
{
	CheckUseCountNumber();

	if (m_counter)
	{
		m_counter->IncrementUseCount();
	}

	auto sharedPtr = std::make_shared<T>(*m_pointer.get());
	m_shared.push_back(sharedPtr.get());
	
	return sharedPtr;
}

template <typename T>
void WeakPtr<T>::CheckUseCountNumber()
{
	T value;
	if(m_pointer)
		value = *m_pointer.get();

	m_shared.erase(remove_if(m_shared.begin(), m_shared.end(), [&](T *item) {if((item && *item != value) || !item) { m_counter->DecrementUseCount(); return true; } return false; }), m_shared.end());
}

