#include "stdafx.h"
#include "Shooter2Mark.h"



CShooter2Mark::CShooter2Mark(float x, float y)
{
	SetCenterPos(x, y);

	// 生成[1,5)之间的随机数
	int i = 1 + rand() % 5;
	TCHAR szFilename[MAX_PATH] = { 0 };
	_stprintf_s(szFilename, _T("res/The Toolbox Mark %02d.png"), i);
	m_img = Image::FromFile(szFilename);

	for(int i = 0; i < (1+rand()%3); ++i)
	{
		SDynamic dy;
		// 下落的物体
		dy.m_img2 = Image::FromFile(_T("res/The Toolbox Mark 06.png"));
		// 速度 包含方向 [-5,4/-5,4]
		dy.m_speed = PointF(float(rand() % 10 - 5), float(rand() % 10 - 5));
		//位置
		dy.m_pos.X = x + float(rand() % 80 - 40);
		dy.m_pos.Y = y + float(rand() % 80 - 40);
		// 当前角度(用于旋转
		dy.m_dir = Degree2Radian(rand()% 360);
		// 是否显示
		dy.m_bShow = true;
		m_vD.push_back(dy);
	}
}

CShooter2Mark::~CShooter2Mark()
{
}

// 顺时针旋转绘图
static void DrawImageRotate(PointF mousePt, Graphics &gh, Image* img, float degree)
{
	//旋转绘图 平面
	PointF center = mousePt;
	center.X += img->GetWidth() / 2.0f;
	center.Y += img->GetHeight() / 2.0f;

	gh.TranslateTransform(center.X, center.Y);
	gh.RotateTransform(degree);
	gh.TranslateTransform(-center.X, -center.Y);

	ON_SCOPE_EXIT([&]()
	{
		//重置坐标变换，精度是否足够
		// 移动到中心点
		gh.TranslateTransform(center.X, center.Y);
		gh.RotateTransform(-degree);
		gh.TranslateTransform(-center.X, -center.Y);
	});

	{
		RectF rc;
		rc.X = mousePt.X;
		rc.Y = mousePt.Y;
		rc.Width = (float)img->GetWidth();
		rc.Height = (float)img->GetHeight();
		gh.DrawImage(img, rc);
	}
}


void CShooter2Mark::Draw(Gdiplus::Graphics& gh)
{
	// 主图片
	gh.DrawImage(m_img, GetCenterPos());
	for(auto &dy:m_vD)
	{
		if(dy.m_bShow)
		{
			if(!g_game->GetRectF().Contains(dy.m_pos))
			{
				continue;
			}

			DrawImageRotate(dy.m_pos, gh, dy.m_img2, Radian2Degree(dy.m_dir));
			{
				//调整位置
				dy.m_pos.X += dy.m_speed.X;
				dy.m_pos.Y += dy.m_speed.Y;

				//调整速度,y方向符合重力加速度
				dy.m_speed.Y += 1.0f;
				//调整当前的角度
				dy.m_dir += PI(0.1f);
				
				if(dy.m_dir >= PI(2.0f))
				{
					dy.m_dir = 0.0f;
				}
			}
		}
	}

	//移除落到游戏窗口外的对象
	m_vD.erase(std::remove_if(m_vD.begin(), m_vD.end(),
		[&](auto &lhs)->bool
	{
		return (!g_game->GetRectF().Contains(lhs.m_pos));
	}), m_vD.end());
}

bool CShooter2Mark::IsChanging() const
{
	return ~m_vD.empty();
}
