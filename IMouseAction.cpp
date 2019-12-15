#include "stdafx.h"
#include "IMouseAction.h"


IMouseAction::IMouseAction()
{
}


IMouseAction::~IMouseAction()
{
}

bool IMouseAction::OnLButtonUp(UINT nFlags, CPoint point)
{
	return false;
}

bool IMouseAction::OnLButtonDown(UINT nFlags, CPoint point)
{
	return false;
}

bool IMouseAction::OnLButtonDbClk(UINT nFlags, CPoint point)
{
	return false;
}

bool IMouseAction::OnRButtonDown(UINT nFlags, CPoint point)
{
	return false;
}

bool IMouseAction::OnRButtonUp(UINT nFlags, CPoint point)
{
	return false;
}

bool IMouseAction::OnRButtonDbClk(UINT nFlags, CPoint point)
{
	return false;
}

bool IMouseAction::OnMouseMove(UINT nFlags, CPoint point)
{
	return false;
}
