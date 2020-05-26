#include "timer.h"

float Timer::DeltaTime()const
{
	return (float)mDeltaTime;
}

void Timer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
}

void Timer::Tick()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	// Time difference between this frame and the previous.
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	// Prepare for next frame.
	mPrevTime = mCurrTime;

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
	// processor goes into a power save mode or we get shuffled to another
	// processor, then mDeltaTime can be negative.
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}

void Timer::Pause()
{
	if(!m_pause)
		m_pause = true;
}

void Timer::Start()
{
	if (m_pause)
	{
		m_pause = false;
		__int64 startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
		mPrevTime = startTime;
		m_pause = false;
	}
}
