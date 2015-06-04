#include "Engine.h"
//#include "Path.h"
//#include "AnimationMath.h"

// include something here

Path::Path()
{
	totalTime = 1.0f;
	looping = true;
	cycling = false;
	running = false;

	// TO-DO
	//	- initialize anything else that doesn't exist yet
	// i = 0
	// i + 1 = 1
	currentWaypointIndex = 0;
	nextWaypointIndex = 1;
	currentTime = t = 0.f;
}

Path::Path(float time, bool loop, bool cycle)
{
	totalTime = time > 0 ? time : 0;
	looping = loop;
	cycling = cycle;
	running = false;

	// TO-DO
	//	- the same
	currentWaypointIndex = 0;
	nextWaypointIndex = 1;
	currentTime = t = 0.f;
}



void Path::AddWaypointToEnd(const Vec3 newWaypoint)
{
	// TO-DO
	//	- only perform this action if the path is not 
	//	being animated!

	if (!running)
	{
		waypoints.push_back(newWaypoint);
	}
}

void Path::RemoveLastWaypoint()
{
	// TO-DO
	//	- the same
	if (!running)
	{
		waypoints.pop_back();
	}
}

void Path::RemoveAllWaypoints()
{
	// TO-DO
	//	- the same

	if (!running)
	{
		waypoints.clear();
	}
}


void Path::SetTotalTime(float time)
{
	// TO-DO
	//	- the same
	//	- what is a restriction on time?
	//	- set the total time
	//	- figure out how much time per 'segment'

	if (!running && time > 0)
	{
		totalTime = time;
		unsigned int numSegments = cycling ? (waypoints.size()) : waypoints.size() - 1;

		segmentTime = totalTime / (float)numSegments;
	}
}


void Path::Reset()
{
	running = false;

	// TO-DO
	//	- reset all our indices and timers
	currentWaypointIndex = 0;
	nextWaypointIndex = 1;
	currentTime = t = 0.f;

	if(waypoints.size())
		currentState = waypoints[0];
}


void Path::Update(float dt)
{
	// TO-DO
	//	- only if running
	//	- increment current time and check if it is 
	//	time to go to the next frame
	// - compute 't' and current state

	float p0, p1, p2, p3;
	p0 = p1 = p2 = p3 = currentWaypointIndex;

	if (running)
	{
		currentTime += dt;

		if (currentTime > segmentTime)
		{
			NextWaypoint();
		}

		t = currentTime/segmentTime; //0..1

		//currentState = LERP(waypoints[currentWaypointIndex], waypoints[nextWaypointIndex], t);

		if (waypoints.size() == 2)
		{
			p0 = currentWaypointIndex;
			p1 = currentWaypointIndex;
			p2 = nextWaypointIndex;
			p3 = nextWaypointIndex;
		}
		else if (waypoints.size() > 2)
		{
			p0 = (currentWaypointIndex == 0) ? 0 : currentWaypointIndex-1;
			p1 = currentWaypointIndex;
			p2 = nextWaypointIndex;
			p3 = (nextWaypointIndex + 1 >= waypoints.size()) ? nextWaypointIndex : nextWaypointIndex + 1;
		}
		Vec3 temp = Vec3(0,0,0);

		currentState = CatmullRom(waypoints[p0], waypoints[p1], waypoints[p2], waypoints[p3], t);

	}
}


void Path::NextWaypoint()
{
	// TO-DO
	//	- change our time so that it reflects that we 
	//	are now traversing a new segment of the path
	//	- use what we know about the path as a whole
	//	(its properties) to figure out which waypoint 
	//	is to be set as our next guiding keyframe
	//	(i.e. our new 'p1')

	currentTime -= segmentTime;

	currentWaypointIndex = nextWaypointIndex;

	if (currentWaypointIndex < waypoints.size()-1)
	{
		nextWaypointIndex++;
	}
	else if (cycling)
	{
		nextWaypointIndex = 0;
	}
	else if (looping)
	{
		currentWaypointIndex = 0;
		nextWaypointIndex = 1;
	}
	else
	{

	}

}
