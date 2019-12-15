#pragma once
#include "IDrawable.h"
#include "IMouseAction.h"

class CShooter: public IDrawable, public IMouseAction
{
public:
	CShooter();
	virtual ~CShooter();
};

