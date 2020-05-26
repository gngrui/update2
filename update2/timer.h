#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer()
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		mSecondsPerCount = 1.0 / (double)countsPerSec;
	};
	float DeltaTime() const;

	void Reset();
	void Tick();

	void Pause();
	void Start();

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool m_pause = false;
};