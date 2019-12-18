#pragma once

#include "IDrawable.h"
#include "IMouseAction.h"

class CMenuItem
	:public IDrawable
	,public IMouseAction
{
public:
	CMenuItem();
	CMenuItem(float x, float y, PCTSTR szImg, PCTSTR szTips);
	virtual ~CMenuItem();

	virtual  void Draw(Gdiplus::Graphics& gh) override;

	//�����Ϣ
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnRButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnMouseMove(UINT nFlags, CPoint point) override;

	//��ʼ���Ŷ���
	void StartAnimate();
	// ���ö������ɳ� ɢ��������
	void InitAnimateInfo0(float x, float y, float dir);
	// �����ĵ�����ת
	void InitAnimateInfo1(float x, float y, float dir);
	// �����ĵ�����ת�� ����ת
	void InitAnimateInfoReverse();
	// do nothing
	void InitAnimateInfo3(float x, float y);

	// ֹͣ���Ŷ���
	void EndAnimate()
	{
		m_indexAnimate = m_vAnimateInfo.size();
	}

	// �����Ƿ񲥷����
	bool IsAnimateEnd() const
	{
		return m_indexAnimate != 0 && m_indexAnimate >= m_vAnimateInfo.size();
	}
private:
	// ͼƬ
	Image *m_img{ nullptr };
	//����Ĵ�С
	SizeF m_sizeInit;

	//������ص���Ϣ
	typedef struct
	{
		SizeF size;
		PointF pos;
	}SAnimateInfo;

	std::vector<SAnimateInfo> m_vAnimateInfo;
	// ��ǰ�ڵڼ�֡��λ��
	size_t m_indexAnimate;
	// ��ǵ�ǰʱ�ɳ�����
	bool m_bAnimate{ false };
	// ��ǵ�ǰ�Ƿ�ת����
	bool m_bAnimate2{ false };
};

