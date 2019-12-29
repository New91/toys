#pragma once
#include "Shooter.h"
class CShooter1 :
	public CShooter
{
public:
	CShooter1(int heigth);
	virtual ~CShooter1();
	virtual void Draw(Gdiplus::Graphics& gh) override;

	// ���������Ϣ
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnLButtonUp(UINT nFlags, CPoint point) override;
	virtual bool OnRButtonDown(UINT nFlags, CPoint point) override;

	virtual bool OnMouseMove(UINT nFlags, CPoint point) override;
private:
	// ���ӵĸ߶�
	int m_nHeight = 1024;
	// 0������ 1���� 2���һ�ͷ 3���� 4�����ͷ 5����ˢ
	int m_status = 1;
	//  ǰһ�ε�״̬
	int m_statusLast = 1;
	PointF m_mousePos{ 0,0 };
	PointF m_mousePosLast{ 0,0 };

	//��������ƶ�������Ҳ�����ƶ�
	// �����¼�ϴλ���ʱ��λ�ú���Ҫ���ȵ��������
	PointF m_lastChangePos{ 0,0 };

	// �仯�ľ���
	const float m_distanceChange = 23.0f;
	int m_iColorIndex = 0;

	//���ӵ�ͼƬ
	Image *m_img0;
	Image *m_img1;
	Image *m_img2;
	Image *m_img3;
	Image *m_img4;
	Image *m_img5;
};

