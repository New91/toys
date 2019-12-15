#pragma once
class IMouseAction
{
public:
	IMouseAction();
	virtual ~IMouseAction();
	virtual bool OnLButtonUp(UINT nFlags, CPoint point);
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	virtual bool OnLButtonDbClk(UINT nFlags, CPoint point);
	virtual bool OnRButtonDown(UINT nFlags, CPoint point);
	virtual bool OnRButtonUp(UINT nFlags, CPoint point);
	virtual bool OnRButtonDbClk(UINT nFlags, CPoint point);
	virtual bool OnMouseMove(UINT nFlags, CPoint point);
};

