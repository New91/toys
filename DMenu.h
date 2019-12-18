#pragma once
#include "MenuItem.h"
#include "IMouseAction.h"

class CDMenu:
public IDrawable, public IMouseAction
{
public:
	CDMenu(HWND hWnd);
	virtual ~CDMenu();

	// 重新初始化各菜单子项及位置信息
	void InitAnimateInfo0();

	// 根据自己当前的属性画自己
	virtual void Draw(Gdiplus::Graphics &gh);

	///处理鼠标消息，若不处理返回false
	//鼠标左键按下
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnMouseMove(UINT nFlags, CPoint point) override;
private:
	HWND m_hWnd;
	// 菜单子项
	// 盒子
	std::shared_ptr<CMenuItem> m_box;
	std::shared_ptr<CMenuItem> m_cover;
	std::shared_ptr<CMenuItem> m_cover2;
	std::shared_ptr<CMenuItem> m_item0;
	std::shared_ptr<CMenuItem> m_item1;
	std::shared_ptr<CMenuItem> m_item2;
	std::shared_ptr<CMenuItem> m_item3;

	//结束动画播放
	void EndAnimate();

	typedef enum
	{
		EStatusOverCover1,
		EStatusItem0,
		EStatusItem1,
		EStatusItem2,
		EStatusItem3,
		EStatusOverCover2,
		EStatusAll,
	}EStatus;

	EStatus m_eStatus{ EStatusOverCover1 };
};

