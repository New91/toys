#include "stdafx.h"
#include "Game.h"
#include "ScreenTools.h"

CGame::CGame(HWND hWnd, float x, float y, float w, float h)
	:m_hWnd(hWnd)
	,m_x(x)
	,m_y(y)
	,m_width(w)
	,m_height(h)
{
	//����ȫ��ָ��
	g_game = this;
	{
		//��ͼ������Ļ�������Լ��Ĵ�����
		RECT r{ (long)x,(long)y,(long)(x + w),(long)(y + h) };
		HBITMAP hBmp = CScreenTools::CopyScreenToBitmap(&r);
		//���汳��ͼ
		m_imgBk = Bitmap::FromHBITMAP(hBmp, NULL);
	}
	//��ȡ���ڿͻ�����С
	GetClientRect(m_hWnd, &m_rcClient);
}

CGame::~CGame()
{
}

bool CGame::EnterFrame(DWORD dwTime)
{
	Draw();
	return false;
}

void CGame::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch(m_eStatus)
	{
	case CGame::EGameStatusSelect:
		{//�˵��׶Σ�����m_menu�˵�����
		break;
		}
	case CGame::EGameStatusNormal:
		{//��Ϸ�׶�
		break;
		}
	default:
		{
		break;
		}
	}
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (m_eStatus)
	{
	case CGame::EGameStatusSelect:
	{//�˵��׶Σ�����m_menu�˵�����
		break;
	}
	case CGame::EGameStatusNormal:
	{//��Ϸ�׶�
		break;
	}
	default:
	{
		break;
	}
	}

}

void CGame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
}

void CGame::OnRButtonDown(UINT nFlags, CPoint point)
{
	switch (m_eStatus)
	{
	case CGame::EGameStatusSelect:
	{//�˵��׶Σ�����m_menu�˵�����
		break;
	}
	case CGame::EGameStatusNormal:
	{//��Ϸ�׶�
		break;
	}
	default:
	{
		break;
	}
	}

}

void CGame::OnRButtonUp(UINT nFlags, CPoint point)
{
	switch (m_eStatus)
	{
	case CGame::EGameStatusSelect:
	{//�˵��׶Σ�����m_menu�˵�����
		break;
	}
	case CGame::EGameStatusNormal:
	{//��Ϸ�׶�
		break;
	}
	default:
	{
		break;
	}
	}

}

void CGame::OnRButtonDblClk(UINT nFlags, CPoint point)
{
}

void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
	switch (m_eStatus)
	{
	case CGame::EGameStatusSelect:
	{//�˵��׶Σ�����m_menu�˵�����
		break;
	}
	case CGame::EGameStatusNormal:
	{//��Ϸ�׶�
		break;
	}
	default:
	{
		break;
	}
	}

}

BOOL CGame::OnESC()
{
	switch (m_eStatus)
	{
	case CGame::EGameStatusSelect:
	{//��ǰû������Ϸ��������
		return FALSE;
	}
	case CGame::EGameStatusNormal:
	{//��ǰ��Ϸ���ص��˵�
		m_eStatus = EGameStatusSelect;
		//��ʾ���
		{
			//��ʼ״̬��������0�����б�֤��0�Ϳ�����ʾ��
			int i = ShowCursor(TRUE);
			if(i>0)
			{
				//���ٵ�0
				while (ShowCursor(FALSE) > 0) { ; }
			}else if(i<0)
			{
				//���ӵ�0
				while (ShowCursor(FALSE) < 0) { ; }
			}
		}
		return TRUE;
	}
	default:
	{
		break;
	}
	}
	return FALSE;
}

void CGame::Draw()
{
	HDC hdc = ::GetDC(m_hWnd);
	ON_SCOPE_EXIT([&](){//�뿪����������ʱ���ͷ�DC
		::ReleaseDC(m_hWnd, hdc);
	});

	CDC *dc = CClientDC::FromHandle(hdc);
	//˫�����ͼ��
	CDC m_dcMemory;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, m_rcClient.Width(), m_rcClient.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc());
	gh.SetPageUnit(Gdiplus::UnitPixel);

	Color clr;
	clr.SetFromCOLORREF(BACK_GROUND_LAYER);
	gh.Clear(clr);
	gh.ResetClip();

	gh.DrawImage(m_imgBk, m_x, m_y, m_width, m_height);//������ͼ
	{
		switch(m_eStatus)
		{
		case CGame::EGameStatusSelect:
			break;
		case CGame::EGameStatusNormal:
			break;
		default:
			break;
		}
	}
	DrawFps(gh);//����֡��
	::BitBlt(hdc, 0, 0, m_rcClient.Width(), m_rcClient.Height(),//���Ƶ���Ļ
		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	return;
}

void CGame::DrawFps(Gdiplus::Graphics& gh)
{
	static int fps = 0;
	m_fps++;
	static DWORD dwLast = GetTickCount();//���һ�����ʱ��
	if(GetTickCount() - dwLast >= 1000)
	{
		fps = m_fps;
		m_fps = 0;
		dwLast = GetTickCount();
	}

	{
		CString s;
		s.Format(_T("FPS:%d"), fps);
		gh.DrawString(s.GetString(), -1, &m_font, origin, &m_brush);
	}
}
