#pragma once

#include "Event.h"
#include "Entity.h"
#include "headfile.h"
#include "Job.h"
#include "Problem.h"

class CSimulator
{
private:
	double _simulationTime;
	int _arriveEvent;
	int _departureEvent;
	int _endSimulationEvent;
	int _nextEventType;

	CEvent _myEvent;
	CEntity _myEntity;
	vector <CEvent> _eventList;
	vector <vector<CEntity>> _queues;

	int*_nBusyMachines;
	int* _nIdleMachines;


	CJob* _jobInformation;
	int* _permutation;
	double* _completionTime;
	CProblem problem;

public:
	CSimulator(CProblem& pbl, int* permutation);
	void InitSimulationEnvironment();
	   
	void DiscreteEventSimulation(double* completionTime);
	void Arrive();
	void Depart();
	void SelectNextEvent();
	void EventSchedule();
	void EndSimulation();
};