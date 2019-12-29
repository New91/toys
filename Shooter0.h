#pragma once
#include "Shooter.h"
#include "GameTimer.h"

/*
 * 忍者类
 */
class CShooter0 :
	public CShooter
{
public:
	CShooter0();
	virtual ~CShooter0();

	virtual void Draw(Gdiplus::Graphics& gh) override;

	//处理鼠标消息
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnRButtonDown(UINT nFlags, CPoint point) override;
private:
	std::vector<Image* > m_vImage;
	typedef enum
	{
		EStatus0 = 0,
		EStatusMove0,		//右
		EStatusMove1,		//右下
		EStatusMove2,		//上
		EStatusMove3,		//左上
		EStatusMove4,		//左
		EStatusMove5,		//左下
		EStatusMove6,		//下
		EStatusMove7,		//右下
		EStatusFireLeft,	//开火向左
		EStatusFireRight,	//开火向右
	}EStatus;

	EStatus m_eStatus{ EStatus0 };

	// 当前显示的图片
	size_t m_index = 0;
	//没有动作时，上下晃动

	CGameTimeval m_timer0{ 500 };
	// 记录当前是向上 还是向下
	bool m_bUp = false;
	/*
	 * 向某个方向上移动
	 * 开始移动
	 * 到达后恢复静止状态
	 */
	void DrawMove(Gdiplus::Graphics &gh);

	// 鼠标右键单击的位置
	PointF m_moveTo;
	//移动的方向
	float m_moveDir;

	/*
	 * 开火动画处理：开火共有4桢动画
	 * 0原地转身
	 * 1聚集能量
	 * 2聚集能量
	 * 3射击开始
	 * 4射击中
	 * 5射击完成
	 */
	//两帧图片之间的时间间隔
	CGameTimeval m_timeFire{ 100 };

	//  当前显示第几幅图片
	size_t m_index_fire = 0;
	//绘制开火动画
	void DrawFire(Gdiplus::Graphics &gh);

	// 鼠标右键单击的位置
	PointF m_fireTo;
};

