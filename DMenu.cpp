#include "stdafx.h"
#include "DMenu.h"
#include "Shooter.h"
#include "Shooter0.h"
#include "Shooter1.h"
#include "Shooter2.h"

CDMenu::CDMenu(HWND hWnd):m_hWnd(hWnd)
{
	m_box = make_shared<CMenuItem>(100.0f, 100.0f, _T("res/Menu Center01.png"), _T(""));
	m_cover = make_shared<CMenuItem>(100.0f, 100.0f, _T("res/Menu Center02.png"), _T(""));
	m_cover2= make_shared<CMenuItem>(100.0f, 100.0f, _T("res/Menu Center02.png"), _T(""));
	m_item0 = make_shared<CMenuItem>(100.0f, 100.0f, _T("res/MenuItem00.png"), _T("����"));
	m_item1 = make_shared<CMenuItem>(100.0f, 100.0f, _T("res/MenuItem01.png"), _T("��ˢ��"));
	m_item2 = make_shared<CMenuItem>(100.0f, 100.0f, _T("res/MenuItem02.png"), _T("����"));
	m_item3 = make_shared<CMenuItem>(100.0f, 100.0f, _T("res/MenuItem03.png"), _T("��Ƥ��"));
	{
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		PointF pt((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
		SetCenterPos(pt);
	}
	InitAnimateInfo0();
	
}


CDMenu::~CDMenu()
{
}

// ���³�ʼ�����˵����λ����Ϣ
void CDMenu::InitAnimateInfo0()
{
	//��ȡ��Ļ���ĵ��λ�ã����ø����λ��
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	PointF pt = GetCenterPos();
	//���ø�������ĵ�
	m_box->SetCenterPos(pt);
	m_item0->SetCenterPos(pt);
	m_item1->SetCenterPos(pt);
	m_item2->SetCenterPos(pt);
	m_item3->SetCenterPos(pt);

	//�ϸǵ����ĵ��ں��ӵ�����
	{
		PointF pt2 = pt;
		pt2.Y -= 30;
		m_cover->SetCenterPos(pt2);//�򿪵ĺи�
	}

	{
		PointF pt2 = pt;
		pt2.Y -= 30;
		m_cover2->SetCenterPos(pt2);//�رյĺи�
	}

	//��ʼ��������Ϣ
	m_box->InitAnimateInfo3(pt.X, pt.Y);
	m_cover->InitAnimateInfo1(pt.X, pt.Y - 100, PI(0.5f));
	//��ʼ���ĸ��˵�����Ķ���
	m_item0->InitAnimateInfo0(pt.X, pt.Y, 0.0f);
	m_item1->InitAnimateInfo0(pt.X, pt.Y, PI(0.5f));
	m_item2->InitAnimateInfo0(pt.X, pt.Y, PI(1.0f));
	m_item3->InitAnimateInfo0(pt.X, pt.Y, PI(1.5f));
	//��ʼ��������Ϣ
	m_cover2->InitAnimateInfo1(pt.X, pt.Y - 100, PI(0.5f));
	m_cover2->InitAnimateInfoReverse();
}

void CDMenu::Draw(Gdiplus::Graphics& gh)
{
	switch (m_eStatus)
	{
	case EStatusOverCover1:
	{
		PointF pt = GetCenterPos();
		if (m_cover->IsAnimateEnd())
		{
			m_eStatus = EStatusItem0;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		break;
	}
	case EStatusItem0:
	{
		if (m_item0->IsAnimateEnd())
		{
			m_eStatus = EStatusItem1;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		break;
	}
	case EStatusItem1:
	{
		if (m_item1->IsAnimateEnd())
		{
			m_eStatus = EStatusItem2;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		break;
	}
	case EStatusItem2:
	{
		if (m_item2->IsAnimateEnd())
		{
			m_eStatus = EStatusItem3;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		break;
	}
	case EStatusItem3:
	{
		if (m_item3->IsAnimateEnd())
		{
			m_eStatus = EStatusOverCover2;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	case EStatusOverCover2:
	{
		if (m_cover2->IsAnimateEnd())
		{
			m_eStatus = EStatusAll;
			break;
		}
		m_box->Draw(gh);
		m_cover2->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	case EStatusAll:
	{
		m_box->Draw(gh);
		m_cover2->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	default:
		break;
	}
}

bool CDMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// �鿴�������ĸ��˵�
	if(m_item0->OnLButtonDown(nFlags,point))
	{
		EndAnimate();
		//AfxMessageBox(_T("CShooter0"));
		g_game->SetStatusNormal(make_shared<CShooter0>(), TRUE);
		return true;
	}
	if (m_item1->OnLButtonDown(nFlags, point))
	{
		EndAnimate();
		RECT rc;
		GetClientRect(m_hWnd, &rc);
		//AfxMessageBox(_T("CShooter1"));
		g_game->SetStatusNormal(make_shared<CShooter1>(static_cast<int>(rc.bottom - rc.top)), FALSE);
		return true;
	}
	if (m_item2->OnLButtonDown(nFlags, point))
	{
		EndAnimate();
		g_game->SetStatusNormal(make_shared<CShooter2>(), TRUE);

		//AfxMessageBox(_T("CShooter2"));
		return true;
	}
	if (m_item3->OnLButtonDown(nFlags, point))
	{
		EndAnimate();
		AfxMessageBox(_T("CShooter3"));
		return true;
	}

	return false;
}

bool CDMenu::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_item0->OnMouseMove(nFlags, point))
	{
		return true;
	}
	if (m_item1->OnMouseMove(nFlags, point))
	{
		return true;
	}
	if (m_item2->OnMouseMove(nFlags, point))
	{
		return true;
	}
	if (m_item3->OnMouseMove(nFlags, point))
	{
		return true;
	}
	return false;
}

void CDMenu::EndAnimate()
{
	m_eStatus = EStatusAll;
	m_item0->EndAnimate();
	m_item1->EndAnimate();
	m_item2->EndAnimate();
	m_item3->EndAnimate();
	m_cover->EndAnimate();
	m_cover2->EndAnimate();
}
