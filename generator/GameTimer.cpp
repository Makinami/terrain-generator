#include <Windows.h>
#include "GameTimer.h"

GameTimer::GameTimer()
{
	__int64 countsPerSecond;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond);
	mSecondsPerCount = 1.0 / (double)countsPerSecond;
}

// Returns the total time elapsed since Reset() was called, NOT counting any
// time when the clock was paused.
float GameTimer::TotalTime() const
{
	if (mStopped)
		return (float)(((mStopTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	else
		return (float)(((mCurrTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
}

float GameTimer::DeltaTime() const
{
	return (float)mDeltaTime;
}

void GameTimer::Reset()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mCurrTime);

	mBaseTime = mCurrTime;
	mPrevTime = mCurrTime;
	mStopTime = 0;
	mPausedTime = 0;
	mStopped = false;
}

void GameTimer::Start()
{
	if (!mStopped) return;

	QueryPerformanceCounter((LARGE_INTEGER*)&mCurrTime);
	
	mPausedTime += (mCurrTime - mStopTime);
	
	mPrevTime = mCurrTime;
	mStopTime = 0;
	mStopped = false;
}

void GameTimer::Stop()
{
	if (mStopped) return;

	QueryPerformanceCounter((LARGE_INTEGER*)&mCurrTime);
	mStopTime = mCurrTime;
	mStopped = true;
}

void GameTimer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0f;
		return;
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&mCurrTime);

	mDeltaTime = (mCurrTime - mPrevTime)*mSecondsPerCount;

	mPrevTime = mCurrTime;

	if (mDeltaTime < 0.0)
		mDeltaTime = 0.0;
}