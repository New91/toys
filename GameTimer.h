#pragma once

#include <windows.h>

class CGameTimer
{
public:
	explicit  CGameTimer(unsigned int timeout = 3000,
						unsigned int timeval = 300)
		:m_timeout(timeout)
	,m_timeval(timeval)
	{
		
	}
	virtual ~CGameTimer(){}
	//����ʱ����
	void SetTimeval(unsigned int timeval)
	{
		m_timeval = timeval;
	}

	//������һ��ʱ��
	void SetLastTime()
	{
		m_timeLast = GetTickCount();
	}

	//������ʼʱ��Ϊ��ǰʱ��
	void StartTimer()
	{
		m_timeStart = ::GetTickCount();
		m_times = 0;
	}

	//�����ܳ�ʱʱ��
	void SetTimeout(unsigned int timeout)
	{
		m_timeout = timeout;
	}
	//�ж��Ƿ�ʱ����ʱ�䣩
	bool IsTimeOut() const
	{
		return (GetTickCount() - m_timeStart) >= m_timeout;
	}

	//�ж��Ƿ񵽴�ʱ���� ������ˣ� �Ƿ����
	bool IsTimeval(bool bUpdate = true)
	{
		if((GetTickCount() - m_timeLast) >= m_timeval)
		{
			if(bUpdate)
			{
				m_timeLast = GetTickCount();
				m_times++;
			}
			return true;
		}else
		{
			return false;
		}
	}
	size_t GetTimes() const
	{
		return m_times;
	}
private:
	unsigned int m_timeStart{ ::GetTickCount() };
	unsigned int m_timeout{ 3000 };
	unsigned int m_timeLast{ m_timeStart };
	unsigned int m_timeval{ 300 };
	unsigned int m_times{ 0 };
};


//�ж�ʱ����
class CGameTimeval
{
public:
	explicit CGameTimeval(unsigned int timeval = 300)
		:m_timeval(timeval)
	{
		
	}
	virtual ~CGameTimeval(){}

	void Restart()
	{
		m_timeLast = GetTickCount();
		m_times = 0;
	}

	void SetTimeval(unsigned int timeval)
	{
		m_timeval = timeval;
	}

	void SetLastTime()
	{
		m_timeLast = GetTickCount();
	}

	//�Ƿ�ﵽ��ʱ������������ˣ��Ƿ����
	bool IsTimeval(bool bUpdate = true)
	{
		if(GetTickCount() - m_timeLast >= m_timeval)
		{
			if(bUpdate)
			{
				m_timeLast = GetTickCount();
				m_times++;
			}
			return true;
		}else
		{
			return false;
		}
	}

	size_t GetTimes() const
	{
		return m_times;
	}
private:
	unsigned int m_timeLast{ GetTickCount() };
	unsigned int m_timeval{ 100 };
	// ����IsTimeval(true)�Ĵ���
	unsigned int m_times{ 0 };
};