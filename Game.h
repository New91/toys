#pragma once

class IMark;

class CGame
{
public:
	/*
	 * 构造函数：
	 * hwnd： 游戏窗口
	 * x,y:位置
	 * w,h：窗口宽高
	 */
	CGame(HWND hWnd, float x, float y, float w, float h);
	~CGame();
public:
	//游戏的一帧
	bool EnterFrame(DWORD dwTime);

	/////
	///处理鼠标消息
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDblClk(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);

	BOOL OnESC();

	//增加一个破坏物
	void Append(std::shared_ptr<IMark> pMark)
	{
		m_vMarks.push_back(pMark);
	}
	//获取游戏窗口的宽度
	float GetWidth() const
	{
		return m_width;
	}

	//高度
	float GetHeight() const
	{
		return m_height;
	}

	// 获取范围
	RectF GetRectF() const
	{
		return RectF(m_x, m_y, m_width, m_height);
	}
private:
	HWND m_hWnd;
	float m_x;
	float m_y;

	float m_width;
	float m_height;
	//游戏只分为两个阶段：菜单阶段，正式游戏阶段
	typedef enum EGameStatus{EGameStatusSelect, EGameStatusNormal}EGameStatus;
	EGameStatus m_eStatus{ EGameStatusSelect };

private:
	CRect m_rcClient;

	int m_fps{ 0 };
	//输出FPS文字用到画刷
	SolidBrush m_brush{ Color(254,0xFF,0x00,0x00) };
	//输出FPS文字字体
	Gdiplus::Font m_font{ L"宋体",10.0 };
	//在左上角
	PointF origin{ 0.0f,0.0f };

	//画出所有对象
	void Draw();

	//输出fps
	void DrawFps(Gdiplus::Graphics &gh);

	//破坏窗口留下的东西
	std::vector<std::shared_ptr<IMark>> m_vMarks;

	//背景图
	Gdiplus::Bitmap *m_imgBk;
};

