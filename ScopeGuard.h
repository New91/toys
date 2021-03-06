#pragma once

#include  "stdafx.h"
#include <functional>

class ScopeGuard
{
public:
	explicit ScopeGuard(std::function<void()> onEixtScope)
		:onExitScope_(onEixtScope),dismissed_(false)
	{
		
	}
	~ScopeGuard()
	{
		if(!dismissed_)
		{
			onExitScope_();
		}
	}
	void Dismiss()
	{
		dismissed_ = true;
	}
private:
	std::function<void()> onExitScope_;
	bool dismissed_;
private:
	ScopeGuard(ScopeGuard const &);
	ScopeGuard &operator=(ScopeGuard const &);
};

#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT,__LINE__)(callback)