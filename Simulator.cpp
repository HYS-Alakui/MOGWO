

#include "headfile.h"
#include "Event.h"
#include "Entity.h"
#include "headfile.h"
#include "Job.h"
#include "Genetic.h"


void CGenetic::InitSimulationEnvironment(CIndividual& t)
{
	_permutation = new int[NJobs];
	for (int i = 0; i < NJobs; i++)
	{
		_permutation[i] = t.v_chromosome[i];
	}
	_completionTime = new double[NJobs];
	TotalEnergyConsumption = 0.0;


	_simulationTime = 0.0;
	_arriveEvent = 1;
	_departureEvent = 2;
	_endSimulationEvent = 3;
	_nextEventType = -1;

	vector <CEvent>().swap(_eventList);
	vector <vector <CEntity>>().swap(_queues);
	for (int i = 0; i < NWorkstations; i++)
	{
		vector <CEntity> l;
		_queues.push_back(l);
	}
	_nBusyMachines = new int [NWorkstations];
	_nProcessedJobs = new int[NWorkstations];
	_nIdleMachines = new int[NWorkstations];
	for (int i = 0; i < NWorkstations; i++)
	{
		_nBusyMachines[i] = 0;
		_nProcessedJobs[i] = 0;
		_nIdleMachines[i] = 0;
	}
	//initialize the event list;
	_jobInformation = new CJob [NJobs];
	for (int i = 0; i < NJobs; i++)
	{
		_myEvent.EventTime = _simulationTime;
		_myEvent.EventType = _arriveEvent;
		_myEvent.JobNo = _permutation[i];
		_myEvent.StageNo = 1;
		_myEvent.WorkstationIndex = -1;

		EventSchedule();

		CJob job;
		for (int j = 0; j < NWorkstations; j++)
		{
			job.ProcessTime.push_back(ProcessTime[j][i]);

			if (j + 1 <= NWorkstationsAtStage1)
			{
				job.RestWorkstationsAtStage1.push_back(j + 1);
			}
			if (j + 1 > NWorkstationsAtStage1)
			{
				job.RestWorkstationsAtStage2.push_back(j + 1);
			}
			job.EnergyConsumption.push_back(EnergyConsumption[j][i]);
		}
		job.DueDate = DueDate[i];
		job.StageIndex = 1;
		_jobInformation[i] = job;
	}
	//create the end simulation event.

	_myEvent.EventTime = INF_DOUBLE_MAX;
	_myEvent.EventType = _endSimulationEvent;
	_myEvent.JobNo = -1;
	_myEvent.StageNo = -1;
	_myEvent.WorkstationIndex = -1;
	
	EventSchedule();
}

void CGenetic::EndSimulation()
{
	delete[] _jobInformation;
	delete[] _permutation;

	delete[] _nBusyMachines;
	delete[] _nIdleMachines;
	delete[] _completionTime;
	delete[] _nProcessedJobs;
}

