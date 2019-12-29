#include "stdafx.h"
#include "Shooter0.h"
#include "Shooter0Mark.h"
#include <iostream>


CShooter0::CShooter0()
{
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 静.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 右.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 右上.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 上.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 左上.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 左.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 左下.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 下.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 右下.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 左下.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Fire Path.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire 00.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire 01.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire 02.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire 03.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire 04.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Right Fire 00.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Right Fire 01.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Right Fire 02.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Right Fire 03.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Right Fire 04.png")));

	// 设置本类的大小
	RectF rc;
	rc.Width = (float)m_vImage[0]->GetWidth();
	rc.Height = (float)m_vImage[0]->GetHeight();
	rc.X = 800.0f;
	rc.Y = 600.0f;
	SetRect(rc);
}


CShooter0::~CShooter0()
{
}

void CShooter0::Draw(Gdiplus::Graphics& gh)
{
	switch(m_eStatus)
	{
	case EStatus0:
		{
			// 当前阶段机器上下晃动
			// 设置显示的图片
		m_index = 0;
			//判断时间
			if(m_timer0.IsTimeval())
			{
				m_bUp = !m_bUp;
				if(m_bUp)
				{
					//位置向上移
					auto pt = GetCenterPos();
					pt.Y += 1.0f;
					SetCenterPos(pt);
				}else
				{
					//位置向下移
					auto pt = GetCenterPos();
					pt.Y -= 1.0f;
					SetCenterPos(pt);
				}
			}
			cout << m_vImage[m_index] << endl;
			gh.DrawImage(m_vImage[m_index], GetRect());
		break;
		}
	case EStatusMove0:
		{
		m_index = 1 + (EStatusMove0 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
		}
	case EStatusMove1:
	{
		m_index = 1 + (EStatusMove1 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove2:
	{
		m_index = 1 + (EStatusMove2 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove3:
	{
		m_index = 1 + (EStatusMove3 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove4:
	{
		m_index = 1 + (EStatusMove4 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove5:
	{
		m_index = 1 + (EStatusMove5 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove6:
	{
		m_index = 1 + (EStatusMove6 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove7:
	{
		m_index = 1 + (EStatusMove7 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusFireLeft:
	{
		DrawFire(gh);
		break;
	}
	case EStatusFireRight:
	{
		DrawFire(gh);
		break;
	}
	default:
		break;
	}
}

bool CShooter0::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 根据当前位置和单击位置计算角度
	PointF ptCenter = GetCenterPos();
	// 单击位置
	PointF ptDest(static_cast<float>(point.x), static_cast<float>(point.y));

	// 记录移动的目的地
	m_moveTo = ptDest;

	//计算夹角
	float theta = std::atan2<float>(-(ptDest.Y - ptCenter.Y),
		ptDest.X - ptCenter.X);
	if(theta < 0.0f)
	{
		theta = PI(2.0f) + theta;
	}

	m_moveDir = theta;//记录移动方向
	//平面直角坐标系统分为8份，当角落在某个区间时，分别处理 如显示不同的图片
	float a_per = PI(2.0f / 8.0f);
	float a_per_half = (a_per / 2.0f);
	float a_start = -a_per_half;
	int i = 0;
	for(;i<7;i++)
	{
		float min = a_start + i * a_per;
		float max = a_start + (1 + i)*a_per;
		if(min <= theta && theta < max)
		{
			//设置当前的状态
			m_eStatus = (EStatus)(i + EStatusMove0);
			break;
		}
	}
	// 直接落入第8个位置
	if(i == 7)
	{
		// 设置当前的状态
		m_eStatus = (EStatus)(i + EStatusMove0);
		return true;
	}
	// 这里是不可能走到的
	return false;
}

bool CShooter0::OnRButtonDown(UINT nFlags, CPoint point)
{
	PointF ptCenter = GetCenterPos();
	PointF ptDest(static_cast<float>(point.x), static_cast<float>(point.y));
	m_fireTo = ptDest;

	if(ptDest.X > ptCenter.X)
	{
		m_eStatus = EStatusFireRight;
	}else
	{
		m_eStatus = EStatusFireLeft;//向左开火
	}

	// 重新开始倒计时
	m_timeFire.Restart();
	// 重置帧序号
	m_index_fire = 0;
	return true;
}

void CShooter0::DrawMove(Gdiplus::Graphics& gh)
{
	// 只更新位置,直到到达为止
	// 如果到达，更新状态
	if(GetRect().Contains(m_moveTo))
	{
		m_eStatus = EStatus0;
		return;
	}
	// 否则移动忍者
	PointF pt = GetCenterPos();
	pt.X += 20.0f * cos(PI(2.0f) - m_moveDir);
	pt.Y += 20.0f * sin(PI(2.0f) - m_moveDir);

	SetCenterPos(pt);
}

void CShooter0::DrawFire(Gdiplus::Graphics& gh)
{
	//画图片
	switch(m_eStatus)
	{
	case EStatusFireLeft:
		{
			switch(m_index_fire)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 5:
				{
				int t = 10 + m_index_fire%5;
				auto img = m_vImage[t];//忍者转身
				RectF r = GetRect();
				r.Width = (float)img->GetWidth();
				r.Height = (float)img->GetHeight();
				gh.DrawImage(img, r);
				break;
				}
			case 4:
				{
				const float Y = GetRect().Y;
				const float X = GetRect().X;

				const float YY = Y;
				const float XX = m_fireTo.X + 30.0f;

					//画忍者身体,动作
				{
					auto img = m_vImage[13];
					gh.DrawImage(img, X, Y);
				}
					//画激光中间部分
				{
					auto img = m_vImage[9];
					float left = X + 52;
					// 拼接图片进行输出，因为中间部分长度不确定,不能事先确定图片的长度
					while(left >= (XX + 60.0f))
					{
						gh.DrawImage(img, left, Y, (float)img->GetWidth(),
							(float)img->GetHeight());
						left -= (-2.0f + (float)img->GetWidth());
					}
					
				}
					// 画击中部分
				{
					// 这个要根据鼠标的左键画图
					auto img = m_vImage[14];
					gh.DrawImage(img, X, Y);
				}
				break;
				}
			case 6:
				{
				m_eStatus = EStatus0;
				return;
				}
			default:
				break;
			}
		}
	case EStatusFireRight:
		{
		switch (m_index_fire)
		{
		case 0:
		case 1:
		case 2:
		case 5:
		{
			int t = 15 + m_index_fire % 5;
			auto img = m_vImage[t];//忍者转身
			RectF r = GetRect();
			r.Width = (float)img->GetWidth();
			r.Height = (float)img->GetHeight();
			gh.DrawImage(img, r);
			break;
		}
		case 3:
			{
				// 射击开始：发出第一颗子弹
			g_game->Append(std::make_shared<CShooter0Mark>(
				m_fireTo.X, GetRect().Y));
			}
		case 4:
		{
			const float Y = GetRect().Y;
			const float X = GetRect().X;

			const float YY = Y;
			const float XX = m_fireTo.X - m_vImage[19]->GetWidth() + 30.0f;

			//画忍者身体,动作
			{
				auto img = m_vImage[18];
				gh.DrawImage(img, X, Y, (float)m_vImage[18]->GetWidth(),
										(float)m_vImage[18]->GetHeight());
			}
			//画激光中间部分
			{
				auto img = m_vImage[9];
				float left = X + 50;
				// 拼接图片进行输出，因为中间部分长度不确定,不能事先确定图片的长度
				while (left >= (XX))
				{
					gh.DrawImage(img, left, Y+4, (float)img->GetWidth(),
						(float)img->GetHeight());
					left -= (-2.0f + (float)img->GetWidth());
				}

			}
			// 画击中部分
			{
				// 这个要根据鼠标的左键画图
				auto img = m_vImage[19];
				gh.DrawImage(img, X, Y, (float)m_vImage[19]->GetWidth(),
					(float)m_vImage[19]->GetHeight());
			}
			break;
		}
		case 6:
		{
			m_eStatus = EStatus0;
			return;
		}
		default:
			break;
		}
			break;
		}
	default:
		break;
	}

	if(m_timeFire.IsTimeval())
	{
		//如果时间间隔到达，才进行切换状态的操作，这样是为了防止速度过快
		int times = m_timeFire.GetTimes();
		if(times > 6)
		{
			m_index_fire = 6;
		}else if(times > 0) //向下取整 
		{
			m_index_fire = times - 1;
		}
	}
}
