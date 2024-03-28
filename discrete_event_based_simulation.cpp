
#include "Entity.h"
#include "Event.h"
#include "Genetic.h"
#include "headfile.h"
#include "Individual.h"
#include "random.h"




/*
void CGenetic::discrete_event_based_simulation(CIndividual& t)
{
	event_simulation(t);
}
void CGenetic::init_simulation_environment(CIndividual& t)
{
	simulation_time = 0.0;
	arrive_event = 1;
	departure_event = 2;
	end_simulation_event = 3;
	busy = 1;
	idle = 0;
	next_event_type = -1;

	int i;
	vector <CEvent>().swap(v_event_list);
	for (i = 0; i < number_of_workstations; i++)
	{
		vector <vector <CEntity>>().swap(v_queues);
	}
	vector <double>().swap(v_complete_time);

	p_number_of_busy_machines = new int [number_of_workstations];
	for (i=0; i<number_of_workstations; i++)
	{
		p_number_of_busy_machines[i] = 0;
	}
	//initialize the queue_list.
	for (i = 0; i < number_of_workstations; i++)
	{
		vector <CEntity> v_entity;
		v_queues.push_back(v_entity);
	}
	for (i = 0; i < number_of_jobs; i++)
	{
		v_complete_time.push_back(0);
	}
	//initialize the event list;
	vector <CJob>().swap(v_job_information);
	for (i = 0; i < number_of_jobs; i++)
	{
		my_event.event_time = simulation_time;
		my_event.event_type = arrive_event;
		my_event.job_no = t.v_chromosome[i];
		my_event.stage_no = 1;
		CJob job;
		for (int j = 0; j < number_of_workstations; j++)
		{
			job.v_processing_time.push_back(p_processing_time[j]);
			job.v_due_date.push_back(p_due_date[j]);
			if (j < number_of_workstations - 1)
			{
				job.v_selected_workstations.push_back(j + 1);
			}			
		}
		v_job_information.push_back(job);
		event_schedule();
	}
	//create the end simulation event.
	my_event.event_time = INF_DOUBLE_MAX;
	my_event.event_type = end_simulation_event;
	my_event.job_no = -1.0;
	my_event.stage_no = -1;
	event_schedule();
}
void CGenetic::event_simulation(CIndividual& t)
{
	int i;
	p_completion_time = new double[number_of_jobs];
	init_simulation_environment(t);
	while (next_event_type != end_simulation_event)
	{
		select_next_event();
		if (next_event_type == arrive_event)
		{
			arrive();
		}
		if (next_event_type == departure_event)
		{
			departure();
		}
		if (next_event_type == end_simulation_event) //calculate objective function values...
		{
			//calculate objective function value...
			double cmax = INF_DOUBLE_MIN;
			for (int i=0; i<number_of_jobs; i++)
			{
				if (cmax < p_completion_time[i])
				{
					cmax = p_completion_time[i];
				}
			}
			double total_tardiness = 0.0;
			for (int i = 0; i < number_of_jobs; i++)
			{
				if (p_completion_time[i] - p_due_date[i] > 0)
				{
					total_tardiness = total_tardiness + p_completion_time[i] - p_due_date[i];
				}
			}
			vector <double>().swap(t.v_objValue);
			t.v_objValue.push_back(cmax);
			t.v_objValue.push_back(total_tardiness);
		}
	}
	delete[] p_completion_time;
}
void CGenetic::arrive()
{
	int job_no, stage_no, station_no, event_type;

	event_type = my_event.event_type;
	stage_no = my_event.stage_no;
	job_no = my_event.job_no;

	//*********************************************************************
	//if this is a new arrival to the system, generate the time of the next
	//arrival and determine the job no and operation no of the arriving job. 
	//*********************************************************************
	if (stage_no == 1)   //the arrive event is in the 1# stage.
	{
		//find a workstation with least queue...
		int selected_workstations_size = v_job_information[job_no-1].v_selected_workstations.size();	
		int min_queue_length = INF_INT_MAX;
		int min_workstation_index, workstation_index = 1;
		for (int i = 0; i < selected_workstations_size; i++)
		{
			workstation_index = v_job_information[job_no - 1].v_selected_workstations[i];
			if (min_queue_length > v_queues[workstation_index - 1].size())
			{
				min_queue_length = v_queues[workstation_index - 1].size();
				min_workstation_index = workstation_index;
			}
		}
		if (p_number_of_busy_machines[min_workstation_index - 1] == p_number_of_machines[min_workstation_index - 1])
		{
			//all the machines in this station are busy, put the arrive job into its corresponding queue list.
			//put in its queue list.
			my_entity.time_of_arrive_to_station = simulation_time;
			my_entity.job_no = job_no;
			my_entity.stage_no = stage_no;
			my_entity.workstation_index = min_workstation_index;

			v_queues[min_workstation_index - 1].push_back(my_entity);
		}
		else if (p_number_of_busy_machines[min_workstation_index - 1] < p_number_of_machines[min_workstation_index - 1])
		{
			//schedule a departure event about the arrive job.
			my_event.event_time = simulation_time + v_job_information[job_no - 1].v_processing_time[min_workstation_index - 1];
			my_event.event_type = departure_event;
			my_event.job_no = job_no;
			my_event.stage_no = stage_no;
			my_event.workstation_index = min_workstation_index;
			p_number_of_busy_machines[min_workstation_index - 1] = p_number_of_busy_machines[min_workstation_index - 1] + 1;

			event_schedule();  //departure event.
		}
	}
	else if (stage_no == 2)
	{
		if (p_number_of_busy_machines[number_of_workstations - 1] == p_number_of_machines[number_of_workstations - 1])
		{
			my_entity.time_of_arrive_to_station = simulation_time;
			my_entity.stage_no = stage_no;
			my_entity.job_no = job_no;
			my_entity.workstation_index = number_of_workstations;

			v_queues[number_of_workstations - 1].push_back(my_entity);
		}
		else if (p_number_of_busy_machines[number_of_workstations  - 1] < p_number_of_machines[number_of_workstations - 1])
		{
			my_event.event_time = simulation_time + v_job_information[job_no - 1].v_processing_time[number_of_workstations - 1];
			my_event.event_type = departure_event;
			my_event.job_no = job_no;
			my_event.stage_no = stage_no;
			my_event.workstation_index = number_of_workstations;
			p_number_of_busy_machines[number_of_workstations - 1] = p_number_of_busy_machines[number_of_workstations - 1] + 1;

			//event_schedule();  //departure event. //end...
			p_completion_time[job_no - 1] = my_event.event_time;
		}
	}
}
void CGenetic::departure()
{
	int i, n;
	int job_no, stage_no, event_type, selected_workstations_size, workstation_index;

	event_type = my_event.event_type;
	stage_no = my_event.stage_no;
	job_no = my_event.job_no;
	workstation_index = my_event.workstation_index;
	//schedule a arrive event...
	selected_workstations_size = v_job_information[job_no - 1].v_selected_workstations.size();
	//delete this workstation from selected workstations of this job...
	for (int i = 0; i < selected_workstations_size; i++)
	{
		if (v_job_information[job_no - 1].v_selected_workstations[i] == workstation_index)
		{
			v_job_information[job_no - 1].v_selected_workstations.erase(v_job_information[job_no - 1].v_selected_workstations.begin() + i);
			break;
		}
	}
	selected_workstations_size = v_job_information[job_no - 1].v_selected_workstations.size();
	if (selected_workstations_size == 0) // go to stage 2...
	{
		my_event.event_time = simulation_time;
		my_event.event_type = arrive_event;
		my_event.job_no = job_no;
		my_event.stage_no = 2;
		my_event.workstation_index = number_of_workstations;

		event_schedule();
	}
	else
	{
		my_event.event_time = simulation_time;
		my_event.event_type = arrive_event;
		my_event.job_no = job_no;
		my_event.stage_no = 1;
		my_event.workstation_index = -1;
		event_schedule();
	}
	/////////////////////////////////////////////////////////////////////////////
	if (v_queues[workstation_index - 1].size() == 0) //there is no job in this queue...
	{
		p_number_of_busy_machines[workstation_index - 1] = p_number_of_busy_machines[workstation_index - 1] - 1;
	}
	else  //if thers is some job in this queue...schedule a departure event...
	{ 
		if (stage_no == 1)
		{
			my_entity = v_queues[workstation_index - 1][0];
			v_queues[workstation_index - 1].erase(v_queues[workstation_index - 1].begin());

			int job_index = my_entity.job_no;
			my_event.job_no = job_index;
			my_event.stage_no = 1;
			my_event.workstation_index = workstation_index;
			my_event.event_time = simulation_time + v_job_information[job_index - 1].v_processing_time[workstation_index - 1];
			my_event.event_type = departure_event;

			event_schedule();
		}
		else
		{ 
			my_entity = v_queues[workstation_index - 1][0];
			v_queues[workstation_index - 1].erase(v_queues[workstation_index - 1].begin());

			int job_index = my_entity.job_no;
			my_event.job_no = job_index;
			my_event.stage_no = 2;
			my_event.workstation_index = number_of_workstations;
			my_event.event_time = simulation_time + v_job_information[job_index - 1].v_processing_time[workstation_index - 1];
			my_event.event_type = departure_event;

			//event_schedule();

			p_completion_time[job_no - 1] = my_event.event_time;
		}
	}
}
void CGenetic::select_next_event()
{
	//choose the first event in the event list...
	if (v_event_list.size() != 0)
	{
		simulation_time = v_event_list[0].event_time;

		next_event_type = v_event_list[0].event_type;
		my_event.event_time = v_event_list[0].event_time;
		my_event.event_type = v_event_list[0].event_type;
		my_event.stage_no = v_event_list[0].stage_no;
		my_event.job_no = v_event_list[0].job_no;

		v_event_list.erase(v_event_list.begin());
	}
}
void CGenetic::event_schedule()
{
	//events in the event list are sorted as increasing.
	int event_list_size = v_event_list.size();
	int i, pos;
	pos = -1;
	for (i = 0; i < event_list_size; i++)
	{
		if (my_event.event_time < v_event_list[i].event_time)  // first in first out. 
		{
			pos = i;
			break;
		}
	}
	if (pos == -1)
	{
		v_event_list.push_back(my_event);
	}
	else
	{
		v_event_list.insert(v_event_list.begin() + pos, my_event);
	}
}
*/