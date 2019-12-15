#pragma once

class IMark;

class CGame
{
public:
	/*
	 * ���캯����
	 * hwnd�� ��Ϸ����
	 * x,y:λ��
	 * w,h�����ڿ��
	 */
	CGame(HWND hWnd, float x, float y, float w, float h);
	~CGame();
public:
	//��Ϸ��һ֡
	bool EnterFrame(DWORD dwTime);

	/////
	///���������Ϣ
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDblClk(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);

	BOOL OnESC();

	//����һ���ƻ���
	void Append(std::shared_ptr<IMark> pMark)
	{
		m_vMarks.push_back(pMark);
	}
	//��ȡ��Ϸ���ڵĿ��
	float GetWidth() const
	{
		return m_width;
	}

	//�߶�
	float GetHeight() const
	{
		return m_height;
	}

	// ��ȡ��Χ
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
	//��Ϸֻ��Ϊ�����׶Σ��˵��׶Σ���ʽ��Ϸ�׶�
	typedef enum EGameStatus{EGameStatusSelect, EGameStatusNormal}EGameStatus;
	EGameStatus m_eStatus{ EGameStatusSelect };

private:
	CRect m_rcClient;

	int m_fps{ 0 };
	//���FPS�����õ���ˢ
	SolidBrush m_brush{ Color(254,0xFF,0x00,0x00) };
	//���FPS��������
	Gdiplus::Font m_font{ L"����",10.0 };
	//�����Ͻ�
	PointF origin{ 0.0f,0.0f };

	//�������ж���
	void Draw();

	//���fps
	void DrawFps(Gdiplus::Graphics &gh);

	//�ƻ��������µĶ���
	std::vector<std::shared_ptr<IMark>> m_vMarks;

	//����ͼ
	Gdiplus::Bitmap *m_imgBk;
};

