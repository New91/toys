#include "stdafx.h"
#include "Shooter0Mark.h"


CShooter0Mark::CShooter0Mark(float x, float y)
{
	// ����ͼƬ
	m_img.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire Marks 0.png")));
	m_img.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire Marks 1.png")));
	m_img.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire Marks 2.png")));
	m_img.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire Marks 3.png")));
	m_img.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire Marks 4.png")));

	srand(GetTickCount());// ����[0,5)֮����������
	m_index = rand() % 5;
	float t = rand() / (360.0f);// ����[0,360)֮����������
	m_dir = Degree2Radian(t);

	//�����Լ��Ĵ�С
	RectF rc;
	rc.X = 0;
	rc.Y = 0;
	rc.Width = (float)m_img[0]->GetWidth();
	rc.Height= (float)m_img[0]->GetHeight();
	SetRect(rc);

	SetCenterPos(x, y);
}

void CShooter0Mark::Draw(Gdiplus::Graphics& gh)
{
	gh.DrawImage(m_img[m_index], GetRect());//���ƴ��������ͼƬ
}

bool CShooter0Mark::IsChanging() const
{
	return false;
}

CShooter0Mark::~CShooter0Mark()
{
}
