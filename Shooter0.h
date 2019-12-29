#pragma once
#include "Shooter.h"
#include "GameTimer.h"

/*
 * ������
 */
class CShooter0 :
	public CShooter
{
public:
	CShooter0();
	virtual ~CShooter0();

	virtual void Draw(Gdiplus::Graphics& gh) override;

	//���������Ϣ
	virtual bool OnLButtonDown(UINT nFlags, CPoint point) override;
	virtual bool OnRButtonDown(UINT nFlags, CPoint point) override;
private:
	std::vector<Image* > m_vImage;
	typedef enum
	{
		EStatus0 = 0,
		EStatusMove0,		//��
		EStatusMove1,		//����
		EStatusMove2,		//��
		EStatusMove3,		//����
		EStatusMove4,		//��
		EStatusMove5,		//����
		EStatusMove6,		//��
		EStatusMove7,		//����
		EStatusFireLeft,	//��������
		EStatusFireRight,	//��������
	}EStatus;

	EStatus m_eStatus{ EStatus0 };

	// ��ǰ��ʾ��ͼƬ
	size_t m_index = 0;
	//û�ж���ʱ�����»ζ�

	CGameTimeval m_timer0{ 500 };
	// ��¼��ǰ������ ��������
	bool m_bUp = false;
	/*
	 * ��ĳ���������ƶ�
	 * ��ʼ�ƶ�
	 * �����ָ���ֹ״̬
	 */
	void DrawMove(Gdiplus::Graphics &gh);

	// ����Ҽ�������λ��
	PointF m_moveTo;
	//�ƶ��ķ���
	float m_moveDir;

	/*
	 * ���𶯻�����������4�嶯��
	 * 0ԭ��ת��
	 * 1�ۼ�����
	 * 2�ۼ�����
	 * 3�����ʼ
	 * 4�����
	 * 5������
	 */
	//��֡ͼƬ֮���ʱ����
	CGameTimeval m_timeFire{ 100 };

	//  ��ǰ��ʾ�ڼ���ͼƬ
	size_t m_index_fire = 0;
	//���ƿ��𶯻�
	void DrawFire(Gdiplus::Graphics &gh);

	// ����Ҽ�������λ��
	PointF m_fireTo;
};

