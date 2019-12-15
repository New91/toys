
// DeskopToysDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DeskopToys.h"
#include "DeskopToysDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDeskopToysDlg 对话框



CDeskopToysDlg::CDeskopToysDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DESKOPTOYS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeskopToysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDeskopToysDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
//	ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_WM_RBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_TIMER()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDeskopToysDlg 消息处理程序

BOOL CDeskopToysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	{
		int w = GetSystemMetrics(SM_CXSCREEN);
		int y = GetSystemMetrics(SM_CYSCREEN);
		MoveWindow(0, 0, w, y);
		//截取部分屏幕，并保存到文件中
		//RECT r{ 0,0,100,300 };
		//HBITMAP hBmp = CScreenTools::CopyScreenToBitmap(&r);
		//保存背景图
		//CScreenTools::SaveBitmapToFile(hBmp, _T("F:\\1.bmp"));
		///HBITMAP hBmp = CScreenTools::PrintScreen();
		///bmp = Bitmap::FromHBITMAP(hBmp, NULL);
		m_pGame = std::make_shared<CGame>(GetSafeHwnd(), 0.0f, 0.0f, float(w), float(y));
		SetTimer(1, 0, nullptr);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDeskopToysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		{
			HDC hdc = ::GetDC(GetSafeHwnd());
			Gdiplus::Graphics gh(hdc);
			gh.DrawImage(bmp, Rect(0, 0, 2560, 1600));
			::ReleaseDC(GetSafeHwnd(), hdc);
		}
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDeskopToysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CDeskopToysDlg::PreTranslateMessage(MSG* pMsg)
{
	//按下<ESC>键时
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		if(m_pGame->OnESC())
		{
			return TRUE;
		}else
		{
			
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDeskopToysDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->OnLButtonUp(nFlags, point);
	CDialogEx::OnLButtonUp(nFlags, point);
}


//void CDeskopToysDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//}


void CDeskopToysDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->OnRButtonDown(nFlags, point);
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CDeskopToysDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->OnRButtonUp(nFlags, point);
	CDialogEx::OnRButtonUp(nFlags, point);
}


void CDeskopToysDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->OnMouseMove(nFlags, point);
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDeskopToysDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->EnterFrame(0);
	CDialogEx::OnTimer(nIDEvent);
}


void CDeskopToysDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->OnLButtonDown(nFlags, point);
	CDialogEx::OnLButtonDown(nFlags, point);
}
