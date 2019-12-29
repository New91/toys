#include "stdafx.h"
#include "MenuItem.h"


CMenuItem::CMenuItem()
{
}

CMenuItem::CMenuItem(float x, float y, PCTSTR szImg, PCTSTR szTips)
{
	m_img = Image::FromFile(szImg);
	int width = m_img->GetWidth();
	int height = m_img->GetHeight();
	//����˵�ռ�õ�����
	RectF r(static_cast<float>(x),
		static_cast<float>(y),
		static_cast<float>(width),
		static_cast<float>(height));
	SetRect(r);
	m_sizeInit.Width = (float)width;
	m_sizeInit.Height = (float)height;
}

void CMenuItem::Draw(Gdiplus::Graphics& gh)
{
	if(m_indexAnimate >= m_vAnimateInfo.size())
	{
		m_indexAnimate = m_vAnimateInfo.size();
		if (m_indexAnimate == 0)
			return;
		m_indexAnimate--;
	}
	{
		auto const& info = m_vAnimateInfo[m_indexAnimate++];
		SetCenterPos(info.pos);								//�ƶ�λ��
		SetSize(info.size.Width, info.size.Height);		//����
	}
	gh.DrawImage(m_img, GetRect());
}

bool CMenuItem::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(this->GetRect().Contains((float)point.x,(float)point.y))
	{
		return true;
	}
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
	if (m_bAnimate)
		return;
	m_bAnimate = true;

	m_indexAnimate = 0;
	m_vAnimateInfo.clear();
	float w = m_sizeInit.Width*0.01f;
	float h = m_sizeInit.Height*0.01f;
	float ww = m_sizeInit.Width;
	float hh = m_sizeInit.Height;

	//���
	float www = m_sizeInit.Width*2.0f;
	float hhh = m_sizeInit.Height*2.0f;
	SAnimateInfo info;

	//��һ��λ��
	{
		info.size.Width = w;
		info.size.Height = h;
		info.pos.X = x;
		info.pos.Y = y;
		m_vAnimateInfo.push_back(info);
	}

	float distance = 1.0f;
	//�ﵽ���ֵ
	while(true)
	{
		// ��Сÿ������10%
		w *= (1 + 0.1f);
		h *= (1 + 0.1f);
		if(w > www && h > hhh)
		{
			break;
		}

		//λ��ÿ���ƶ�distance����
		x += distance * cos(PI(2) - dir);
		y += distance * sin(PI(2) - dir);
		{
			info.size.Width = w;
			info.size.Height = h;
			info.pos.X = x;
			info.pos.Y = y;
			m_vAnimateInfo.push_back(info);
		}
	}

	// �ָ���ԭʼֵ
	distance = 4.0f;
	while (true)
	{
		// ��Сÿ������10%
		w *= (1 - 0.03f);
		h *= (1 - 0.03f);
		if (w < www && h <= hhh)
		{
			break;
		}

		//λ��ÿ���ƶ�distance����
		x += distance * cos(PI(2) - dir);
		y += distance * sin(PI(2) - dir);
		{
			info.size.Width = w;
			info.size.Height = h;
			info.pos.X = x;
			info.pos.Y = y;
			m_vAnimateInfo.push_back(info);
		}
	}

	//����ʼ��С��Ϣ��������
	info.size = m_sizeInit;
	info.pos.X = x;
	info.pos.Y = y;
	m_vAnimateInfo.push_back(info);
	
}

// ���ö�����Ϣ�������ĵ�����ת
void CMenuItem::InitAnimateInfo1(float x, float y, float dir)
{
	if (m_bAnimate)
		return;
	m_bAnimate = true;

	m_indexAnimate = 0;
	m_vAnimateInfo.clear();//�˶�·����Ϣ���
	float w = m_sizeInit.Width;
	float h = m_sizeInit.Height;
	SAnimateInfo info;
	// ��һ��λ��
	{
		info.size.Width = w;
		info.size.Height = h;
		info.pos.X = x;
		info.pos.Y = y;
		m_vAnimateInfo.push_back(info);
	}

	for(int i = 0; i< 25; ++i)
	{
		// �߶�ÿ������10%
		h *= (1 - 0.05f);
		{
			info.size.Width = w;
			info.size.Height = h;
			info.pos.X = x;
			info.pos.Y = y;
			m_vAnimateInfo.push_back(info);
		}
	}
}

// ���ö�����Ϣ: �����ĵ�����ת������ת
void CMenuItem::InitAnimateInfoReverse()
{
	if (m_bAnimate2)
		return;
	m_bAnimate2 = true;

	m_indexAnimate = 0;
	// �Ѳ�����Ϣ������������һ��
	std::reverse(m_vAnimateInfo.begin(), m_vAnimateInfo.end());
}

void CMenuItem::InitAnimateInfo3(float x, float y)
{
	if (m_bAnimate)
		return;
	m_bAnimate = true;

	m_indexAnimate = 0;
	m_vAnimateInfo.clear();
	float w = m_sizeInit.Width * 0.01f;
	float h = m_sizeInit.Height * 0.01f;
	SAnimateInfo info;
	info.size = m_sizeInit;
	info.pos.X = x;
	info.pos.Y = y;
	m_vAnimateInfo.push_back(info);
}


CMenuItem::~CMenuItem()
{
}
