#pragma once
#include "IMark.h"

/*
 * �����ڴ��������µĺۼ�
 */
class CShooter0Mark :
	public IMark
{
public:
	CShooter0Mark(float x, float y);
	virtual ~CShooter0Mark();

	//���Լ�
	virtual void Draw(Gdiplus::Graphics& gh) override;

	//  ״̬�Ƿ��ڸı���
	virtual  bool IsChanging() const override;

private:
	std::vector<Image*> m_img;
	size_t m_index{ 0 };
	float m_dir;
};

