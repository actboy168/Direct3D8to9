#include "SpinLock.h"

#include <Windows.h>
#include <intrin.h>

#pragma intrinsic( _InterlockedExchange8 )
#pragma intrinsic( _ReadWriteBarrier )

namespace
{
	struct CSpinLockEnableHelper
	{
		bool operator ()()
		{
			SYSTEM_INFO info;
			::GetSystemInfo(&info);
			return (info.dwNumberOfProcessors > 1);
		}
	};

	bool CSpinLockIsEnable = CSpinLockEnableHelper()();


	void CSpinLockBackoff()
	{
		if (CSpinLockIsEnable)
		{
			for (size_t n = 0; n < 16; ++n) __nop();
		}
		else
		{
			::SwitchToThread();
		}
	}
}

CSpinLock::CSpinLock()
: spin_(false)
{ }

CSpinLock::CSpinLock(bool locked)
: spin_(locked)
{ }

CSpinLock::~CSpinLock()
{ }

bool CSpinLock::lockable() const
{
	return !spin_;
}

bool CSpinLock::try_lock()
{
#pragma warning(suppress:4800)
	return !(bool)_InterlockedExchange8(reinterpret_cast<char volatile *>(&spin_), (char)true);
}

void CSpinLock::unlock()
{
	spin_ = false;
	_ReadWriteBarrier();
}

void CSpinLock::lock()
{
	for (;; CSpinLockBackoff())
	{
		if (lockable() && try_lock())
		{
			break;
		}
	}
}
