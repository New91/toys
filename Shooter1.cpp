#include "stdafx.h"
#include "Shooter1.h"
#include "Shooter1Mark.h"


CShooter1::CShooter1(int heigth):m_nHeight(heigth)
{
	m_img0 = Image::FromFile(_T("res/Pablo The Painter 00.png"));
	m_img1 = Image::FromFile(_T("res/Pablo The Painter 01.png"));
	m_img2 = Image::FromFile(_T("res/Pablo The Painter 02.png"));
	m_img3 = Image::FromFile(_T("res/Pablo The Painter 03.png"));
	m_img4 = Image::FromFile(_T("res/Pablo The Painter 04.png"));
	m_img5 = Image::FromFile(_T("res/Pablo The Painter 05.png"));
}

CShooter1::~CShooter1()
{
}

void CShooter1::Draw(Gdiplus::Graphics& gh)
{
	auto drawImg = [&](Image* img)
	{
		RectF rc;
		rc.X = m_mousePos.X;
		rc.Y = m_mousePos.Y;
		rc.Width = (float)img->GetHeight();
		rc.Height = (float)img->GetWidth();
		rc.Offset(-(rc.Width / 3.0f - 10.0f), 0);
		gh.DrawImage(img, rc);
	};

	// 重复画出相同的图片，拼接成一个梯子
	{
		//获取图片的大小
		float h = (float)m_img0->GetHeight();
		float w = (float)m_img0->GetWidth();

		RectF rc;
		rc.Width = w;
		rc.Height = h;
		rc.X = m_mousePos.X;
		//循环绘制，X位置不变，y位置一直增加，直到到达屏幕底端为止
		for(int y = 0; y < m_nHeight; ++y)
		{
			rc.Y = y * h;
			gh.DrawImage(m_img0, rc);
		}
	}

	// 根据当前状态，绘制不同的图片
	switch(m_status)
	{
	case 0:
	{
		break;
	}
	case 1:
		{
		drawImg(m_img1);
		break;
		}
	case 2:
	{
		drawImg(m_img2);
		break;
	}
	case 3:
	{
		drawImg(m_img3);
		break;
	}
	case 4:
	{
		drawImg(m_img4);
		break;
	}
	case 5:
	{
		drawImg(m_img5);
		break;
	}
	default:
		break;
	}
}

bool CShooter1::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_status = 5;
	return true;
}

bool CShooter1::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_status = 1;
	return true;
}

bool CShooter1::OnRButtonDown(UINT nFlags, CPoint point)
{
	//变颜色
	if(1+m_iColorIndex >= 6)
	{
		m_iColorIndex = 0;
	}else
	{
		m_iColorIndex++;
	}
	return false;
}

bool CShooter1::OnMouseMove(UINT nFlags, CPoint point)
{
	// 记录当前的位置
	m_mousePos.X = (float)point.x;
	m_mousePos.Y = (float)point.y;

	if(m_status == 5)
	{
		m_status = 5;
		RectF rc;
		rc.X = m_mousePosLast.X;
		rc.Y = m_mousePosLast.Y;
		rc.Width = 1;
		rc.Height = 1;
		if(!rc.Contains(m_mousePos))
		{
			m_mousePosLast = m_mousePos;
			g_game->Append(std::make_shared<CShooter1Mark>(
				m_mousePos.X, m_mousePos.Y, m_iColorIndex
				));
		}
		return true;
		
	}

	if((point.y > m_lastChangePos.Y) &&
		(m_distanceChange <= abs(point.y - m_lastChangePos.Y)))
	{
		switch(m_status)
		{
		case 1:
		case 2:
			{
			m_status = 3;
			}
			break;
		case 3:
		case 4:
			{
			m_status = 1;
			}
			break;
		default:
			break;
		}
		m_lastChangePos = m_mousePos;
	}else if((point.y < m_lastChangePos.Y) &&
		(m_distanceChange <= abs(point.y - m_lastChangePos.Y)))
	{
		switch (m_status)
		{
		case 1:
		case 2:
		{
			m_status = 3;
		}
		break;
		case 3:
		case 4:
		{
			m_status = 1;
		}
		break;
		default:
			break;
		}
		m_lastChangePos = m_mousePos;
	}else
	{
		
	}

	return true;
}
