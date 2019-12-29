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
	//计算菜单占用的区域
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
		SetCenterPos(info.pos);								//移动位置
		SetSize(info.size.Width, info.size.Height);		//缩放
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

	//最大
	float www = m_sizeInit.Width*2.0f;
	float hhh = m_sizeInit.Height*2.0f;
	SAnimateInfo info;

	//第一个位置
	{
		info.size.Width = w;
		info.size.Height = h;
		info.pos.X = x;
		info.pos.Y = y;
		m_vAnimateInfo.push_back(info);
	}

	float distance = 1.0f;
	//达到最大值
	while(true)
	{
		// 大小每次增加10%
		w *= (1 + 0.1f);
		h *= (1 + 0.1f);
		if(w > www && h > hhh)
		{
			break;
		}

		//位置每次移动distance像素
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

	// 恢复到原始值
	distance = 4.0f;
	while (true)
	{
		// 大小每次增加10%
		w *= (1 - 0.03f);
		h *= (1 - 0.03f);
		if (w < www && h <= hhh)
		{
			break;
		}

		//位置每次移动distance像素
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

	//将初始大小信息放入数组
	info.size = m_sizeInit;
	info.pos.X = x;
	info.pos.Y = y;
	m_vAnimateInfo.push_back(info);
	
}

// 设置动画信息：以中心点做翻转
void CMenuItem::InitAnimateInfo1(float x, float y, float dir)
{
	if (m_bAnimate)
		return;
	m_bAnimate = true;

	m_indexAnimate = 0;
	m_vAnimateInfo.clear();//运动路径信息清空
	float w = m_sizeInit.Width;
	float h = m_sizeInit.Height;
	SAnimateInfo info;
	// 第一个位置
	{
		info.size.Width = w;
		info.size.Height = h;
		info.pos.X = x;
		info.pos.Y = y;
		m_vAnimateInfo.push_back(info);
	}

	for(int i = 0; i< 25; ++i)
	{
		// 高度每次增加10%
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

// 设置动画信息: 以中心点做翻转，逆向翻转
void CMenuItem::InitAnimateInfoReverse()
{
	if (m_bAnimate2)
		return;
	m_bAnimate2 = true;

	m_indexAnimate = 0;
	// 把播放信息数组逆序排列一下
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
