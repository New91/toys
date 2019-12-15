#pragma once
class IDrawable
{
public:
	IDrawable();
	virtual ~IDrawable();
	//根据自己的当前属性画自己
	virtual  void Draw(Gdiplus::Graphics &gh) = 0;

	RectF GetRect() const
	{
		return m_rect;
	}

	void SetRect(RectF &rect)
	{
		m_rect = rect;
	};

	void SetRect(float x,float y,float width,float height)
	{
		m_rect.X = x;
		m_rect.Y = y;
		m_rect.Width = width;
		m_rect.Height = height;
	}

	void SetCenterPos(const PointF& ptCenter)
	{
		RectF r = m_rect;
		r.X = ptCenter.X - r.Width / 2.0f;
		r.Y = ptCenter.Y - r.Height/ 2.0f;
		SetRect(r);
	};

	void SetCenterPos(float x, float y)
	{
		PointF ptCenter(x, y);
		SetCenterPos(ptCenter);
	}

	PointF GetCenterPos()
	{
		PointF pt;
		pt.X = m_rect.X + m_rect.Width / 2.0f;
		pt.Y = m_rect.Y + m_rect.Height / 2.0f;
		return pt;
	}

	void SetSize(float w, float h)
	{
		PointF ptCenter = GetCenterPos();
		RectF rr = m_rect;
		rr.Width = w;
		rr.Height = h;
		SetRect(rr);
		SetCenterPos(ptCenter);
	}
protected:
	RectF m_rect;
};

