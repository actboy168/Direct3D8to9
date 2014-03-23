#pragma once

#include <Windows.h>
#include <map>
#include "SpinLock.h"
#include "ComptrGurad.h"

template <class T>
class CObjectPool
{
public:
	CObjectPool()
	{ }

	~CObjectPool()
	{ }

	template <class SourceT, class BaseT>
	T* Create(SourceT* source, BaseT* base)
	{
		T* result = nullptr;
		ComptrGurad<IUnknown> pUnknown;
		if (SUCCEEDED(pUnknown.query(source)))
		{
			CSpinLockGuard guard(mutex_);
			auto it = pool_.find(pUnknown.get());
			if (it == pool_.end())
			{
				result = new T(source, base);
				pool_.insert(std::make_pair(pUnknown.get(), result));
			}
			else
			{
				result = it->second;
				result->AddRef();
			}
		}
		else
		{
			result = new T(source, base);
		}

		return result;
	}

	template <class SourceT>
	void Destory(SourceT* source)
	{
		ComptrGurad<IUnknown> pUnknown;
		if (SUCCEEDED(pUnknown.query(source)))
		{
			CSpinLockGuard guard(mutex_);
			pool_.erase(pUnknown.get());
		}
	}

private:
	std::map<IUnknown*, T*> pool_;
	CSpinLock mutex_;
};
