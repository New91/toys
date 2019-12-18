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

	//鼠标消息
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnRButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnMouseMove(UINT nFlags, CPoint point) override;

	//开始播放动画
	void StartAnimate();
	// 设置动画，飞出 散布在四周
	void InitAnimateInfo0(float x, float y, float dir);
	// 以中心点做翻转
	void InitAnimateInfo1(float x, float y, float dir);
	// 以中心点做翻转， 逆向翻转
	void InitAnimateInfoReverse();
	// do nothing
	void InitAnimateInfo3(float x, float y);

	// 停止播放动画
	void EndAnimate()
	{
		m_indexAnimate = m_vAnimateInfo.size();
	}

	// 动画是否播放完毕
	bool IsAnimateEnd() const
	{
		return m_indexAnimate != 0 && m_indexAnimate >= m_vAnimateInfo.size();
	}
private:
	// 图片
	Image *m_img{ nullptr };
	//最初的大小
	SizeF m_sizeInit;

	//动画相关的信息
	typedef struct
	{
		SizeF size;
		PointF pos;
	}SAnimateInfo;

	std::vector<SAnimateInfo> m_vAnimateInfo;
	// 当前在第几帧的位置
	size_t m_indexAnimate;
	// 标记当前时飞出动画
	bool m_bAnimate{ false };
	// 标记当前是反转动画
	bool m_bAnimate2{ false };
};

