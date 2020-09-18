
#pragma once
#include <avr/io.h>

template<uint8_t N> class MovingAverage
{
public:
	MovingAverage()
	:m_samples{0}
	,m_currentPos(0)
	{}

	~MovingAverage() = default;

	uint16_t getValue(uint16_t nextSampleIn)
	{
		m_samples[m_currentPos] = nextSampleIn;
		updateCurrentPos();
		return calculateAvg();
	}
private:

	uint16_t calculateAvg() const
	{
		uint16_t sum = 0;
		for(uint8_t i = 0; i < N; ++i)
		{
			sum+=m_samples[i];
		}

		return sum / N;
	}

	void updateCurrentPos()
	{
		m_currentPos++;
		if(m_currentPos == N)
			m_currentPos=0;
	}

private:
	uint16_t m_samples[N]; //buffer of samples, used in a circular manner
	uint8_t m_currentPos;
};

