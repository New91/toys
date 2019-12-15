#pragma once
#include "IDrawable.h"

class IMark:public IDrawable
{
public:
	IMark();
	virtual ~IMark();
	virtual bool IsChanging() const = 0;
};

