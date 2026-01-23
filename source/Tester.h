#pragma once
#include "Synthesizer.h"
#include "TimeManager.h"

typedef int note;

struct timestamp
{
public:
	int tick;
	std::vector<note> notes;
	timestamp(int t, std::initializer_list<note> n)
		: tick(t), notes(n) {
	}
};

struct Song
{
public:
	Song(std::vector<timestamp> coreography) : timeline(coreography) 
	{
	}
	void Init() 
	{
		tracker = Time::RequestTracker(0.0f);
	}
	void SetResolution(float ticksPerSecond) { resolution = ticksPerSecond; }
	timestamp Advance()
	{
		float timePassed = static_cast<float>(tracker->GetTimePassed());
		int targetTick = static_cast<int>(timePassed * resolution);
		if (targetTick < timeline.size())
		{
			timestamp& ts = timeline[targetTick];
			return ts;
		}
		else
		{
			tracker->CheckOnce(); // reset timer
			return timeline[0];
		}
		//return timestamp(-1, {});
	}
	std::shared_ptr<Time::TimeTracker> GetTracker() { return tracker; }
private:
	std::vector<timestamp> timeline;
	float resolution; // ticks per second
	std::shared_ptr<Time::TimeTracker> tracker;
};


class Tester
{
public:
	void Init();
	void RunTests();
private:
	int currentTick = 0;
	float resolution = 6.0f; // ticks per second
	std::vector<note> activeNotes;
	std::shared_ptr<Time::TimeTracker> tracker;

	bool initialized = false;
};


