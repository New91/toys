#include "stdafx.h"
#include "Game.h"
#include "ScreenTools.h"
#include "IMark.h"

CGame::CGame(HWND hWnd, float x, float y, float w, float h)
	:m_hWnd(hWnd)
	,m_x(x)
	,m_y(y)
	,m_width(w)
	,m_height(h)
{
	//保存全局指针
	g_game = this;
	m_menu = std::make_shared<CDMenu>(hWnd);//菜单初始化
	{
		//截图整个屏幕，画在自己的窗口上
		RECT r{ (long)x,(long)y,(long)(x + w),(long)(y + h) };
		HBITMAP hBmp = CScreenTools::CopyScreenToBitmap(&r);
		//保存背景图
		m_imgBk = Bitmap::FromHBITMAP(hBmp, NULL);
	}
	//获取窗口客户区大小
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
		{//菜单阶段，交给m_menu菜单处理
			if(m_menu->OnLButtonDown(nFlags, point))
			{
				break;
			}
		break;
		}
	case CGame::EGameStatusNormal:
		{//游戏阶段
		m_pTool->OnLButtonDown(nFlags, point);
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
	{//菜单阶段，交给m_menu菜单处理
		if (m_menu->OnRButtonDown(nFlags, point)){
			break;
		}
		break;
	}
	case CGame::EGameStatusNormal:
	{//游戏阶段
		m_pTool->OnLButtonUp(nFlags, point);
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
	{//菜单阶段，交给m_menu菜单处理
		if (m_menu->OnRButtonDown(nFlags, point)) {
			break;
		}
		break;
	}
	case CGame::EGameStatusNormal:
	{//游戏阶段
		m_pTool->OnRButtonDown(nFlags, point);
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
	{//菜单阶段，交给m_menu菜单处理
		if (m_menu->OnRButtonUp(nFlags, point)) {
			break;
		}
		break;
	}
	case CGame::EGameStatusNormal:
	{//游戏阶段
		m_pTool->OnRButtonUp(nFlags, point);
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
	{//菜单阶段，交给m_menu菜单处理
		break;
	}
	case CGame::EGameStatusNormal:
	{//游戏阶段
		m_pTool->OnMouseMove(nFlags, point);
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
	{//当前没有在游戏，不处理
		return FALSE;
	}
	case CGame::EGameStatusNormal:
	{//当前游戏返回到菜单
		m_eStatus = EGameStatusSelect;
		//显示鼠标
		{
			//初始状态，计数是0，所有保证是0就可以显示了
			int i = ShowCursor(TRUE);
			if(i>0)
			{
				//减少到0
				while (ShowCursor(FALSE) > 0) { ; }
			}else if(i<0)
			{
				//增加到0
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

void CGame::SetStatusNormal(std::shared_ptr<CShooter> pTool, BOOL bCursor)
{
	// 设置使用的工具
	m_pTool = pTool;
	// 设置游戏状态
	m_eStatus = EGameStatusNormal;
	//隐藏鼠标
	if(!bCursor)
	{
		while(true)
		{
			int i = ShowCursor(FALSE);
			TRACE("隐藏光标 %d \r\n", i);
			if(i<0)
			{
				break;
			}
		}
	}else
	{
		int i = ShowCursor(bCursor);
		TRACE("显示光标 %d \r\n", i);
	}
}

void CGame::Draw()
{
	HDC hdc = ::GetDC(m_hWnd);
	ON_SCOPE_EXIT([&](){//离开函数作用域时，释放DC
		::ReleaseDC(m_hWnd, hdc);
	});

	CDC *dc = CClientDC::FromHandle(hdc);
	//双缓冲绘图用
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
	if(!m_vMarks.empty())
	{
		Graphics gh(m_imgBk);
		for(auto ptr:m_vMarks)
		{
			// 不再变化的对象，直接合并入背景图片中，用来提高绘图效率
			if(!ptr->IsChanging())
			{
				ptr->Draw(gh);
			}
		}

		// 删除不再变化的对象
		m_vMarks.erase(std::remove_if(m_vMarks.begin(), m_vMarks.end(),
			[](auto &lhs)->bool {return !lhs->IsChanging(); }), m_vMarks.end());
	}
	
	gh.DrawImage(m_imgBk, m_x, m_y, m_width, m_height);//画背景图
	for(auto &ptr:m_vMarks)
	{
		ptr->Draw(gh);
	}
	{
		switch(m_eStatus)
		{
		case CGame::EGameStatusSelect:
			if(m_menu)
			{
				m_menu->Draw(gh);
			}
			break;
		case CGame::EGameStatusNormal:
			if(m_pTool)
			{
				m_pTool->Draw(gh);
			}
			break;
		default:
			break;
		}
	}
	DrawFps(gh);//画出帧数
	::BitBlt(hdc, 0, 0, m_rcClient.Width(), m_rcClient.Height(),//复制到屏幕
		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	return;
}

void CGame::DrawFps(Gdiplus::Graphics& gh)
{
	static int fps = 0;
	m_fps++;
	static DWORD dwLast = GetTickCount();//最后一次输出时间
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
