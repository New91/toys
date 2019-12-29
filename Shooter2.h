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

	// ����״̬
	enum class EStatusHammer
	{
		EStatusHammerDownFirst,
		EStatusHammerDown,
		EStatusHammerUp,
	};
	EStatusHammer m_eStatusHammer{ EStatusHammer::EStatusHammerDown };
	//���״̬
	enum class EStatusSaw{EStatusSawStart,EStatusMoving,EStatusSawStop};
	EStatusSaw m_eStatusSaw{ EStatusSaw::EStatusSawStop };
	//���������ٶ�
	float m_sawSpeed = 10.0f;
	float m_sawDegree = 0.0f;
	PointF m_sawPos{0.0f, 0.0f };
	PointF m_mousePosLast{ 0.0f,0.0f };
	PointF m_mousePos{ 0.0f, 0.0f };

	//���ߵ�ͼƬ
	Image *m_img0;
	Image *m_img1;
	Image *m_img2;

	// ����������壬��ˢ
	Gdiplus::Font m_font{ L"����", 20.0f };
	SolidBrush m_brush{ Color::Red };
};

