#pragma once

class CSpinLock
{
public:
	CSpinLock();
	CSpinLock(bool locked);
	~CSpinLock();
	bool lockable() const;
	bool try_lock();
	void unlock();
	void lock();

private:
	CSpinLock(CSpinLock&);
	CSpinLock& operator=(CSpinLock&);

private:
	volatile bool        spin_;
};

class CSpinLockGuard
{
public:
	inline explicit CSpinLockGuard(CSpinLock& l)
		: lock_(l)
	{
		lock_.lock();
	}

	inline ~CSpinLockGuard()
	{
		lock_.unlock();
	}

private:
	CSpinLockGuard(CSpinLockGuard&);
	CSpinLockGuard& operator=(CSpinLockGuard&);

private:
	CSpinLock& lock_;
};
