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
map<string, pair<int,int>> CalculateMapTurnover;
map<string, pair<int, int>> CalculateMapResponse;

queue<Job> FIFOQueue;
deque<Job> SJFQueue;
deque<Job> RRQueue;
//vector<Job> SJFvec;

void testInput();
void FIFO();
void SJF();
void STCF();
void RR(int stepCount);
void Calculate(map<string, pair<int, int>> m);
bool SJFComparator(Job a, Job b);
bool STCFComprator(Job x, Job y);

int main()
{
	cout << "Running Project" << endl;
	
	testInput();
	
	cout << "FIFO" << endl;
	
	cout << "Time:" << "\t\tName:" << "\t\tArrivalTime:" << "\t\tDuration:" << endl;
	//first in first out
	FIFO();
	
	cout << " " << endl;
	cout << "Turn around "<< endl;
	Calculate(CalculateMapTurnover);
	CalculateMapTurnover.clear();
	
	cout << " " << endl;
	cout << "Response time " << endl;
	Calculate(CalculateMapResponse);
	CalculateMapResponse.clear();

	cout << " " << endl;
	cout << "SJF" << endl;

	time1 = 0;

	cout << "Time:" << "\t\tName:" << "\t\tArrivalTime:" << "\t\tDuration:" << endl;
	//shortest job first
	SJF();

	cout << " " << endl;
	cout << "Turn around " << endl;
	Calculate(CalculateMapTurnover);
	CalculateMapTurnover.clear();

	cout << " " << endl;
	cout << "Response time " << endl;
	Calculate(CalculateMapResponse);
	CalculateMapResponse.clear();

	cout << " " << endl;
	cout << "STCF" << endl;

	time1 = 0;

	cout << "Time:" << "\t\tName:" << "\t\tArrivalTime:" << "\t\tDuration:" << endl;
	//shortest time to completion
	STCF();

	cout << " " << endl;
	cout << "Turn around " << endl;
	Calculate(CalculateMapTurnover);
	CalculateMapTurnover.clear();

	cout << " " << endl;
	cout << "Response time " << endl;
	Calculate(CalculateMapResponse);
	CalculateMapResponse.clear();


	cout << " " << endl;
	cout << "RR" << endl;

	time1 = 0;

	cout << "Time:" << "\t\tName:" << "\t\tArrivalTime:" << "\t\tDuration:" << endl;

	RR(1);

	cout << " " << endl;
	cout << "Turn around " << endl;
	Calculate(CalculateMapTurnover);
	CalculateMapTurnover.clear();

	cout << " " << endl;
	cout << "Response time " << endl;
	Calculate(CalculateMapResponse);
	CalculateMapResponse.clear();

	cout << " " << endl;
	cout << "RR2" << endl;

	time1 = 0;

	cout << "Time:" << "\t\tName:" << "\t\tArrivalTime:" << "\t\tDuration:" << endl;

	RR(2);

	cout << " " << endl;
	cout << "Turn around " << endl;
	Calculate(CalculateMapTurnover);
	CalculateMapTurnover.clear();

	cout << " " << endl;
	cout << "Response time " << endl;
	Calculate(CalculateMapResponse);
	CalculateMapResponse.clear();

	cout << "" << endl;
	cout << "Simulation Complete" << endl;
	
	//prevents console window closing instantly
	system("pause");
}

