#ifndef _PATH_H
#define _PATH_H
#include "Vec3.h"


//#include "Include/SFML/Graphics.hpp"

// want to create a class that is responsible for managing 
//	a path comprised of several 2D waypoints; an object can 
//	use this path and get the current position
// our first implementation will be controlled with LERP, 
//	but it should later be as general purpose as possible!
class Path
{
public: 

	// ctors
	Path();
	Path(float time, bool loop, bool cycle);

	// set properties of the path: 
	//	total time? does it loop? is the end 
	//	connected back to the beginning (cyclical)
	inline void SetLooping(bool loop) { looping = loop; }
	inline void SetCycling(bool cycle) { cycling = cycle; }

	// get properties
	inline bool GetLooping() const { return looping; }
	inline bool GetCycling() const { return cycling; }

	// add and remove waypoints
	void AddWaypointToEnd(Vec3 newWaypoint);
	void RemoveLastWaypoint();
	void RemoveAllWaypoints();

	// set the total duration of the path animation
	// should be done after all of the waypoints are added, 
	//	right before we start animating with this path
	// **** why?
	void SetTotalTime(float time);

	// start and stop animating along the path
	inline void Start() { running = true; }
	inline void Stop() { running = false; }

	// stop go back to start of path
	void Reset();

	// actually update over time!
	void Update(float dt);

	// **** get our current state!!!!
	inline Vec3 GetCurrentState() const {return currentState;}

	unsigned int currentWaypointIndex;

	std::vector<Vec3> waypoints;
private: 

	// function to increment the waypoint properly
	void NextWaypoint();


	// **** need something to store our waypoints
	//std::vector<Vec3> waypoints;


	// **** how do we know our current point of reference?
	// i.e. our current 'p0' and 'p1' for use in any algorithm
	unsigned int nextWaypointIndex;

	// **** how long is each 'segment' of the path?
	//	assume evenly divided for now
	float segmentTime;

	// **** what is our current time within the current 
	//	segment?
	// in seconds
	float currentTime;


	// **** how do we know our relative state at the 
	//	current frame?
	float t;

	// **** what is our current state?
	Vec3 currentState;

	// additional properties that tell us about 
	//	the behaviour of the path as a whole
	// 1) what is the total duration of the path?
	//	need to know this since we are using time to 
	//	control our beloved 't' parameter...
	float totalTime;
	// 2) does it loop?
	bool looping;
	// 3) is there a 'segment' that connects the end 
	//	back to the start (first key to last key)?
	//	i.e. does the path cycle or just warp back to 
	//	the beginning when it ends
	bool cycling;
	// 4) are we currently running or stopped?
	bool running;

};


#endif	// _PATH_H
