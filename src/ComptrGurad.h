#pragma once

#pragma warning(push)
#pragma warning(disable:6387)
#include <Shlobj.h>
#pragma warning(pop)

template <class Interface, const IID* InterfaceId = &__uuidof(Interface)>
class ComptrGurad
{
public:
	ComptrGurad()
		: ptr_(NULL)
	{ }

	~ComptrGurad()
	{
		if (ptr_) ptr_->Release();
	}

	HRESULT query(IUnknown* source)
	{
		return source->QueryInterface(*InterfaceId, (void**)&ptr_);
	}

	const Interface* operator ->() const
	{
		return ptr_;
	}

	Interface* operator ->()
	{
		return ptr_;
	}

	const Interface* get() const
	{
		return ptr_;
	}

	Interface* get()
	{
		return ptr_;
	}

private:
	ComptrGurad(ComptrGurad&);
	ComptrGurad& operator=(ComptrGurad&);

private:
	Interface* ptr_;
};
