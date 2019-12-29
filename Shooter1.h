#pragma once
#include "Shooter.h"
class CShooter1 :
	public CShooter
{
public:
	CShooter1(int heigth);
	virtual ~CShooter1();
	virtual void Draw(Gdiplus::Graphics& gh) override;

	// 处理鼠标消息
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnLButtonUp(UINT nFlags, CPoint point) override;
	virtual bool OnRButtonDown(UINT nFlags, CPoint point) override;

	virtual bool OnMouseMove(UINT nFlags, CPoint point) override;
private:
	// 梯子的高度
	int m_nHeight = 1024;
	// 0：梯子 1：右 2：右回头 3：左 4：左回头 5：粉刷
	int m_status = 1;
	//  前一次的状态
	int m_statusLast = 1;
	PointF m_mousePos{ 0,0 };
	PointF m_mousePosLast{ 0,0 };

	//鼠标上下移动，忍者也跟着移动
	// 这里记录上次换腿时的位置和需要换腿的纵向距离
	PointF m_lastChangePos{ 0,0 };

	// 变化的距离
	const float m_distanceChange = 23.0f;
	int m_iColorIndex = 0;

	//梯子的图片
	Image *m_img0;
	Image *m_img1;
	Image *m_img2;
	Image *m_img3;
	Image *m_img4;
	Image *m_img5;
};

