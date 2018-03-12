#pragma once
#include "Job.hpp"
#include<iostream>
#include<map>
#include <queue>
#include <vector>

int time = 0;
int time2 = 0;
using namespace std;
map<int, Job> jobsTable;
queue<Job> FIFOQueue;
deque<Job> SJFQueue;
vector<Job> SJFvec;

void testInput();
void FIFO();
void SJF();
void STCF();
void RR();
void RR2();
bool SJFComparator(Job a, Job b);
bool STCFComprator(Job x, Job y);

int main()
{
	cout << "Running Project" << endl;
	
	testInput();
	
	cout << "FIFO" << endl;
	
	//first in first out
	FIFO();

	cout << " " << endl;
	cout << "SJF" << endl;

	time = 0;

	//shortest job first
	SJF();
	
	cout << " " << endl;
	cout << "STCF" << endl;

	time = 0;

	//shortest time to completion
	STCF();
	
	//RR();
	
	//RR2();

	//prevents console window closing instantly
	system("pause");
}

void testInput()
{
	jobsTable[0] = Job("job1", 2, 5);
	jobsTable[1] = Job("job2", 3, 7);
	jobsTable[2] = Job("job3", 7, 2);
	jobsTable[3] = Job("job4", 12, 5);
	jobsTable[4] = Job("job5", 9, 4);
	jobsTable[5] = Job("job6", 11, 6);
	

	//Print out job names
	for (map<int, Job>::iterator it = jobsTable.begin(); it != jobsTable.end(); ++it)
		cout << it->first << " Name: " << it->second.mName << " ArrivalTime: " << it->second.mArrivalTime << " Duration: " << it->second.mDuration <<'\n';
	cout << " " << endl;
}

void FIFO()
{
	
	//check if job arrives based on current time
	for (time; time < 100; time++)
	{
		for (map<int, Job>::iterator it = jobsTable.begin(); it != jobsTable.end(); it++)
		{
			if (it->second.mArrivalTime == time)
			{
				cout << it->first << "  Name: " << it->second.mName << " ArrivalTime: " << it->second.mArrivalTime << " Duration: " << it->second.mDuration << '\n';
				FIFOQueue.push(it->second);
			
			}
			else 
			{
			
			}
		}
		if (!FIFOQueue.empty())
		{
			FIFOQueue.front().mIsJobCompleted++;
			cout << "time: "<<time << " Name: " << FIFOQueue.front().mName << " Arrival Time: " << FIFOQueue.front().mArrivalTime << " Duration: " << FIFOQueue.front().mDuration << endl;
			if (FIFOQueue.front().mDuration == FIFOQueue.front().mIsJobCompleted)
			{
				cout << "Job Completed" << endl;
				
				FIFOQueue.pop();

			}
		}
	}
}


void SJF()
{
	for (time; time < 100; time++)//seems to start at 400
	{
		for (map<int, Job>::iterator it = jobsTable.begin(); it != jobsTable.end(); it++)
		{
			if (it->second.mArrivalTime == time)
			{
				
				cout << it->first << " Name: " << it->second.mName << " ArrivalTime: " << it->second.mArrivalTime << " Duration: " << it->second.mDuration << '\n';
	
				SJFQueue.push_back(it->second);
			}
		
		}

	
		if (!SJFQueue.empty())
		{
			SJFQueue.front().mIsJobCompleted++;
			//no values except time passed in not sure why ?
			//cout << "time: " << time << " Name: " << SJFQueue.front().mName << " Arrival Time: " << SJFQueue.front().mArrivalTime << " Duration: " << SJFQueue.front().mDuration << endl;
			if (SJFQueue.front().mDuration == SJFQueue.front().mIsJobCompleted)
			{
				cout << "Job Completed" << endl;
				SJFQueue.pop_front();
				//cout << "time: " << time << " Name: " << SJFQueue.front().mName << " Arrival Time: " << SJFQueue.front().mArrivalTime << " Duration: " << SJFQueue.front().mDuration << endl;
				if (!SJFQueue.empty())
				{
					sort(SJFQueue.begin(), SJFQueue.end(), &SJFComparator);
				}
				
				
			}
			if (!SJFQueue.empty())
			{
				cout << "time: " << time << " Name: " << SJFQueue.front().mName << " Arrival Time: " << SJFQueue.front().mArrivalTime << " Duration: " << SJFQueue.front().mDuration << endl;
			}
		}
	
	}
}

void STCF()
{
	/*
	for (time; time < 100; time++)//seems to start at 400
	{
		for (map<int, Job>::iterator it = jobsTable.begin(); it != jobsTable.end(); it++)
		{
			if (it->second.mArrivalTime == time)
			{
				cout << it->first << " Name: " << it->second.mName << " ArrivalTime: " << it->second.mArrivalTime << " Duration: " << it->second.mDuration << '\n';

				SJFQueue.push_back(it->second);
			}
		}
		if (!SJFQueue.empty())
		{
			SJFQueue.front().mIsJobCompleted++;
			//no values except time passed in not sure why ?
			//cout << "time: " << time << " Name: " << SJFQueue.front().mName << " Arrival Time: " << SJFQueue.front().mArrivalTime << " Duration: " << SJFQueue.front().mDuration << endl;
			if (SJFQueue.front().mDuration == SJFQueue.front().mIsJobCompleted)
			{
				cout << "Job Completed" << endl;
				SJFQueue.pop_front();
				//cout << "time: " << time << " Name: " << SJFQueue.front().mName << " Arrival Time: " << SJFQueue.front().mArrivalTime << " Duration: " << SJFQueue.front().mDuration << endl;
				if (!SJFQueue.empty())
				{
					sort(SJFQueue.begin(), SJFQueue.end(), &SJFComparator);
				}
			}
			if (!SJFQueue.empty())
			{
				cout << "time: " << time << " Name: " << SJFQueue.front().mName << " Arrival Time: " << SJFQueue.front().mArrivalTime << " Duration: " << SJFQueue.front().mDuration << endl;
			}
		}
	}	
	*/	
}

bool SJFComparator(Job a, Job b)
{
	if (a.mDuration == b.mDuration) {
		return true;
	}
	return a.mDuration < b.mDuration;
	
}

bool STCFComprator(Job x, Job y) {
	if (x.mDuration == y.mDuration) {
		return true;
	}
	return x.mDuration < y.mDuration;
}

void RR()
{

}