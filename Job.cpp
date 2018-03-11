#pragma once
#include "Job.hpp"

Job::Job() 
{

}

Job::Job(string name, int arrivalTime, int duration) : mName(name) , mArrivalTime(arrivalTime), mDuration(duration), mIsJobCompleted(0)
{

}

Job::~Job()
{

}