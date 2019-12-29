#pragma once
#include "IMark.h"
class CShooter1Mark :
	public IMark
{
public:
	CShooter1Mark(float x, float y, int index);
	virtual ~CShooter1Mark();

	virtual void Draw(Gdiplus::Graphics& gh) override;
	virtual bool IsChanging() const override;

private:
	std::vector<Image*> m_img;
	size_t m_index = 0;
};

