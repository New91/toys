#pragma once
#include "Shooter.h"

class CShooter2 :
	public CShooter
{
public:
	CShooter2();
	virtual ~CShooter2();
	virtual void Draw(Gdiplus::Graphics& gh) override;
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnLButtonUp(UINT nFlags, CPoint point) override;
	virtual bool OnRButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnMouseMove(UINT nFlags, CPoint point) override;
private:
	enum class EStatus{EStatusHammer, EStatusSaw};
	EStatus m_status{ EStatus::EStatusHammer };

	// 锤子状态
	enum class EStatusHammer
	{
		EStatusHammerDownFirst,
		EStatusHammerDown,
		EStatusHammerUp,
	};
	EStatusHammer m_eStatusHammer{ EStatusHammer::EStatusHammerDown };
	//电锯状态
	enum class EStatusSaw{EStatusSawStart,EStatusMoving,EStatusSawStop};
	EStatusSaw m_eStatusSaw{ EStatusSaw::EStatusSawStop };
	//电锯的运行速度
	float m_sawSpeed = 10.0f;
	float m_sawDegree = 0.0f;
	PointF m_sawPos{0.0f, 0.0f };
	PointF m_mousePosLast{ 0.0f,0.0f };
	PointF m_mousePos{ 0.0f, 0.0f };

	//工具的图片
	Image *m_img0;
	Image *m_img1;
	Image *m_img2;

	// 输出文字字体，画刷
	Gdiplus::Font m_font{ L"宋体", 20.0f };
	SolidBrush m_brush{ Color::Red };
};

