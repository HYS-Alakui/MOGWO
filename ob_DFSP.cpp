#include "Genetic.h"
#include "Individual.h"
#include "random.h"
#include <cmath>
#include <iostream>
#include <iomanip>

void CGenetic::evaluate_DFSP(CIndividual& t)//评估适应度
{
	double ***p_starting_time;//每个作业在不同工厂的不同机器上的开始时间
	p_starting_time = new double**[number_of_factories];
	for (int i = 0; i < number_of_factories; i++)
	{
		p_starting_time[i] = new double*[number_of_machines];
		for (int j = 0; j < number_of_machines; j++)
		{
			p_starting_time[i][j] = new double[number_of_jobs1];
		}
	}
	for (int i = 0; i < number_of_factories; i++)//初始化
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			for (int k = 0; k < number_of_jobs1; k++)
			{
				p_starting_time[i][j][k] = 0;
			}
		}
	}

	double ***p_finishing_time;//每个作业在不同工厂的不同机器上的完工时间
	p_finishing_time = new double**[number_of_factories];
	for (int i = 0; i < number_of_factories; i++)
	{
		p_finishing_time[i] = new double*[number_of_machines];
		for (int j = 0; j < number_of_machines; j++)
		{
			p_finishing_time[i][j] = new double[number_of_jobs1];
		}
	}
	for (int i = 0; i < number_of_factories; i++)//初始化
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			for (int k = 0; k < number_of_jobs1; k++)
			{
				p_finishing_time[i][j][k] = 0;
			}
		}
	}


	double *p_completion_time1 = new double[number_of_jobs1];
	double *p_processing_cost1 = new double[number_of_jobs1];

	//cout << "工厂分配：" << endl;
	//for (int i = 0; i < number_of_factories; i++)
	//{
	//	int f_size = t.v_job_assignment[i].size();
	//	for (int j = 0; j < f_size; j++)
	//	{
	//		cout << t.v_job_assignment[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	int job_assignment_size;
	int current_job_number, current_job_index, pre_job_index;
	vector<vector<vector<double> > >F_Start_time_Job;//所有工厂内作业的开始时间在每台机器上
	vector<vector<vector<double> > >F_Finish_time_Job;//所有工厂内作业的完成时间在每台机器上
	vector<vector<vector<double> > >().swap(F_Start_time_Job);
	vector<vector<vector<double> > >().swap(F_Finish_time_Job);
	vector<vector<vector<double> > >factory_machine_job_starttime;//工厂内机器上作业的开始时间
	vector<vector<vector<double> > >factory_machine_job_finishtime;//工厂内机器上作业的结束时间

	vector<vector<vector<double> > >().swap(t.factory_machine_job_starttime);
	vector<vector<vector<double> > >().swap(t.factory_machine_job_finishtime);

	for (int i = 0; i < number_of_factories; i++)
	{
		vector<vector<double> >Start_time_Job(number_of_machines);//工厂内作业的开始时间在每台机器上
		vector<vector<double> >Finish_time_Job(number_of_machines);//工厂内作业的完成时间在每台机器上

		job_assignment_size = t.v_job_assignment[i].size();//获取每个工厂有多少个作业
		//cout << "job_assignment_size = " << job_assignment_size << endl;
		for (int j = 0; j < 1; j++)//获取当前工厂的第一个作业
		{
			current_job_number = t.v_job_assignment[i][j];
			//cout << "current_job_number = " << current_job_number << endl;
			current_job_index = current_job_number - 1;
			//cout << "current_job_index = " << current_job_index << endl;
			p_processing_cost1[current_job_index] = 0;

			for (int k = 0; k < 1; k++)//第一台机器
			{
				//cout << "max_design_value = " << max_design_value << endl;
				p_starting_time[i][k][current_job_index] = max_design_value;
				p_finishing_time[i][k][current_job_index] = p_starting_time[i][k][current_job_index] + p_b_flow_processing_time[i][k][current_job_index];
				//cout << "工件" << current_job_index + 1 << "在工厂" << i + 1 << "的第" << k + 1 << "台机器上的完工时间为" <<p_finishing_time[i][k][current_job_index] << endl;			
				p_processing_cost1[current_job_index] = p_unit_machine_cost1[k] * p_b_flow_processing_time[i][k][current_job_index];				
				Start_time_Job[k].push_back(0);//第一个作业在第一台机器上开始时间0
				Finish_time_Job[k].push_back(p_finishing_time[i][k][current_job_index]);//第一个作业在第一台机器上结束时间为处理时间
			}
			for (int k = 1; k < number_of_machines; k++)//后面几台机器
			{
				p_starting_time[i][k][current_job_index] = p_finishing_time[i][k - 1][current_job_index];
				p_finishing_time[i][k][current_job_index] = p_starting_time[i][k][current_job_index] + p_b_flow_processing_time[i][k][current_job_index];
				//cout << "工件" << current_job_index + 1 << "在工厂" << i + 1 << "的第" << k + 1 << "台机器上的完工时间为"<< p_finishing_time[i][k][current_job_index] << endl;
				p_processing_cost1[current_job_index] += p_unit_machine_cost1[k] * p_b_flow_processing_time[i][k][current_job_index];
				Start_time_Job[k].push_back(p_starting_time[i][k][current_job_index]);//第一个作业在其他机器上开始时间是上台机器最后一个作业的结束时间
				Finish_time_Job[k].push_back(p_finishing_time[i][k][current_job_index]);//j结束时间=开始时间+处理时间
			}
			p_completion_time1[current_job_index] = p_finishing_time[i][number_of_machines - 1][current_job_index];//获取每个作业的完工时间
			//cout << "The completion time of job " << current_job_index + 1 << " is equal to " << p_completion_time1[current_job_index] << endl;
			//cout << "The processing cost of job " << current_job_index + 1 << " is equal to " << p_processing_cost1[current_job_index] << endl;
		}
		//system("pause");

		for (int j = 1; j < job_assignment_size; j++)//当前工厂的其他作业
		{
			pre_job_index = t.v_job_assignment[i][j - 1] - 1;
			//cout << "pre_job_index = " << pre_job_index << endl;
			current_job_index = t.v_job_assignment[i][j] - 1;
			//cout << "current_job_index = " << current_job_index << endl;
			p_processing_cost1[current_job_index] = 0;

			for (int k = 0; k < 1; k++)//第一台机器
			{
				p_starting_time[i][k][current_job_index] = p_finishing_time[i][k][pre_job_index];
				p_finishing_time[i][k][current_job_index] = p_starting_time[i][k][current_job_index] + p_b_flow_processing_time[i][k][current_job_index];
				//cout << "工件" << current_job_index + 1 << "在工厂" << i + 1 << "的第" << k + 1 << "台机器上的完工时间为" << p_finishing_time[i][k][current_job_index] << endl;				
				p_processing_cost1[current_job_index] = p_unit_machine_cost1[k] * p_b_flow_processing_time[i][k][current_job_index];
				Start_time_Job[k].push_back(p_starting_time[i][k][current_job_index]);
				Finish_time_Job[k].push_back(p_finishing_time[i][k][current_job_index]);
			}
			for (int k = 1; k < number_of_machines; k++)//后面几台机器
			{
				if (p_finishing_time[i][k - 1][current_job_index] < p_finishing_time[i][k][pre_job_index])//若当前工件在上台机器完工时间<上个工件在当前机器上完工时间
				{
					p_starting_time[i][k][current_job_index] = p_finishing_time[i][k][pre_job_index];//此时不存在空闲时间
					Start_time_Job[k].push_back(p_starting_time[i][k][current_job_index]);
				}
				else
				{
					p_starting_time[i][k][current_job_index] = p_finishing_time[i][k - 1][current_job_index];//此时需等工件在上台机器上加工完，故存在空闲时间
					Start_time_Job[k].push_back(p_starting_time[i][k][current_job_index]);
				}
				p_finishing_time[i][k][current_job_index] = p_starting_time[i][k][current_job_index] + p_b_flow_processing_time[i][k][current_job_index];
				//cout << "工件" << current_job_index + 1 << "在工厂" << i + 1 << "的第" << k + 1 << "台机器上的完工时间为" << p_finishing_time[i][k][current_job_index] << endl;				
				p_processing_cost1[current_job_index] += p_unit_machine_cost1[k] * p_b_flow_processing_time[i][k][current_job_index];			
				Finish_time_Job[k].push_back(p_finishing_time[i][k][current_job_index]);
			}
			p_completion_time1[current_job_index] = p_finishing_time[i][number_of_machines - 1][current_job_index];//获取每个作业的完工时间
			//cout << "The completion time of job " << current_job_index + 1 << " is equal to " << p_completion_time1[current_job_index] << endl;
			//cout << "The processing cost of job " << current_job_index + 1 << " is equal to " << p_processing_cost1[current_job_index] << endl;
		}

		F_Start_time_Job.push_back(Start_time_Job);//所有工厂内每台机器上作业的开始时间
		F_Finish_time_Job.push_back(Finish_time_Job);//所有工厂内每台机器上作业的结束时间

		t.factory_machine_job_starttime.push_back(Start_time_Job);//所有工厂内每台机器上作业的开始时间-产生新个体要用
		t.factory_machine_job_finishtime.push_back(Finish_time_Job);//所有工厂内每台机器上作业的结束时间-产生新个体要用
	}
	//system("pause");
	//for (int i = 0; i < F_Start_time_Job.size(); i++)
	//{
	//	for (int j = 0; j < F_Start_time_Job[i].size(); j++)
	//	{
	//		for (int k = 0; k < F_Start_time_Job[i][j].size(); k++)
	//		{
	//			cout << F_Start_time_Job[i][j][k] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	//for (int i = 0; i < F_Finish_time_Job.size(); i++)
	//{
	//	for (int j = 0; j < F_Finish_time_Job[i].size(); j++)
	//	{
	//		for (int k = 0; k < F_Finish_time_Job[i][j].size(); k++)
	//		{
	//			cout << F_Finish_time_Job[i][j][k] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");

	//cout << "生产阶段各工件在工厂的机器上的完工时间：" << endl;
	//for (int i = 0; i < number_of_factories; i++)
	//{
	//	for (int j = 0; j < number_of_machines; j++)
	//	{
	//		for (int k = 0; k < number_of_jobs1; k++)
	//		{
	//			cout << p_finishing_time[i][j][k] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl<<endl;
	//}
	//cout << endl;
	//system("pause");
		
	//cout << "生产阶段各工件的完工时间：" << endl;
	//for (int i = 0; i < number_of_jobs1; i++)
	//{
	//	cout << p_completion_time1[i] << " ";
	//}
	//cout << endl;
	int Max_completion_time;
	Max_completion_time = p_completion_time1[0];
	for (int i = 0; i < number_of_jobs1; i++)
	{
		//cout << "p_completion_time1[" << i << "]= " << p_completion_time1[i] << endl;//输出每个作业的完工时间
		if (Max_completion_time < p_completion_time1[i])
		{
			Max_completion_time = p_completion_time1[i];
		}
	}
	DFSP_makespan = Max_completion_time;//获取该个体的makespan
	t.DFSP_makespan_value = DFSP_makespan;

	//cout << "DFSP生产阶段各工件的加工成本：" << endl;
	total_production_cost1 = 0;
	for (int i = 0; i < number_of_jobs1; i++)
	{
		total_production_cost1 += p_processing_cost1[i];
		//cout << p_processing_cost1[i] << " ";
	}
	//cout << endl;
	//system("pause");

	//cout << "DFSP_makespan = " << DFSP_makespan << endl;
	//cout << "t.DFSP_makespan_value = " << t.DFSP_makespan_value << endl;
	//cout << "total_production_cost1= " << total_production_cost1 << endl;
	//system("pause");

	//////获取DFSP的关键路径
	//获取关键工厂和最后一个job
	double* p_makespan = new double[number_of_factories];//储存每个工厂的makespan
	for (int f = 0; f < number_of_factories; f++)
	{
		int fac_size = t.v_job_assignment[f].size();
		//cout << "fac_size = " << fac_size << endl;//每个工厂的作业规模
		int key_job_number = t.v_job_assignment[f][fac_size - 1];
		//cout << "key_job_number = " << key_job_number << endl;//每个工厂最后一个job的索引
		p_makespan[f] = p_completion_time1[key_job_number - 1];//获取每个工厂的每个makespan=该工厂最后一个job的完工时间
	}
	int key_index = 0;
	int Max_makespan = p_makespan[0];
	for (int f = 0; f < number_of_factories; f++)
	{
		//cout << "p_makespan[" << f << "]=" << p_makespan[f] << endl;
		if (Max_makespan < p_makespan[f])
		{
			Max_makespan = p_makespan[f];
			key_index = f;
		}
	}
	//cout << "key_index = " << key_index << endl;//关键工厂索引
	t.key_factory_index = key_index;
	int key_j_index; //关键工厂最后一个job的索引;
	int key_fac_size = t.v_job_assignment[key_index].size();
	key_j_index = t.v_job_assignment[key_index][key_fac_size - 1] - 1;
	//cout << "key_j_index = " << key_j_index << endl;

	//往回倒推，所以关键路径容器是倒序
	int last_job = key_j_index + 1;
	//cout << "last_job = " << last_job << endl;
	vector<int>critical_path_operation_reverse;//关键路径-逆序
	vector<int>critical_path_machine_reverse;//关键路径的操作所在的机器-逆序
	vector<int>().swap(critical_path_operation_reverse);//关键路径-逆序
	vector<int>().swap(critical_path_machine_reverse);//关键路径的操作所在的机器-逆序
	int critical_operation = last_job;
	int critical_position = 0;//关键操作在工厂分配数组的位置索引
	for (int i = 0; i < t.v_job_assignment[key_index].size(); i++)
	{
		if (critical_operation == t.v_job_assignment[key_index][i])
		{
			critical_position = i;
		}
	}
	//cout << "critical_position = " << critical_position << endl;
	int critical_F = key_index + 1;
	double critical_time = F_Finish_time_Job[critical_F - 1][number_of_machines - 1][critical_position];//关键操作的完成时间
	//cout << "critical_time = " << critical_time << endl;
	int current_machine = number_of_machines;//(当前机器编号)
	//system("pause");

	critical_path_operation_reverse.push_back(critical_operation);//关键工厂最后一个job
	critical_path_machine_reverse.push_back(current_machine);//关键工厂最后一台机器
	while (F_Start_time_Job[critical_F - 1][current_machine - 1][critical_position] != 0) //只要该job在关键工厂中最后一台机器上的开始时间不为0
	{
		if (current_machine != 1) //只要不是第一台机器
		{
			if (critical_position != 0) //只要不是工厂分配数组中第一个位置即第一个job
			{
				//同一个作业在上台机器上的的完成时间
				double front_job_completetime = F_Finish_time_Job[critical_F - 1][current_machine - 2][critical_position];
				//cout << "该作业在前一台机器上的完工时间 = " << front_job_completetime << endl;
				//同台机器上前面作业的完成时间
				double front_job_machine_completetime = F_Finish_time_Job[critical_F - 1][current_machine - 1][critical_position - 1];
				//cout << "当前机器的前一作业的完工时间 = " << front_job_machine_completetime << endl;
				if (front_job_completetime > front_job_machine_completetime)
				{   //更换机器，机器-1，位置不变-作业不变
					critical_time = front_job_completetime;
					critical_position = critical_position;
					current_machine = current_machine - 1;
					critical_operation = t.v_job_assignment[critical_F - 1][critical_position];
					critical_path_operation_reverse.push_back(critical_operation);
					critical_path_machine_reverse.push_back(current_machine);
				}
				else
				{   //机器不变，位置减1-作业改变
					critical_time = front_job_machine_completetime;
					critical_position = critical_position - 1;
					current_machine = current_machine;
					critical_operation = t.v_job_assignment[critical_F - 1][critical_position];
					critical_path_operation_reverse.push_back(critical_operation);
					critical_path_machine_reverse.push_back(current_machine);
				}

			}
			else
			{
				critical_time = F_Finish_time_Job[critical_F - 1][current_machine - 2][critical_position];
				critical_position = critical_position;
				current_machine = current_machine - 1;
				critical_operation = t.v_job_assignment[critical_F - 1][critical_position];
				critical_path_operation_reverse.push_back(critical_operation);
				critical_path_machine_reverse.push_back(current_machine);
			}
		}
		else
		{
			if (critical_position != 0)
			{
				critical_time = F_Finish_time_Job[critical_F - 1][current_machine - 1][critical_position - 1];
				critical_position = critical_position - 1;
				current_machine = current_machine;
				critical_operation = t.v_job_assignment[critical_F - 1][critical_position];
				critical_path_operation_reverse.push_back(critical_operation);
				critical_path_machine_reverse.push_back(current_machine);
			}
			else
			{
				break;
			}
		}
	}
	vector<int>().swap(t.critical_path_operation);
	vector<int>().swap(t.critical_path_machine);
	for (int k = 0; k < critical_path_operation_reverse.size(); k++) //关键路径
	{
		t.critical_path_operation.push_back(critical_path_operation_reverse[k]);
		t.critical_path_machine.push_back(critical_path_machine_reverse[k]);
	}
	//cout << "关键路径涉及的job和机器：" << endl;
	//for (int k = 0; k < t.critical_path_operation.size(); k++)
	//{
	//	int job_index = t.critical_path_operation[k] - 1;
	//	cout << job_index << " ";
	//	int machine_index = t.critical_path_machine[k] - 1;
	//	cout << machine_index << endl;//机器索引号
	//	cout <<"start："<< p_starting_time[critical_F - 1][machine_index][job_index] << " ";//验证
	//	cout <<"finish："<< p_finishing_time[critical_F - 1][machine_index][job_index] << endl;//验证
	//}
	//cout << endl;
	//system("pause");


	//每个作业在不同工厂的不同机器上的开始时间
	for (int i = 0; i < number_of_factories; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			delete[] p_starting_time[i][j];
		}
		delete[] p_starting_time[i];
	}
	delete[] p_starting_time;

	//每个作业在不同工厂的不同机器上的完工时间
	for (int i = 0; i < number_of_factories; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			delete[] p_finishing_time[i][j];
		}
		delete[] p_finishing_time[i];
	}
	delete[] p_finishing_time;

	delete[] p_completion_time1;//释放new开辟的一维空间
	delete[] p_processing_cost1;
}