#pragma once
#include "Job.hpp"
#include<iostream>
#include<map>
#include <queue>
int time = 0;
using namespace std;
map<int, Job> jobsTable;
queue<Job> FIFOQueue;
void testInput();
void FIFO();
int main()
{
	
	cout << "Running Project" << endl;
	
	testInput();
	
	cout << "FIFO" << endl;
	
	FIFO();

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
	for (time; time < 400; time++)
	{
		for (map<int, Job>::iterator it = jobsTable.begin(); it != jobsTable.end(); it++)
		{
			if (it->second.mArrivalTime == time)
			{
				cout << it->first << " Name: " << it->second.mName << " ArrivalTime: " << it->second.mArrivalTime << " Duration: " << it->second.mDuration << '\n';
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
		//time++;
	}
	//if arrives set it to be queued for update
	//update current job

	//check if job completed

	//increase time

	//do again
}