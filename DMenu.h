#pragma once
#include "MenuItem.h"
#include "IMouseAction.h"

class CDMenu:
public IDrawable, public IMouseAction
{
public:
	CDMenu(HWND hWnd);
	virtual ~CDMenu();

	// ���³�ʼ�����˵����λ����Ϣ
	void InitAnimateInfo0();

	// �����Լ���ǰ�����Ի��Լ�
	virtual void Draw(Gdiplus::Graphics &gh);

	///���������Ϣ������������false
	//����������
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnMouseMove(UINT nFlags, CPoint point) override;
private:
	HWND m_hWnd;
	// �˵�����
	// ����
	std::shared_ptr<CMenuItem> m_box;
	std::shared_ptr<CMenuItem> m_cover;
	std::shared_ptr<CMenuItem> m_cover2;
	std::shared_ptr<CMenuItem> m_item0;
	std::shared_ptr<CMenuItem> m_item1;
	std::shared_ptr<CMenuItem> m_item2;
	std::shared_ptr<CMenuItem> m_item3;

	//������������
	void EndAnimate();

	typedef enum
	{
		EStatusOverCover1,
		EStatusItem0,
		EStatusItem1,
		EStatusItem2,
		EStatusItem3,
		EStatusOverCover2,
		EStatusAll,
	}EStatus;

	EStatus m_eStatus{ EStatusOverCover1 };
};

