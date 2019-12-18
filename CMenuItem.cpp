#include "stdafx.h"
#include "MenuItem.h"


CMenuItem::CMenuItem()
{
}

CMenuItem::CMenuItem(float x, float y, PCTSTR szImg, PCTSTR szTips)
{
}

void CMenuItem::Draw(Gdiplus::Graphics& gh)
{
}

bool CMenuItem::OnLButtonDown(UINT nFlags, CPoint point)
{
	return false;
}

bool CMenuItem::OnRButtonDown(UINT nFlags, CPoint point)
{
	return false;
}

bool CMenuItem::OnMouseMove(UINT nFlags, CPoint point)
{
	return false;
}

void CMenuItem::StartAnimate()
{
}

void CMenuItem::InitAnimateInfo0(float x, float y, float dir)
{
}

void CMenuItem::InitAnimateInfo1(float x, float y, float dir)
{
}

void CMenuItem::InitAnimateInfoReverse()
{
}

void CMenuItem::InitAnimateInfo3(float x, float y)
{
}


CMenuItem::~CMenuItem()
{
}