void CGenetic::DiscreteEventSimulation(CIndividual& t)
{
	double _last_event_time = 0;
	double duration_time;
	int _number_of_idle_machines;

	InitSimulationEnvironment(t);
	while (_nextEventType != _endSimulationEvent)
	{
		SelectNextEvent();
		////////////////////////////////////////////////////////////////
		duration_time = _myEvent.EventTime - _last_event_time;
		for (int i = 0; i < NWorkstations; i++)
		{
			_number_of_idle_machines = NMachines[i] - _nBusyMachines[i];
			if (_nBusyMachines[i] != NMachines[i] && _nProcessedJobs[i] != NJobs)
			{
				TotalEnergyConsumption = TotalEnergyConsumption
					+ duration_time * _number_of_idle_machines * StandbyEnergyConsumption[i];
			}
		}
		_last_event_time = _myEvent.EventTime;


		if (_nextEventType == _arriveEvent)
		{
			Arrive();
		}
		if (_nextEventType == _departureEvent)
		{
			Depart();
		}
		if (_nextEventType == _endSimulationEvent) //calculate objective function values...
		{
			/*
			for (int i = 0; i < problem.NJobs; i++)
			{
				completionTime[i] = _completionTime[i];
			}*/

			//calculate objective values...
			vector <double>().swap(t.v_objective_value);
			double total_tardiness = 0.0;
			for (int i = 0; i < NJobs; i++)
			{
				if (_completionTime[i] > DueDate[i])
				{ 
					total_tardiness = total_tardiness + (_completionTime[i] - DueDate[i]);
				}
			}
			//Calculate energy consumption...
			for (int i = 0; i < NJobs; i++)
			{
				for (int j = 0; j < NWorkstations; j++)
				{
					TotalEnergyConsumption = TotalEnergyConsumption
						+ (_jobInformation[i].ProcessTime[j] * _jobInformation[i].EnergyConsumption[j]);
				}
			}
			t.v_objective_value.push_back(total_tardiness);
			t.v_objective_value.push_back(TotalEnergyConsumption);
		}
	}
	EndSimulation();
}
void CGenetic::Arrive()
{
	int jobNo, stageNo;

	stageNo = _myEvent.StageNo;
	jobNo = _myEvent.JobNo;
	////////////////////////////////////////////////////////////////
	//if this is a new arrival to the system, generate the time of the next
	//arrival and determine the job no and operation no of the arriving job. 
	////////////////////////////////////////////////////////////////
	if (stageNo == 1)   //the arrive event is in the 1# stage.
	{
		//find a workstation with least queue...
		int restWorkstationsAtStage1Count = _jobInformation[jobNo - 1].RestWorkstationsAtStage1.size();
		int minQueueLength = INF_INT_MAX;
		int minWorkstationIndex = 0, workstationIndex = 0;
		for (int i = 0; i < restWorkstationsAtStage1Count; i++)
		{
			workstationIndex = _jobInformation[jobNo - 1].RestWorkstationsAtStage1[i];
			if (minQueueLength > _queues[workstationIndex - 1].size())
			{
				minQueueLength = _queues[workstationIndex - 1].size();
				minWorkstationIndex = workstationIndex;
			}
		}
		if (_nBusyMachines[minWorkstationIndex - 1] == NMachines[minWorkstationIndex - 1])
		{
			//all the machines in this station are busy, put the arrive job into its corresponding queue list.
			//put in its queue list.
			_myEntity.TimeOfArriveToStation = _simulationTime;
			_myEntity.JobNo = jobNo;
			_myEntity.StageNo = stageNo;
			_myEntity.WorkstationIndex = minWorkstationIndex;

			_queues[minWorkstationIndex - 1].push_back(_myEntity);
		}
		else if (_nBusyMachines[minWorkstationIndex - 1] < NMachines[minWorkstationIndex - 1])
		{
			//schedule a departure event about the arrive job.
			_myEvent.EventTime = _simulationTime + _jobInformation[jobNo - 1].ProcessTime[minWorkstationIndex - 1];
			_myEvent.EventType = _departureEvent;
			_myEvent.JobNo = jobNo;
			_myEvent.StageNo = 1;
			_myEvent.WorkstationIndex = minWorkstationIndex;

			EventSchedule();  //departure event.

			_nBusyMachines[minWorkstationIndex - 1] = _nBusyMachines[minWorkstationIndex - 1] + 1;
		}
	}
	else if (stageNo == 2)
	{
		//find a workstation with least queue...
		int restWorkstationsAtStage2Count = _jobInformation[jobNo - 1].RestWorkstationsAtStage2.size();
		int minQueueLength = INF_INT_MAX;
		int minWorkstationIndex = 0, workstationIndex = 0;
		for (int i = 0; i < restWorkstationsAtStage2Count; i++)
		{
			workstationIndex = _jobInformation[jobNo - 1].RestWorkstationsAtStage2[i];
			if (minQueueLength > _queues[workstationIndex - 1].size())
			{
				minQueueLength = _queues[workstationIndex - 1].size();
				minWorkstationIndex = workstationIndex;
			}
		}
		if (_nBusyMachines[minWorkstationIndex - 1] == NMachines[minWorkstationIndex - 1])
		{
			//all the machines in this station are busy, put the arrive job into its corresponding queue list.
			//put in its queue list.
			_myEntity.TimeOfArriveToStation = _simulationTime;
			_myEntity.JobNo = jobNo;
			_myEntity.StageNo = 2;
			_myEntity.WorkstationIndex = minWorkstationIndex;

			_queues[minWorkstationIndex - 1].push_back(_myEntity);
		}
		else if (_nBusyMachines[minWorkstationIndex - 1] < NMachines[minWorkstationIndex - 1])
		{
			//schedule a departure event about the arrive job.		

			_myEvent.EventTime = _simulationTime + _jobInformation[jobNo - 1].ProcessTime[minWorkstationIndex - 1];
			_myEvent.EventType = _departureEvent;
			_myEvent.JobNo = jobNo;
			_myEvent.StageNo = 2;
			_myEvent.WorkstationIndex = minWorkstationIndex;

			EventSchedule();  //departure event.
			_nBusyMachines[minWorkstationIndex - 1] = _nBusyMachines[minWorkstationIndex - 1] + 1;
		}
	}
}
void CGenetic::Depart()
{
	//int i, n;
	int jobNo, stageNo, workstationIndex;
	stageNo = _myEvent.StageNo;
	jobNo = _myEvent.JobNo;
	workstationIndex = _myEvent.WorkstationIndex;
	//schedule a arrive event...

	_nProcessedJobs[workstationIndex - 1] = _nProcessedJobs[workstationIndex - 1] + 1;

	//delete this workstation from selected workstations of this job...
	if (stageNo == 1)  // if departe in stage 1...
	{
		int restWorkstationsAtStage1Count = _jobInformation[jobNo - 1].RestWorkstationsAtStage1.size();
		for (int i = 0; i < restWorkstationsAtStage1Count; i++)
		{
			if (_jobInformation[jobNo - 1].RestWorkstationsAtStage1[i] == workstationIndex)
			{
				_jobInformation[jobNo - 1].RestWorkstationsAtStage1.erase(_jobInformation[jobNo - 1].RestWorkstationsAtStage1.begin() + i);
				break;
			}
		}
		restWorkstationsAtStage1Count = _jobInformation[jobNo - 1].RestWorkstationsAtStage1.size();
		if (restWorkstationsAtStage1Count == 0 && _jobInformation[jobNo - 1].StageIndex == 1) // go to stage #2...
		{
			_jobInformation[jobNo - 1].StageIndex = 2;

			_myEvent.EventTime = _simulationTime;
			_myEvent.EventType = _arriveEvent;
			_myEvent.JobNo = jobNo;
			_myEvent.StageNo = 2;
			_myEvent.WorkstationIndex = -1;

			EventSchedule();
		}
		else  if (restWorkstationsAtStage1Count != 0) //still in stage #1...
		{
			_myEvent.EventTime = _simulationTime;
			_myEvent.EventType = _arriveEvent;
			_myEvent.JobNo = jobNo;
			_myEvent.StageNo = 1;
			_myEvent.WorkstationIndex = -1;

			EventSchedule();
		}
	}
	else if (stageNo == 2)  // if depart from stage #2...
	{
		int restWorkstationsAtStage2Count = _jobInformation[jobNo - 1].RestWorkstationsAtStage2.size();
		for (int i = 0; i < restWorkstationsAtStage2Count; i++)
		{
			if (_jobInformation[jobNo - 1].RestWorkstationsAtStage2[i] == workstationIndex)
			{
				_jobInformation[jobNo - 1].RestWorkstationsAtStage2.erase(_jobInformation[jobNo - 1].RestWorkstationsAtStage2.begin() + i);
				break;
			}
		}
		restWorkstationsAtStage2Count = _jobInformation[jobNo - 1].RestWorkstationsAtStage2.size();
		if (restWorkstationsAtStage2Count == 0 ) // end...
		{
			_completionTime[jobNo - 1] = _simulationTime;
		}
		else  //still in stage #2...
		{
			_myEvent.EventTime = _simulationTime;
			_myEvent.EventType = _arriveEvent;
			_myEvent.JobNo = jobNo;
			_myEvent.StageNo = 2;
			_myEvent.WorkstationIndex = -1;

			EventSchedule();
		}
	}
	/////////////////////////////////////////////////////////////////////////////
	if (_queues[workstationIndex - 1].size() == 0) //there is no job in this queue...
	{
		_nBusyMachines[workstationIndex - 1] = _nBusyMachines[workstationIndex - 1] - 1;
	}
	else  //if thers is some job in this queue....
	{
		if (stageNo == 1)
		{

			_myEntity.TimeOfArriveToStation = _queues[workstationIndex - 1][0].TimeOfArriveToStation;
			_myEntity.JobNo = _queues[workstationIndex - 1][0].JobNo;
			_myEntity.StageNo = _queues[workstationIndex - 1][0].StageNo;
			_myEntity.WorkstationIndex = _queues[workstationIndex - 1][0].WorkstationIndex;

			_queues[workstationIndex - 1].erase(_queues[workstationIndex - 1].begin());

			int jobIndex = _myEntity.JobNo;

			_myEvent.EventTime = _simulationTime + _jobInformation[jobIndex - 1].ProcessTime[workstationIndex - 1];
			_myEvent.EventType = _departureEvent;
			_myEvent.JobNo = jobIndex;
			_myEvent.StageNo = 1;
			_myEvent.WorkstationIndex = workstationIndex;

			EventSchedule();
		}
		else if (stageNo == 2)
		{

			_myEntity.TimeOfArriveToStation = _queues[workstationIndex - 1][0].TimeOfArriveToStation;
			_myEntity.JobNo = _queues[workstationIndex - 1][0].JobNo;
			_myEntity.StageNo = _queues[workstationIndex - 1][0].StageNo;
			_myEntity.WorkstationIndex = _queues[workstationIndex - 1][0].WorkstationIndex;

			_queues[workstationIndex - 1].erase(_queues[workstationIndex - 1].begin());

			int jobIndex = _myEntity.JobNo;
			_myEvent.EventTime = _simulationTime + _jobInformation[jobIndex - 1].ProcessTime[workstationIndex - 1];
			_myEvent.EventType = _departureEvent;
			_myEvent.JobNo = jobIndex;
			_myEvent.StageNo = 2;
			_myEvent.WorkstationIndex = workstationIndex;

			EventSchedule();
		}
	}
}
void CGenetic::SelectNextEvent()
{
	//choose the first event in the event list...
	if (_eventList.size() != 0)
	{
		_simulationTime = _eventList[0].EventTime;
		_nextEventType = _eventList[0].EventType;

		_myEvent.EventTime = _eventList[0].EventTime;
		_myEvent.EventType = _eventList[0].EventType;
		_myEvent.StageNo = _eventList[0].StageNo;
		_myEvent.JobNo = _eventList[0].JobNo;
		_myEvent.WorkstationIndex = _eventList[0].WorkstationIndex;

		_eventList.erase(_eventList.begin());
	}
}
void CGenetic::EventSchedule()
{
	//events in the event list are sorted as increasing.
	int eventListSize = _eventList.size();
	int i, pos;
	pos = -1;
	for (i = 0; i < eventListSize; i++)
	{
		if (_myEvent.EventTime < _eventList[i].EventTime)  // first in first out. 
		{
			pos = i;
			break;
		}
	}


	if (pos == -1)
	{
		_eventList.push_back(_myEvent);
	}
	else
	{
		_eventList.insert(_eventList.begin() + pos, _myEvent);
	}
}