#include "Genetic.h"
#include "Individual.h"
#include "random.h"
#include <cmath>
#include <iostream>
#include <iomanip>

void CGenetic::evaluate_DFSP(CIndividual& t)//������Ӧ��
{
	double ***p_starting_time;//ÿ����ҵ�ڲ�ͬ�����Ĳ�ͬ�����ϵĿ�ʼʱ��
	p_starting_time = new double**[number_of_factories];
	for (int i = 0; i < number_of_factories; i++)
	{
		p_starting_time[i] = new double*[number_of_machines];
		for (int j = 0; j < number_of_machines; j++)
		{
			p_starting_time[i][j] = new double[number_of_jobs1];
		}
	}
	for (int i = 0; i < number_of_factories; i++)//��ʼ��
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			for (int k = 0; k < number_of_jobs1; k++)
			{
				p_starting_time[i][j][k] = 0;
			}
		}
	}

	double ***p_finishing_time;//ÿ����ҵ�ڲ�ͬ�����Ĳ�ͬ�����ϵ��깤ʱ��
	p_finishing_time = new double**[number_of_factories];
	for (int i = 0; i < number_of_factories; i++)
	{
		p_finishing_time[i] = new double*[number_of_machines];
		for (int j = 0; j < number_of_machines; j++)
		{
			p_finishing_time[i][j] = new double[number_of_jobs1];
		}
	}
	for (int i = 0; i < number_of_factories; i++)//��ʼ��
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

	//cout << "�������䣺" << endl;
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
	vector<vector<vector<double> > >F_Start_time_Job;//���й�������ҵ�Ŀ�ʼʱ����ÿ̨������
	vector<vector<vector<double> > >F_Finish_time_Job;//���й�������ҵ�����ʱ����ÿ̨������
	vector<vector<vector<double> > >().swap(F_Start_time_Job);
	vector<vector<vector<double> > >().swap(F_Finish_time_Job);
	vector<vector<vector<double> > >factory_machine_job_starttime;//�����ڻ�������ҵ�Ŀ�ʼʱ��
	vector<vector<vector<double> > >factory_machine_job_finishtime;//�����ڻ�������ҵ�Ľ���ʱ��

	vector<vector<vector<double> > >().swap(t.factory_machine_job_starttime);
	vector<vector<vector<double> > >().swap(t.factory_machine_job_finishtime);

	for (int i = 0; i < number_of_factories; i++)
	{
		vector<vector<double> >Start_time_Job(number_of_machines);//��������ҵ�Ŀ�ʼʱ����ÿ̨������
		vector<vector<double> >Finish_time_Job(number_of_machines);//��������ҵ�����ʱ����ÿ̨������

		job_assignment_size = t.v_job_assignment[i].size();//��ȡÿ�������ж��ٸ���ҵ
		//cout << "job_assignment_size = " << job_assignment_size << endl;
		for (int j = 0; j < 1; j++)//��ȡ��ǰ�����ĵ�һ����ҵ
		{
			current_job_number = t.v_job_assignment[i][j];
			//cout << "current_job_number = " << current_job_number << endl;
			current_job_index = current_job_number - 1;
			//cout << "current_job_index = " << current_job_index << endl;
			p_processing_cost1[current_job_index] = 0;

			for (int k = 0; k < 1; k++)//��һ̨����
			{
				//cout << "max_design_value = " << max_design_value << endl;
				p_starting_time[i][k][current_job_index] = max_design_value;
				p_finishing_time[i][k][current_job_index] = p_starting_time[i][k][current_job_index] + p_b_flow_processing_time[i][k][current_job_index];
				//cout << "����" << current_job_index + 1 << "�ڹ���" << i + 1 << "�ĵ�" << k + 1 << "̨�����ϵ��깤ʱ��Ϊ" <<p_finishing_time[i][k][current_job_index] << endl;			
				p_processing_cost1[current_job_index] = p_unit_machine_cost1[k] * p_b_flow_processing_time[i][k][current_job_index];				
				Start_time_Job[k].push_back(0);//��һ����ҵ�ڵ�һ̨�����Ͽ�ʼʱ��0
				Finish_time_Job[k].push_back(p_finishing_time[i][k][current_job_index]);//��һ����ҵ�ڵ�һ̨�����Ͻ���ʱ��Ϊ����ʱ��
			}
			for (int k = 1; k < number_of_machines; k++)//���漸̨����
			{
				p_starting_time[i][k][current_job_index] = p_finishing_time[i][k - 1][current_job_index];
				p_finishing_time[i][k][current_job_index] = p_starting_time[i][k][current_job_index] + p_b_flow_processing_time[i][k][current_job_index];
				//cout << "����" << current_job_index + 1 << "�ڹ���" << i + 1 << "�ĵ�" << k + 1 << "̨�����ϵ��깤ʱ��Ϊ"<< p_finishing_time[i][k][current_job_index] << endl;
				p_processing_cost1[current_job_index] += p_unit_machine_cost1[k] * p_b_flow_processing_time[i][k][current_job_index];
				Start_time_Job[k].push_back(p_starting_time[i][k][current_job_index]);//��һ����ҵ�����������Ͽ�ʼʱ������̨�������һ����ҵ�Ľ���ʱ��
				Finish_time_Job[k].push_back(p_finishing_time[i][k][current_job_index]);//j����ʱ��=��ʼʱ��+����ʱ��
			}
			p_completion_time1[current_job_index] = p_finishing_time[i][number_of_machines - 1][current_job_index];//��ȡÿ����ҵ���깤ʱ��
			//cout << "The completion time of job " << current_job_index + 1 << " is equal to " << p_completion_time1[current_job_index] << endl;
			//cout << "The processing cost of job " << current_job_index + 1 << " is equal to " << p_processing_cost1[current_job_index] << endl;
		}
		//system("pause");

		for (int j = 1; j < job_assignment_size; j++)//��ǰ������������ҵ
		{
			pre_job_index = t.v_job_assignment[i][j - 1] - 1;
			//cout << "pre_job_index = " << pre_job_index << endl;
			current_job_index = t.v_job_assignment[i][j] - 1;
			//cout << "current_job_index = " << current_job_index << endl;
			p_processing_cost1[current_job_index] = 0;

			for (int k = 0; k < 1; k++)//��һ̨����
			{
				p_starting_time[i][k][current_job_index] = p_finishing_time[i][k][pre_job_index];
				p_finishing_time[i][k][current_job_index] = p_starting_time[i][k][current_job_index] + p_b_flow_processing_time[i][k][current_job_index];
				//cout << "����" << current_job_index + 1 << "�ڹ���" << i + 1 << "�ĵ�" << k + 1 << "̨�����ϵ��깤ʱ��Ϊ" << p_finishing_time[i][k][current_job_index] << endl;				
				p_processing_cost1[current_job_index] = p_unit_machine_cost1[k] * p_b_flow_processing_time[i][k][current_job_index];
				Start_time_Job[k].push_back(p_starting_time[i][k][current_job_index]);
				Finish_time_Job[k].push_back(p_finishing_time[i][k][current_job_index]);
			}
			for (int k = 1; k < number_of_machines; k++)//���漸̨����
			{
				if (p_finishing_time[i][k - 1][current_job_index] < p_finishing_time[i][k][pre_job_index])//����ǰ��������̨�����깤ʱ��<�ϸ������ڵ�ǰ�������깤ʱ��
				{
					p_starting_time[i][k][current_job_index] = p_finishing_time[i][k][pre_job_index];//��ʱ�����ڿ���ʱ��
					Start_time_Job[k].push_back(p_starting_time[i][k][current_job_index]);
				}
				else
				{
					p_starting_time[i][k][current_job_index] = p_finishing_time[i][k - 1][current_job_index];//��ʱ��ȹ�������̨�����ϼӹ��꣬�ʴ��ڿ���ʱ��
					Start_time_Job[k].push_back(p_starting_time[i][k][current_job_index]);
				}
				p_finishing_time[i][k][current_job_index] = p_starting_time[i][k][current_job_index] + p_b_flow_processing_time[i][k][current_job_index];
				//cout << "����" << current_job_index + 1 << "�ڹ���" << i + 1 << "�ĵ�" << k + 1 << "̨�����ϵ��깤ʱ��Ϊ" << p_finishing_time[i][k][current_job_index] << endl;				
				p_processing_cost1[current_job_index] += p_unit_machine_cost1[k] * p_b_flow_processing_time[i][k][current_job_index];			
				Finish_time_Job[k].push_back(p_finishing_time[i][k][current_job_index]);
			}
			p_completion_time1[current_job_index] = p_finishing_time[i][number_of_machines - 1][current_job_index];//��ȡÿ����ҵ���깤ʱ��
			//cout << "The completion time of job " << current_job_index + 1 << " is equal to " << p_completion_time1[current_job_index] << endl;
			//cout << "The processing cost of job " << current_job_index + 1 << " is equal to " << p_processing_cost1[current_job_index] << endl;
		}

		F_Start_time_Job.push_back(Start_time_Job);//���й�����ÿ̨��������ҵ�Ŀ�ʼʱ��
		F_Finish_time_Job.push_back(Finish_time_Job);//���й�����ÿ̨��������ҵ�Ľ���ʱ��

		t.factory_machine_job_starttime.push_back(Start_time_Job);//���й�����ÿ̨��������ҵ�Ŀ�ʼʱ��-�����¸���Ҫ��
		t.factory_machine_job_finishtime.push_back(Finish_time_Job);//���й�����ÿ̨��������ҵ�Ľ���ʱ��-�����¸���Ҫ��
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

	//cout << "�����׶θ������ڹ����Ļ����ϵ��깤ʱ�䣺" << endl;
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
		
	//cout << "�����׶θ��������깤ʱ�䣺" << endl;
	//for (int i = 0; i < number_of_jobs1; i++)
	//{
	//	cout << p_completion_time1[i] << " ";
	//}
	//cout << endl;
	int Max_completion_time;
	Max_completion_time = p_completion_time1[0];
	for (int i = 0; i < number_of_jobs1; i++)
	{
		//cout << "p_completion_time1[" << i << "]= " << p_completion_time1[i] << endl;//���ÿ����ҵ���깤ʱ��
		if (Max_completion_time < p_completion_time1[i])
		{
			Max_completion_time = p_completion_time1[i];
		}
	}
	DFSP_makespan = Max_completion_time;//��ȡ�ø����makespan
	t.DFSP_makespan_value = DFSP_makespan;

	//cout << "DFSP�����׶θ������ļӹ��ɱ���" << endl;
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

	//////��ȡDFSP�Ĺؼ�·��
	//��ȡ�ؼ����������һ��job
	double* p_makespan = new double[number_of_factories];//����ÿ��������makespan
	for (int f = 0; f < number_of_factories; f++)
	{
		int fac_size = t.v_job_assignment[f].size();
		//cout << "fac_size = " << fac_size << endl;//ÿ����������ҵ��ģ
		int key_job_number = t.v_job_assignment[f][fac_size - 1];
		//cout << "key_job_number = " << key_job_number << endl;//ÿ���������һ��job������
		p_makespan[f] = p_completion_time1[key_job_number - 1];//��ȡÿ��������ÿ��makespan=�ù������һ��job���깤ʱ��
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
	//cout << "key_index = " << key_index << endl;//�ؼ���������
	t.key_factory_index = key_index;
	int key_j_index; //�ؼ��������һ��job������;
	int key_fac_size = t.v_job_assignment[key_index].size();
	key_j_index = t.v_job_assignment[key_index][key_fac_size - 1] - 1;
	//cout << "key_j_index = " << key_j_index << endl;

	//���ص��ƣ����Թؼ�·�������ǵ���
	int last_job = key_j_index + 1;
	//cout << "last_job = " << last_job << endl;
	vector<int>critical_path_operation_reverse;//�ؼ�·��-����
	vector<int>critical_path_machine_reverse;//�ؼ�·���Ĳ������ڵĻ���-����
	vector<int>().swap(critical_path_operation_reverse);//�ؼ�·��-����
	vector<int>().swap(critical_path_machine_reverse);//�ؼ�·���Ĳ������ڵĻ���-����
	int critical_operation = last_job;
	int critical_position = 0;//�ؼ������ڹ������������λ������
	for (int i = 0; i < t.v_job_assignment[key_index].size(); i++)
	{
		if (critical_operation == t.v_job_assignment[key_index][i])
		{
			critical_position = i;
		}
	}
	//cout << "critical_position = " << critical_position << endl;
	int critical_F = key_index + 1;
	double critical_time = F_Finish_time_Job[critical_F - 1][number_of_machines - 1][critical_position];//�ؼ����������ʱ��
	//cout << "critical_time = " << critical_time << endl;
	int current_machine = number_of_machines;//(��ǰ�������)
	//system("pause");

	critical_path_operation_reverse.push_back(critical_operation);//�ؼ��������һ��job
	critical_path_machine_reverse.push_back(current_machine);//�ؼ��������һ̨����
	while (F_Start_time_Job[critical_F - 1][current_machine - 1][critical_position] != 0) //ֻҪ��job�ڹؼ����������һ̨�����ϵĿ�ʼʱ�䲻Ϊ0
	{
		if (current_machine != 1) //ֻҪ���ǵ�һ̨����
		{
			if (critical_position != 0) //ֻҪ���ǹ������������е�һ��λ�ü���һ��job
			{
				//ͬһ����ҵ����̨�����ϵĵ����ʱ��
				double front_job_completetime = F_Finish_time_Job[critical_F - 1][current_machine - 2][critical_position];
				//cout << "����ҵ��ǰһ̨�����ϵ��깤ʱ�� = " << front_job_completetime << endl;
				//̨ͬ������ǰ����ҵ�����ʱ��
				double front_job_machine_completetime = F_Finish_time_Job[critical_F - 1][current_machine - 1][critical_position - 1];
				//cout << "��ǰ������ǰһ��ҵ���깤ʱ�� = " << front_job_machine_completetime << endl;
				if (front_job_completetime > front_job_machine_completetime)
				{   //��������������-1��λ�ò���-��ҵ����
					critical_time = front_job_completetime;
					critical_position = critical_position;
					current_machine = current_machine - 1;
					critical_operation = t.v_job_assignment[critical_F - 1][critical_position];
					critical_path_operation_reverse.push_back(critical_operation);
					critical_path_machine_reverse.push_back(current_machine);
				}
				else
				{   //�������䣬λ�ü�1-��ҵ�ı�
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
	for (int k = 0; k < critical_path_operation_reverse.size(); k++) //�ؼ�·��
	{
		t.critical_path_operation.push_back(critical_path_operation_reverse[k]);
		t.critical_path_machine.push_back(critical_path_machine_reverse[k]);
	}
	//cout << "�ؼ�·���漰��job�ͻ�����" << endl;
	//for (int k = 0; k < t.critical_path_operation.size(); k++)
	//{
	//	int job_index = t.critical_path_operation[k] - 1;
	//	cout << job_index << " ";
	//	int machine_index = t.critical_path_machine[k] - 1;
	//	cout << machine_index << endl;//����������
	//	cout <<"start��"<< p_starting_time[critical_F - 1][machine_index][job_index] << " ";//��֤
	//	cout <<"finish��"<< p_finishing_time[critical_F - 1][machine_index][job_index] << endl;//��֤
	//}
	//cout << endl;
	//system("pause");


	//ÿ����ҵ�ڲ�ͬ�����Ĳ�ͬ�����ϵĿ�ʼʱ��
	for (int i = 0; i < number_of_factories; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			delete[] p_starting_time[i][j];
		}
		delete[] p_starting_time[i];
	}
	delete[] p_starting_time;

	//ÿ����ҵ�ڲ�ͬ�����Ĳ�ͬ�����ϵ��깤ʱ��
	for (int i = 0; i < number_of_factories; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			delete[] p_finishing_time[i][j];
		}
		delete[] p_finishing_time[i];
	}
	delete[] p_finishing_time;

	delete[] p_completion_time1;//�ͷ�new���ٵ�һά�ռ�
	delete[] p_processing_cost1;
}