#include "stdafx.h"
#include "Shooter2.h"
#include "Shooter2Mark.h"


CShooter2::CShooter2()
{
	m_img0 = Image::FromFile(_T("res/The Toolbox01.png"));
	m_img1 = Image::FromFile(_T("res/The Toolbox02.png"));
	m_img2 = Image::FromFile(_T("res/The Toolbox03.png"));
}


CShooter2::~CShooter2()
{
}

// ˳ʱ����ת��ͼ
void DrawImageRotate(PointF mousePt, Graphics &gh, Image* img, float degree)
{
	//��ת��ͼ ƽ��
	PointF center = mousePt;
	center.X += img->GetWidth() / 2.0f;
	center.Y += img->GetHeight() / 2.0f;

	gh.TranslateTransform(center.X, center.Y);
	gh.RotateTransform(degree);
	gh.TranslateTransform(-center.X, -center.Y);

	ON_SCOPE_EXIT([&]()
	{
		//��������任�������Ƿ��㹻
		// �ƶ������ĵ�
		gh.TranslateTransform(center.X, center.Y);
		gh.RotateTransform(-degree);
		gh.TranslateTransform(-center.X, -center.Y);
	});

	{
		RectF rc;
		rc.X = mousePt.X;
		rc.Y = mousePt.Y;
		rc.Width = (float)img->GetWidth();
		rc.Height = (float)img->GetHeight();
		gh.DrawImage(img, rc);
	}
}
void CShooter2::Draw(Gdiplus::Graphics& gh)
{
	switch(m_status)
	{
		//����
	case EStatus::EStatusHammer:
		{
		Image * img;
			switch(m_eStatusHammer)
			{
			case EStatusHammer::EStatusHammerDownFirst:
				{
				g_game->Append(std::make_shared<CShooter2Mark>(m_mousePos.X, m_mousePos.Y));
				m_eStatusHammer = EStatusHammer::EStatusHammerDown;
				}
			case EStatusHammer::EStatusHammerDown:
			{
				img = m_img1;
			}
			case EStatusHammer::EStatusHammerUp:
				{
				img = m_img2;
				RectF rc;
				rc.X = m_mousePos.X;
				rc.Y = m_mousePos.Y;
				rc.Width = (float)img->GetWidth();
				rc.Height = (float)img->GetHeight();
				gh.DrawImage(img, rc);
				break;
				}
			default:
				{
				assert(false);
				break;
				}
			}
			break;
		}
	default:
		break;
	}
}

bool CShooter2::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch(m_status)
	{
	case EStatus::EStatusHammer:
		{
		m_eStatusHammer = EStatusHammer::EStatusHammerDownFirst;
		break;
		}
	case EStatus::EStatusSaw:
		{
		m_eStatusSaw = EStatusSaw::EStatusSawStart;
		m_sawPos = m_mousePos;
		break;
		}
	default:
		break;
	}
	return false;
}

bool CShooter2::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (m_status)
	{
	case EStatus::EStatusHammer:
	{
		m_eStatusHammer = EStatusHammer::EStatusHammerUp;
		break;
	}
	case EStatus::EStatusSaw:
	{
		m_eStatusSaw = EStatusSaw::EStatusSawStop;
		m_sawPos = m_mousePos;
		break;
	}
	default:
		break;
	}
	return false;
}

bool CShooter2::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_status = EStatus::EStatusHammer;
	return true;
}

float distance(PointF  pt1, PointF pt2)
{
	return std::sqrt(std::pow(pt1.X - pt2.X, 2) + std::pow(pt1.Y - pt2.Y, 2));
}
bool CShooter2::OnMouseMove(UINT nFlags, CPoint point)
{
	m_mousePos.X = (float)point.x;
	m_mousePos.Y = (float)point.y;

	switch(m_status)
	{
	case EStatus::EStatusHammer:
		{
		break;
		}
	case EStatus::EStatusSaw:
		{
			if(m_eStatusSaw == EStatusSaw::EStatusSawStop)
			{
				m_sawPos = m_mousePos;
				if(distance(m_mousePosLast, m_mousePos) > 10)
				{
					//����Ƕ�
					float theta = (atan2(m_mousePos.Y - m_mousePosLast.Y,
						m_mousePos.X - m_mousePosLast.X));
					if(theta < 0.0f)
					{
						theta = PI(2.0f) + theta;
					}
					m_sawDegree = Radian2Degree(theta);
				}
			}
		break;
		}
	default:
		break;
	}
	
	return true;
}
