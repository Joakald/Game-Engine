#pragma once
#include "Windows.h"

class HPTimer
{
public:
	// constructor
	HPTimer()
	{
		LARGE_INTEGER t; // 64-bit integer
		QueryPerformanceFrequency(&t); // set frequency
		Frequency = t.QuadPart; // convert from large integer to long long
		if (!QueryPerformanceCounter(&t)) // populate t with the start time
		{
			//throw error
		}
		StartTime = t.QuadPart;
		CurrentCallToUpdate = t.QuadPart;
		LastCallToUpdate = t.QuadPart;
	}
public:
	void UpdateTime()
	{
		// get the time for the last and current call to update
		LastCallToUpdate = CurrentCallToUpdate;
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		CurrentCallToUpdate = t.QuadPart;
	}
	double GetTimeTotal()
	{
		double d = (double)((CurrentCallToUpdate - StartTime) / Frequency);
		return d;
	}
	double GetTimeDelta()
	{
		// the time between frames, in seconds
		double d = (double)(CurrentCallToUpdate - LastCallToUpdate);
		return d / Frequency;
	}
private:
	long long StartTime; // the last time we reset the timer (our zero time)
	long long LastCallToUpdate;
	long long CurrentCallToUpdate;
	long long Frequency;
};