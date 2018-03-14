#include "Job.hpp"
#include<iostream>
#include<map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int time1 = 0;
int counter = 0;
int totalDuration = 0;

map<int, Job> jobsTable;
map<string, pair<int,int>> CalculateMap;

queue<Job> FIFOQueue;
deque<Job> SJFQueue;
deque<Job> RRQueue;
//vector<Job> SJFvec;

void testInput();
void FIFO();
void SJF();
void STCF();
void RR(int stepCount);
bool SJFComparator(Job a, Job b);
bool STCFComprator(Job x, Job y);

int main()
{
	cout << "Running Project" << endl;
	
	testInput();
	
	cout << "FIFO" << endl;
	
	cout << "time:" << "\tName:" << "\tArrivalTime:" << "\tDuration:" << endl;
	//first in first out
	FIFO();

	cout << " " << endl;
	cout << "SJF" << endl;

	time1 = 0;

	cout << "time:" << "\tName:" << "\tArrivalTime:" << "\tDuration:" << endl;
	//shortest job first
	SJF();
	
	cout << " " << endl;
	cout << "STCF" << endl;

	time1 = 0;

	cout << "time:" << "\tName:" << "\tArrivalTime:" << "\tDuration:" << endl;
	//shortest time to completion
	STCF();
	
	cout << " " << endl;
	cout << "RR" << endl;

	time1 = 0;

	cout << "time:" << "\tName:" << "\tArrivalTime:" << "\tDuration:" << endl;

	RR(1);

	cout << " " << endl;
	cout << "RR2" << endl;

	time1 = 0;

	cout << "time:" << "\tName:" << "\tArrivalTime:" << "\tDuration:" << endl;

	RR(2);
	
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
	
	for (time1; time1 < 100; time1++)
	{
		//turn around time  = completion time - arrival
		//response time = start time - arrival time

		for (map<int, Job>::iterator it = jobsTable.begin(); it != jobsTable.end(); it++)
		{
			if (it->second.mArrivalTime == time1)
			{		
				cout << "Arrival" << "\t" << it->second.mName << "\t" << it->second.mArrivalTime << "\t" << it->second.mDuration << '\n';		
				FIFOQueue.push(it->second);
			}
			else 
			{
			
			}	
		}
		if (!FIFOQueue.empty())
		{
			FIFOQueue.front().mIsJobCompleted++;
			cout <<time1 << "\t" << FIFOQueue.front().mName << "\t" << FIFOQueue.front().mArrivalTime << "\t" << FIFOQueue.front().mDuration << endl;
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
	for (time1; time1 < 100; time1++)//seems to start at 400
	{
		for (map<int, Job>::iterator it = jobsTable.begin(); it != jobsTable.end(); it++)
		{
			if (it->second.mArrivalTime == time1)
			{		
				//cout << it->first << " Name: " << it->second.mName << " ArrivalTime: " << it->second.mArrivalTime << " Duration: " << it->second.mDuration << '\n';
				cout << "Arrival" << "\t" << it->second.mName << "\t" << it->second.mArrivalTime << "\t" << it->second.mDuration << '\n';
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
				cout  << time1  << "\t" << SJFQueue.front().mName << "\t" << SJFQueue.front().mArrivalTime << "\t" << SJFQueue.front().mDuration << endl;
			}
		}
	}
}

void STCF()
{
	for (time1; time1 < 100; time1++)//seems to start at 400
	{
		for (map<int, Job>::iterator it = jobsTable.begin(); it != jobsTable.end(); it++)
		{
			if (it->second.mArrivalTime == time1)
			{
				//cout << " Name: " << it->second.mName << " ArrivalTime: " << it->second.mArrivalTime << " Duration: " << it->second.mDuration << '\n';
				cout << "Arrival" << "\t" << it->second.mName << "\t" << it->second.mArrivalTime << "\t" << it->second.mDuration << '\n';

				SJFQueue.push_back(it->second);
				if (!SJFQueue.empty())
				{
					sort(SJFQueue.begin(), SJFQueue.end(), &SJFComparator);
				}
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
			}
			if (!SJFQueue.empty())
			{
				cout << time1 << "\t" << SJFQueue.front().mName << "\t" << SJFQueue.front().mArrivalTime << "\t" << SJFQueue.front().mDuration << endl;
			}
		}
	}		
}

bool SJFComparator(Job a, Job b)
{
	if (a.mDuration == b.mDuration) {
		return true;
	}
	return a.mDuration < b.mDuration;
}

void RR(int stepSize)
{
	
	int stepCounter = 0;
	for (time1; time1 < 100; time1++)//seems to start at 400
	{
		for (map<int, Job>::iterator it = jobsTable.begin(); it != jobsTable.end(); it++)
		{
			if (it->second.mArrivalTime == time1)
			{
				//cout << " Name: " << it->second.mName << " ArrivalTime: " << it->second.mArrivalTime << " Duration: " << it->second.mDuration << '\n';
				cout << "Arrival" << "\t" << it->second.mName << "\t" << it->second.mArrivalTime << "\t" << it->second.mDuration << '\n';
				
				RRQueue.push_back(it->second);			
			}	
		}	
		
		if (!RRQueue.empty())
		{
			if (stepCounter == stepSize) {
				counter++;
				stepCounter = 0;
			}
			
			if (RRQueue.size() <= counter)
			{
				counter = 0;
			}
		
			RRQueue.at(counter).mIsJobCompleted++;
			stepCounter++;

			if (!RRQueue.empty())
			{
				cout << time1 << "\t" << RRQueue.at(counter).mName << "\t" << RRQueue.at(counter).mArrivalTime << "\t" << RRQueue.at(counter).mDuration << endl;
			}

			if (RRQueue.at(counter).mDuration == RRQueue.at(counter).mIsJobCompleted)
			{
				cout << "Job Completed" << endl;
				RRQueue.erase(RRQueue.begin() + counter);
				counter--;
				stepCounter = 0;
			}		
		}	
	}
	
}

