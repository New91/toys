#include "stdafx.h"
#include "Shooter0.h"
#include "Shooter0Mark.h"
#include <iostream>


CShooter0::CShooter0()
{
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero ��.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero ��.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero ����.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero ��.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero ����.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero ��.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero ����.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero ��.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero ����.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero ����.png")));
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

	// ���ñ���Ĵ�С
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
			// ��ǰ�׶λ������»ζ�
			// ������ʾ��ͼƬ
		m_index = 0;
			//�ж�ʱ��
			if(m_timer0.IsTimeval())
			{
				m_bUp = !m_bUp;
				if(m_bUp)
				{
					//λ��������
					auto pt = GetCenterPos();
					pt.Y += 1.0f;
					SetCenterPos(pt);
				}else
				{
					//λ��������
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
	// ���ݵ�ǰλ�ú͵���λ�ü���Ƕ�
	PointF ptCenter = GetCenterPos();
	// ����λ��
	PointF ptDest(static_cast<float>(point.x), static_cast<float>(point.y));

	// ��¼�ƶ���Ŀ�ĵ�
	m_moveTo = ptDest;

	//����н�
	float theta = std::atan2<float>(-(ptDest.Y - ptCenter.Y),
		ptDest.X - ptCenter.X);
	if(theta < 0.0f)
	{
		theta = PI(2.0f) + theta;
	}

	m_moveDir = theta;//��¼�ƶ�����
	//ƽ��ֱ������ϵͳ��Ϊ8�ݣ���������ĳ������ʱ���ֱ��� ����ʾ��ͬ��ͼƬ
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
			//���õ�ǰ��״̬
			m_eStatus = (EStatus)(i + EStatusMove0);
			break;
		}
	}
	// ֱ�������8��λ��
	if(i == 7)
	{
		// ���õ�ǰ��״̬
		m_eStatus = (EStatus)(i + EStatusMove0);
		return true;
	}
	// �����ǲ������ߵ���
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
		m_eStatus = EStatusFireLeft;//���󿪻�
	}

	// ���¿�ʼ����ʱ
	m_timeFire.Restart();
	// ����֡���
	m_index_fire = 0;
	return true;
}

void CShooter0::DrawMove(Gdiplus::Graphics& gh)
{
	// ֻ����λ��,ֱ������Ϊֹ
	// ����������״̬
	if(GetRect().Contains(m_moveTo))
	{
		m_eStatus = EStatus0;
		return;
	}
	// �����ƶ�����
	PointF pt = GetCenterPos();
	pt.X += 20.0f * cos(PI(2.0f) - m_moveDir);
	pt.Y += 20.0f * sin(PI(2.0f) - m_moveDir);

	SetCenterPos(pt);
}

void CShooter0::DrawFire(Gdiplus::Graphics& gh)
{
	//��ͼƬ
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
				auto img = m_vImage[t];//����ת��
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

					//����������,����
				{
					auto img = m_vImage[13];
					gh.DrawImage(img, X, Y);
				}
					//�������м䲿��
				{
					auto img = m_vImage[9];
					float left = X + 52;
					// ƴ��ͼƬ�����������Ϊ�м䲿�ֳ��Ȳ�ȷ��,��������ȷ��ͼƬ�ĳ���
					while(left >= (XX + 60.0f))
					{
						gh.DrawImage(img, left, Y, (float)img->GetWidth(),
							(float)img->GetHeight());
						left -= (-2.0f + (float)img->GetWidth());
					}
					
				}
					// �����в���
				{
					// ���Ҫ�������������ͼ
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
			auto img = m_vImage[t];//����ת��
			RectF r = GetRect();
			r.Width = (float)img->GetWidth();
			r.Height = (float)img->GetHeight();
			gh.DrawImage(img, r);
			break;
		}
		case 3:
			{
				// �����ʼ��������һ���ӵ�
			g_game->Append(std::make_shared<CShooter0Mark>(
				m_fireTo.X, GetRect().Y));
			}
		case 4:
		{
			const float Y = GetRect().Y;
			const float X = GetRect().X;

			const float YY = Y;
			const float XX = m_fireTo.X - m_vImage[19]->GetWidth() + 30.0f;

			//����������,����
			{
				auto img = m_vImage[18];
				gh.DrawImage(img, X, Y, (float)m_vImage[18]->GetWidth(),
										(float)m_vImage[18]->GetHeight());
			}
			//�������м䲿��
			{
				auto img = m_vImage[9];
				float left = X + 50;
				// ƴ��ͼƬ�����������Ϊ�м䲿�ֳ��Ȳ�ȷ��,��������ȷ��ͼƬ�ĳ���
				while (left >= (XX))
				{
					gh.DrawImage(img, left, Y+4, (float)img->GetWidth(),
						(float)img->GetHeight());
					left -= (-2.0f + (float)img->GetWidth());
				}

			}
			// �����в���
			{
				// ���Ҫ�������������ͼ
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
		//���ʱ��������Ž����л�״̬�Ĳ�����������Ϊ�˷�ֹ�ٶȹ���
		int times = m_timeFire.GetTimes();
		if(times > 6)
		{
			m_index_fire = 6;
		}else if(times > 0) //����ȡ�� 
		{
			m_index_fire = times - 1;
		}
	}
}