void testInput()
{
	string name1 = "";
	int arrivalTime1 = 0;
	int inputDuration = 0;
	int count1 = 0;

	while (cin) {
		cin >> name1 >> arrivalTime1 >> inputDuration;
		jobsTable[count1] = (Job(name1, arrivalTime1, inputDuration));
		count1++;
	}

	/*jobsTable[0] = Job("job1", 2, 5);
	jobsTable[1] = Job("job2", 3, 7);
	jobsTable[2] = Job("job3", 7, 2);
	jobsTable[3] = Job("job4", 12, 5);
	jobsTable[4] = Job("job5", 9, 4);
	jobsTable[5] = Job("job6", 11, 6);*/
	
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
				cout << "Arrival" << "\t\t" << it->second.mName << "\t\t" << it->second.mArrivalTime << "\t\t\t" << it->second.mDuration << '\n';		
				CalculateMapTurnover[it->second.mName].first = it->second.mArrivalTime;
				CalculateMapResponse[it->second.mName].first = it->second.mArrivalTime;
				FIFOQueue.push(it->second);
			}
			else 
			{
			
			}	
		}
		if (!FIFOQueue.empty())
		{
			FIFOQueue.front().mIsJobCompleted++;
			cout <<time1 << "\t\t" << FIFOQueue.front().mName << "\t\t" << FIFOQueue.front().mArrivalTime << "\t\t\t" << FIFOQueue.front().mDuration << endl;
			
			if (!CalculateMapResponse[FIFOQueue.front().mName].second) {
				CalculateMapResponse[FIFOQueue.front().mName].second = (time1 != 0) ? time1 : -1;
			}

			if (FIFOQueue.front().mDuration == FIFOQueue.front().mIsJobCompleted)
			{
				CalculateMapTurnover[FIFOQueue.front().mName].second= time1;
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
				cout << "Arrival" << "\t\t" << it->second.mName << "\t\t" << it->second.mArrivalTime << "\t\t\t" << it->second.mDuration << '\n';
				CalculateMapTurnover[it->second.mName].first = it->second.mArrivalTime;
				CalculateMapResponse[it->second.mName].first = it->second.mArrivalTime;
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
				CalculateMapTurnover[SJFQueue.front().mName].second = time1;
				SJFQueue.pop_front();
				//cout << "time: " << time << " Name: " << SJFQueue.front().mName << " Arrival Time: " << SJFQueue.front().mArrivalTime << " Duration: " << SJFQueue.front().mDuration << endl;
				if (!SJFQueue.empty())
				{
					sort(SJFQueue.begin(), SJFQueue.end(), &SJFComparator);
				}			
			}
			if (!SJFQueue.empty())
			{
				if (!CalculateMapResponse[SJFQueue.front().mName].second) {
					CalculateMapResponse[SJFQueue.front().mName].second = (time1 != 0) ? time1 : -1;
				}
				cout  << time1  << "\t\t" << SJFQueue.front().mName << "\t\t" << SJFQueue.front().mArrivalTime << "\t\t\t" << SJFQueue.front().mDuration << endl;
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
				cout << "Arrival" << "\t\t" << it->second.mName << "\t\t" << it->second.mArrivalTime << "\t\t\t" << it->second.mDuration << '\n';
				
				CalculateMapTurnover[it->second.mName].first = it->second.mArrivalTime;
				CalculateMapResponse[it->second.mName].first = it->second.mArrivalTime;

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
				CalculateMapTurnover[SJFQueue.front().mName].second = time1;
				SJFQueue.pop_front();
				//cout << "time: " << time << " Name: " << SJFQueue.front().mName << " Arrival Time: " << SJFQueue.front().mArrivalTime << " Duration: " << SJFQueue.front().mDuration << endl;			
			}
			if (!SJFQueue.empty())
			{
				if (!CalculateMapResponse[SJFQueue.front().mName].second) {
					CalculateMapResponse[SJFQueue.front().mName].second = (time1 != 0) ? time1 : -1;
				}
				cout << time1 << "\t\t" << SJFQueue.front().mName << "\t\t" << SJFQueue.front().mArrivalTime << "\t\t\t" << SJFQueue.front().mDuration << endl;
			}
		}
	}		
}

bool SJFComparator(Job a, Job b)
{
	/*
	if (a.mDuration == b.mDuration) {
	return true;
	}
	*/
	
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
				cout << "Arrival" << "\t\t" << it->second.mName << "\t\t" << it->second.mArrivalTime << "\t\t\t" << it->second.mDuration << '\n';
				CalculateMapTurnover[it->second.mName].first = it->second.mArrivalTime;
				CalculateMapResponse[it->second.mName].first = it->second.mArrivalTime;
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
				if (!CalculateMapResponse[RRQueue.at(counter).mName].second) {
					CalculateMapResponse[RRQueue.at(counter).mName].second = (time1 != 0) ? time1 : -1;
				}
				cout << time1 << "\t\t" << RRQueue.at(counter).mName << "\t\t" << RRQueue.at(counter).mArrivalTime << "\t\t\t" << RRQueue.at(counter).mDuration << endl;
			}

			if (RRQueue.at(counter).mDuration == RRQueue.at(counter).mIsJobCompleted)
			{
				cout << "Job Completed" << endl;
				CalculateMapTurnover[RRQueue.at(counter).mName].second = time1;
				RRQueue.erase(RRQueue.begin() + counter);
				counter--;
				stepCounter = 0;
			}		
		}	
	}
}

void Calculate(map<string, pair<int, int>> m)
{
	float sumTT =0, countTT =0;
	for (map<string, pair<int, int>>::iterator it = m.begin(); it != m.end(); it++)
	{
		sumTT += it->second.second - it->second.first;
		countTT++;
		cout << it->first << ": " <<  ((it->second.second != -1) ? it->second.second : 0) - it->second.first << endl;
	}
	cout << "Average" << ": " << sumTT/countTT << endl;
}