#pragma once
#include <string>
// i know its bad practice but i find it much simpler using name space then using std everywhere
using namespace std;

class Job
{
public:
	Job();
	Job(string name, int arrivalTime, int duration);
	~Job();
	
	string mName;
	int mDuration;
	int mArrivalTime;

	int mIsJobCompleted;
};