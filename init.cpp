#include "Genetic.h"
#include "Individual.h"
#include "rankSequ.h"
#include "headfile.h"
#include "random.h"
#include "Chromosome.h"
#include <iomanip>
#include <vector>
#include <algorithm>

void CGenetic::init_parameters()//��ʼ������
{	
	number_of_objectives = 2;//Ŀ������
	current_number_of_fitness_evaluations = 0;//��ǰ��Ӧ����������
	number_of_jobs = number_of_jobs1 + number_of_jobs2;
	//cout << "number_of_jobs = " << number_of_jobs << endl;
	total_number_of_fitness_evaluations = 40 * number_of_jobs * number_of_machines;//ֹͣ����������Ӧ����������	
	//cout << total_number_of_fitness_evaluations << endl;
	number_of_individuals = 80;//������Ŀ
	iteration_num = 0;
		
	//��ÿ���Ǳ�׼�������ʱ��=�ۼ�ÿ���Ǳ�׼�������Ĺ�������ʱ��
	p_nonpart_design_time = new double[number_of_jobs2];
	for (int i = 0; i < number_of_jobs2; i++)
	{
		p_nonpart_design_time[i] = 0;
		for (int j = 0; j < number_of_operations; j++)
		{
			p_nonpart_design_time[i] += p_b_fjsp_design_time[j][i];
		}
		//cout << "ÿ���Ǳ�׼�������ʱ�䣺" << p_nonpart_design_time[i] << endl;
	}
	//cout << endl;

	//�ҳ��������ʱ��
	max_design_value = p_nonpart_design_time[0];
	for (int i = 0; i < number_of_jobs2; i++)
	{
		if (p_nonpart_design_time[i] > max_design_value)
		{
			max_design_value = p_nonpart_design_time[i];
		}
	}
	//cout << "max_design_value = " << max_design_value << endl;
	//system("pause");

	//��ÿ���Ǳ�׼������Ƴɱ�=�ۼ�ÿ���Ǳ�׼�������Ĺ������Ƴɱ�
	p_nonpart_design_cost = new double[number_of_jobs2];
	p_nonpart_o_design_cost = new double*[number_of_operations];
	for (int i = 0; i < number_of_operations; i++)
	{
		p_nonpart_o_design_cost[i] = new double[number_of_jobs2];
	}
	for (int i = 0; i < number_of_jobs2; i++)
	{
		p_nonpart_design_cost[i] = 0;
		for (int j = 0; j < number_of_operations; j++)
		{
			p_nonpart_o_design_cost[j][i] = p_b_fjsp_design_time[j][i] * (p_unit_design_cost[j][i]/10);
			//cout << "p_nonpart_o_design_cost[j][i] =" << p_nonpart_o_design_cost[j][i] << endl;
			p_nonpart_design_cost[i] += p_nonpart_o_design_cost[j][i];
		}
		//cout << "ÿ���Ǳ�׼������Ƴɱ���" << p_nonpart_design_cost[i] << endl;
	}	
	total_design_cost = 0;
	for (int i = 0; i < number_of_jobs2; i++)
	{
		total_design_cost += p_nonpart_design_cost[i];
	}
	//cout << "total_design_cost = " << total_design_cost << endl;
	//system("pause");
}//���� ��� ��ʼ����������genetic.h��finfout.cpp��Ӧ�ſ�

void CGenetic::generInitPopu()//��ʼ����Ⱥ
{
	//cout << "------------1����ʼ����Ⱥ---------" << endl;
	vector <CIndividual>().swap(v_Chromo);//����swap�����ڴ棬��Ⱥ��ʼ��Ϊ�գ�vector.clear()������ݣ�����û���ͷ��ڴ�;����swap�������ԡ� ��ô����ͷ��ڴ��أ�������swap������һ���µ����͵�vector,��ԭ����v_Chromo������ȥ��Ȼ����Ȼ���٣����µĵ���v_Chromo��ȫ�µ�û�д��κ����ݵġ�	
	for (int i = 0; i < 0.9 * number_of_individuals; i++)//�������
	{
		//cout << "i = " << i << endl;
		CIndividual t;
		randomWay(t);//���� randomWay���������������t��ʵ�Σ������β�(CIndividual& t)��Ȼ�󷵻�һ���������
		//////���ÿ������
		//for (int j = 0; j < number_of_jobs1; j++)
		//{
		//	cout << t.v_chromosome1[j].factory_number << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs1; j < t.v_chromosome1.size(); j++)
		//{
		//	cout << t.v_chromosome1[j].job_number << " ";
		//}
		//cout << endl;

		//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
		//{
		//	cout << t.v_chromosome2[j].operation_number << " ";
		//}
		//cout << endl;
		//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
		//{
		//	cout << t.v_chromosome2[j].operation_index << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs2 * number_of_operations; j < t.v_chromosome2.size(); j++)
		//{
		//	cout << t.v_chromosome2[j].machine_number << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs2 * number_of_operations; j < t.v_chromosome2.size(); j++)
		//{
		//	cout << t.v_chromosome2[j].job_number << " ";
		//}
		//cout << endl;
		//system("pause");

		assign(t);//���ݹ���������ȡ��������
		//system("pause");

		//�ж��Ƿ��й���Ϊ�գ����й���Ϊ��������������ɹ�������
		for (int f = 0; f < number_of_factories; f++)
		{
			int f_size = t.v_job_assignment[f].size();
			if (f_size == 0)
			{
				int index_f;
				for (int j = 0; j < number_of_jobs1; j++)//Ⱦɫ�幤�����֣�������job����Ŀ���
				{
					index_f = rand() % number_of_factories + 1;//ȡֵ��Χ��[1,number_of_factories]
					t.v_chromosome1[j].job_number = j + 1;
					t.v_chromosome1[j].factory_number = index_f;
				}
				break;
			}

		}
		assign(t);//���ݹ���������ȡ��������
		evaluate_DFSP(t);
		evaluate_FJSP(t);
		evaluate(t);

		//system("pause");
		v_Chromo.push_back(t);
	}

	for (int i = 0.9 * number_of_individuals; i < 0.95 * number_of_individuals; i++)//��������ʹ��OMPT����
	{
		CIndividual t;
		vector <CChromosome>().swap(t.v_chromosome1);//v_chromosome1�Ƕ���DFSP�����ԣ�����Ϊv_chromosome�Ǹ�����������swap�����ڴ�
		//step11:initialize DFSP factory assignment...
		int index1;
		for (int j = 0; j < number_of_jobs1; j++)//Ⱦɫ�幤�����֣�������job����Ŀ���
		{
			CChromosome t1;
			index1 = rand() % number_of_factories + 1;//ȡֵ��Χ��[1,number_of_factories]
			t1.factory_number = index1;
			t1.job_number = j + 1;
			t.v_chromosome1.push_back(t1);
		}
		//step12:initialize DFSP job sequence...
		int ii;
		int min = 1;
		int max = number_of_jobs1;
		int num = max - min + 1; //����� �� ��Ŀ��������ҵ����Ⱦɫ�峤����5����ô����Ҫ5�������
		int jobNo;//��ҵ��
		int* a = new int[num];//����һ������num��Ԫ�ص�����a[num]
		for (ii = 0; ii < num; ii++)//Ϊ ÿ�� �����  ��ֵ
		{
			a[ii] = ii + min;//����Ⱦɫ�峤��=5����ônum=5����ô�����(����)�϶���1,2,3,4,5
		}                  //a[0]=1,a[1]=2,a[2]=3,a[3]=4,a[4]=5
		int index2;
		for (ii = 0; ii < num; ii++)
		{
			CChromosome t2;
			index2 = (int)((float)(num - ii) * rand() / ((RAND_MAX + 1) * 1.0));
			jobNo = a[index2];
			t2.job_number = jobNo;
			t.v_chromosome1.push_back(t2);
			a[index2] = a[num - ii - 1];
		}
		delete[] a;


		vector <CChromosome>().swap(t.v_chromosome2);
		//step21:initialize operation sequence...
		int* p_temp = new int[number_of_jobs2 * number_of_operations];//Ⱦɫ�幤�򲿷֣�����=job����Ŀ��ÿ��job�Ĺ�����Ŀ����������ÿ��job��3������
		int index3 = 0;
		for (int j = 0; j < number_of_jobs2; j++)
		{
			for (int k = 0; k < number_of_operations; k++)
			{
				p_temp[index3] = j + 1;
				index3 = index3 + 1;
			}
		}
		int total_operations_number = number_of_jobs2 * number_of_operations;
		int num2 = number_of_jobs2 * number_of_operations;
		int rand_num;
		for (int o = 0; o < total_operations_number; o++)
		{
			CChromosome t3;
			rand_num = rand() % num2;
			index3 = p_temp[rand_num];
			t3.job_number = index3;
			t3.operation_number = index3;
			t.v_chromosome2.push_back(t3);
			p_temp[rand_num] = p_temp[num2 - 1];
			num2 = num2 - 1;
		}
		delete[] p_temp;

		for (int j = 0; j < number_of_jobs2; j++)//�ж���ÿ��job�ĵڼ�������
		{
			int current_job_number = j + 1;
			int count = 0;
			//cout << "current_job_number = " << current_job_number << endl;
			for (int c = 0; c < total_operations_number; c++)
			{
				if (current_job_number == t.v_chromosome2[c].job_number)
				{
					count = count + 1;
					t.v_chromosome2[c].operation_index = count;
					//cout << "count = " << count << endl;
				}
				continue;
			}
		}

		//step22:initialize machine assignment...
		//���ȣ�Ҫ���ÿ��job��ÿ������Ŀ��û�����
		vector<vector<vector<int>>>().swap(v_available_machines);
		for (int j = 0; j < number_of_jobs2; j++)
		{
			vector <vector<int>> v1;
			v_available_machines.push_back(v1);
			for (int o = 0; o < number_of_operations; o++)
			{
				vector <int> v2;
				v_available_machines[j].push_back(v2);
				int machine_number;
				for (int m = 0; m < number_of_machines; m++)
				{
					if (p_b_fjsp_processing_time[o][m][j] != 0)
					{
						machine_number = m + 1;
						v_available_machines[j][o].push_back(machine_number);
					}
				}
				//cout << endl;
			}
			//cout << endl;
		}

		for (int j = 0; j < number_of_jobs2; j++)
		{
			CChromosome t3;
			//��ȡ��job��ÿ������Ŀ��û�����
			for (int o = 0; o < number_of_operations; o++)
			{
				int operation_machine_size = v_available_machines[j][o].size();
				//cout << "operation_machine_size = " << operation_machine_size << endl;
				//�ҳ�ÿ������ļӹ�ʱ����С�Ļ���
				for (int m = 0; m < operation_machine_size; m++)
				{
					int number_m = v_available_machines[j][o][m];
					//cout << number_m << " ";
					//cout << p_b_fjsp_processing_time[o][number_m - 1][j] <<endl;
				}
				int number_m = v_available_machines[j][o][0];//�ȰѸù���ĵ�һ̨�����Ļ�������Ϊ��С����
				int min_machine_number = number_m;//��С������
				int min_machine_index = number_m - 1;//��С������������
				int min_machine_time = p_b_fjsp_processing_time[o][min_machine_index][j];//��С�����ϵļӹ�ʱ��				
				for (int m = 0; m < operation_machine_size; m++)
				{
					int number_m = v_available_machines[j][o][m];
					//cout << number_m << " ";
					//cout << p_b_fjsp_processing_time[o][number_m - 1][j] << endl;
					if (min_machine_time > p_b_fjsp_processing_time[o][number_m - 1][j])
					{
						min_machine_time = p_b_fjsp_processing_time[o][number_m - 1][j];
						min_machine_number = number_m;
					}
				}
				//cout << "min_machine_number = " << min_machine_number << endl;
				t3.job_number = j + 1;
				t3.machine_number = min_machine_number;
				t.v_chromosome2.push_back(t3);
			}
			//cout << endl;
		}
		//cout << endl;
		//system("pause");

		////���ÿ������
		//for (int j = 0; j < number_of_jobs1; j++)
		//{
		//	cout << t.v_chromosome1[j].factory_number << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs1; j < t.v_chromosome1.size(); j++)
		//{
		//	cout << t.v_chromosome1[j].job_number << " ";
		//}
		//cout << endl;

		//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
		//{
		//	cout << t.v_chromosome2[j].operation_number << " ";
		//}
		//cout << endl;
		//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
		//{
		//	cout << t.v_chromosome2[j].operation_index << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs2 * number_of_operations; j < t.v_chromosome2.size(); j++)
		//{
		//	cout << t.v_chromosome2[j].machine_number << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs2 * number_of_operations; j < t.v_chromosome2.size(); j++)
		//{
		//	cout << t.v_chromosome2[j].job_number << " ";
		//}
		//cout << endl;
		////system("pause");

		assign(t);//���ݹ���������ȡ��������
		//system("pause");

		//�ж��Ƿ��й���Ϊ�գ����й���Ϊ��������������ɹ�������
		for (int f = 0; f < number_of_factories; f++)
		{
			int f_size = t.v_job_assignment[f].size();
			if (f_size == 0)
			{
				int index_f;
				for (int j = 0; j < number_of_jobs1; j++)//Ⱦɫ�幤�����֣�������job����Ŀ���
				{
					index_f = rand() % number_of_factories + 1;//ȡֵ��Χ��[1,number_of_factories]
					t.v_chromosome1[j].job_number = j + 1;
					t.v_chromosome1[j].factory_number = index_f;
				}
				break;
			}

		}
		assign(t);//���ݹ���������ȡ��������
		evaluate_DFSP(t);
		evaluate_FJSP(t);
		evaluate(t);

		//system("pause");
		v_Chromo.push_back(t);
	}

	for (int i = 0.95 * number_of_individuals; i < number_of_individuals; i++)//��������ʹ��OMPT����
	{
		CIndividual t;
		vector <CChromosome>().swap(t.v_chromosome1);//v_chromosome1�Ƕ���DFSP�����ԣ�����Ϊv_chromosome�Ǹ�����������swap�����ڴ�
		//step11:initialize DFSP factory assignment...
		int index1;
		for (int j = 0; j < number_of_jobs1; j++)//Ⱦɫ�幤�����֣�������job����Ŀ���
		{
			CChromosome t1;
			index1 = rand() % number_of_factories + 1;//ȡֵ��Χ��[1,number_of_factories]
			t1.factory_number = index1;
			t1.job_number = j + 1;
			t.v_chromosome1.push_back(t1);
		}
		//step12:initialize DFSP job sequence...
		int ii;
		int min = 1;
		int max = number_of_jobs1;
		int num = max - min + 1; //����� �� ��Ŀ��������ҵ����Ⱦɫ�峤����5����ô����Ҫ5�������
		int jobNo;//��ҵ��
		int* a = new int[num];//����һ������num��Ԫ�ص�����a[num]
		for (ii = 0; ii < num; ii++)//Ϊ ÿ�� �����  ��ֵ
		{
			a[ii] = ii + min;//����Ⱦɫ�峤��=5����ônum=5����ô�����(����)�϶���1,2,3,4,5
		}                  //a[0]=1,a[1]=2,a[2]=3,a[3]=4,a[4]=5
		int index2;
		for (ii = 0; ii < num; ii++)
		{
			CChromosome t2;
			index2 = (int)((float)(num - ii) * rand() / ((RAND_MAX + 1) * 1.0));
			jobNo = a[index2];
			t2.job_number = jobNo;
			t.v_chromosome1.push_back(t2);
			a[index2] = a[num - ii - 1];
		}
		delete[] a;


		vector <CChromosome>().swap(t.v_chromosome2);
		//step21:initialize operation sequence...
		int* p_temp = new int[number_of_jobs2 * number_of_operations];//Ⱦɫ�幤�򲿷֣�����=job����Ŀ��ÿ��job�Ĺ�����Ŀ����������ÿ��job��3������
		int index3 = 0;
		for (int j = 0; j < number_of_jobs2; j++)
		{
			for (int k = 0; k < number_of_operations; k++)
			{
				p_temp[index3] = j + 1;
				index3 = index3 + 1;
			}
		}
		int total_operations_number = number_of_jobs2 * number_of_operations;
		int num2 = number_of_jobs2 * number_of_operations;
		int rand_num;
		for (int o = 0; o < total_operations_number; o++)
		{
			CChromosome t3;
			rand_num = rand() % num2;
			index3 = p_temp[rand_num];
			t3.job_number = index3;
			t3.operation_number = index3;
			t.v_chromosome2.push_back(t3);
			p_temp[rand_num] = p_temp[num2 - 1];
			num2 = num2 - 1;
		}
		delete[] p_temp;

		for (int j = 0; j < number_of_jobs2; j++)//�ж���ÿ��job�ĵڼ�������
		{
			int current_job_number = j + 1;
			int count = 0;
			//cout << "current_job_number = " << current_job_number << endl;
			for (int c = 0; c < total_operations_number; c++)
			{
				if (current_job_number == t.v_chromosome2[c].job_number)
				{
					count = count + 1;
					t.v_chromosome2[c].operation_index = count;
					//cout << "count = " << count << endl;
				}
				continue;
			}
		}

		//step22:initialize machine assignment...
		//���ȣ�Ҫ���ÿ��job��ÿ������Ŀ��û�����
		vector<vector<vector<int>>>().swap(v_available_machines);
		for (int j = 0; j < number_of_jobs2; j++)
		{
			vector <vector<int>> v1;
			v_available_machines.push_back(v1);
			for (int o = 0; o < number_of_operations; o++)
			{
				vector <int> v2;
				v_available_machines[j].push_back(v2);
				int machine_number;
				for (int m = 0; m < number_of_machines; m++)
				{
					if (p_b_fjsp_processing_time[o][m][j] != 0)
					{
						machine_number = m + 1;
						v_available_machines[j][o].push_back(machine_number);
					}
				}
				//cout << endl;
			}
			//cout << endl;
		}

		//��ʼ�����л�����workload = 0��
		int* p_machine_workload = new int[number_of_machines];
		for (int m = 0; m < number_of_machines; m++)
		{
			p_machine_workload[m] = 0;
		}
		//cout << endl;
		for (int j = 0; j < number_of_jobs2; j++)
		{
			CChromosome t3;
			//��ȡ��job��ÿ������Ŀ��û�����
			for (int o = 0; o < number_of_operations; o++)
			{
				int operation_machine_size = v_available_machines[j][o].size();
				//cout << "operation_machine_size = " << operation_machine_size << endl;
				//�ҳ�ÿ������ĵ�ǰ����workload��С�Ļ���
				//�����ÿ�������ʱ���п�ѡ������workload
				for (int m = 0; m < operation_machine_size; m++)
				{
					int number_m = v_available_machines[j][o][m];
					//cout << number_m << " ";
					//cout << p_machine_workload[number_m - 1] << endl;
				}
				//Ȼ���ҳ�������Сworkload�Ļ���
				int number_m = v_available_machines[j][o][0];//�ȰѸù����ѡ�ĵ�һ̨�����Ļ�������Ϊ��С����
				int min_machine_number = number_m;//��С������
				int min_machine_index = number_m - 1;//��С������������
				int min_machine_workload = p_machine_workload[min_machine_index];//��С�����ϵ�workload		
				for (int m = 0; m < operation_machine_size; m++)
				{
					int number_m = v_available_machines[j][o][m];
					//cout << number_m << " ";
					if (min_machine_workload > p_machine_workload[number_m - 1])
					{
						min_machine_workload = p_machine_workload[number_m - 1];
						min_machine_number = number_m;
					}
				}
				//cout << "min_machine_number = " << min_machine_number << endl;
				//Ȼ����¸�ѡ�еĻ�����workload
				p_machine_workload[min_machine_number - 1] += p_b_fjsp_processing_time[o][min_machine_number - 1][j];
				t3.job_number = j + 1;
				t3.machine_number = min_machine_number;

				t.v_chromosome2.push_back(t3);
			}
			//cout << endl;
		}
		//cout << endl;
		//system("pause");

		////���ÿ������
		//for (int j = 0; j < number_of_jobs1; j++)
		//{
		//	cout << t.v_chromosome1[j].factory_number << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs1; j < t.v_chromosome1.size(); j++)
		//{
		//	cout << t.v_chromosome1[j].job_number << " ";
		//}
		//cout << endl;

		//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
		//{
		//	cout << t.v_chromosome2[j].operation_number << " ";
		//}
		//cout << endl;
		//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
		//{
		//	cout << t.v_chromosome2[j].operation_index << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs2 * number_of_operations; j < t.v_chromosome2.size(); j++)
		//{
		//	cout << t.v_chromosome2[j].machine_number << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs2 * number_of_operations; j < t.v_chromosome2.size(); j++)
		//{
		//	cout << t.v_chromosome2[j].job_number << " ";
		//}
		//cout << endl;
		////system("pause");

		assign(t);//���ݹ���������ȡ��������
		//system("pause");

		//�ж��Ƿ��й���Ϊ�գ����й���Ϊ��������������ɹ�������
		for (int f = 0; f < number_of_factories; f++)
		{
			int f_size = t.v_job_assignment[f].size();
			if (f_size == 0)
			{
				int index_f;
				for (int j = 0; j < number_of_jobs1; j++)//Ⱦɫ�幤�����֣�������job����Ŀ���
				{
					index_f = rand() % number_of_factories + 1;//ȡֵ��Χ��[1,number_of_factories]
					t.v_chromosome1[j].job_number = j + 1;
					t.v_chromosome1[j].factory_number = index_f;
				}
				break;
			}

		}
		assign(t);//���ݹ���������ȡ��������
		evaluate_DFSP(t);
		evaluate_FJSP(t);
		evaluate(t);

		//system("pause");
		v_Chromo.push_back(t);
	}

	//for (int i = 0; i < v_Chromo.size(); i++)
	//{
	//	cout << "i = " << i + 1 << endl;
	//	int total_lenth1 = v_Chromo[i].v_chromosome1.size();
	//	for (int j = 0; j < number_of_jobs1; j++)
	//	{
	//		cout << v_Chromo[i].v_chromosome1[j].factory_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs1; j < total_lenth1; j++)
	//	{
	//		cout<<v_Chromo[i].v_chromosome1[j].job_number << " ";
	//	}
	//	cout << endl;
	//	int total_lenth2 = v_Chromo[i].v_chromosome2.size();
	//	//cout << "---machine assignment vector---" << endl;
	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//	{
	//		cout << v_Chromo[i].v_chromosome2[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs2 * number_of_operations; j < total_lenth2; j++)
	//	{
	//		cout << v_Chromo[i].v_chromosome2[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	cout << "---objective value---" << endl;
	//	for (int ob = 0; ob < number_of_objectives; ob++)
	//	{
	//		cout <<v_Chromo[i].v_objective_value[ob] << " ";
	//	}
	//	cout << endl<<endl;
	//	cout << "key_cell = "<<v_Chromo[i].key_cell << endl;
	//}
	//system("pause");
}

void CGenetic::randomWay(CIndividual& t)//�ú�������������һ����������
{
	vector <CChromosome>().swap(t.v_chromosome1);//v_chromosome1�Ƕ���DFSP�����ԣ�����Ϊv_chromosome�Ǹ�����������swap�����ڴ�
	//step11:initialize DFSP factory assignment...
	int index1;
	for (int j = 0; j< number_of_jobs1; j++)//Ⱦɫ�幤�����֣�������job����Ŀ���
	{
		CChromosome t1;
		index1 = rand() % number_of_factories + 1;//ȡֵ��Χ��[1,number_of_factories]
		t1.factory_number = index1;
		t1.job_number = j + 1;		
		t.v_chromosome1.push_back(t1);
	}
	//step12:initialize DFSP job sequence...
	int i;
	int min = 1;
	int max = number_of_jobs1;
	int num = max - min + 1; //����� �� ��Ŀ��������ҵ����Ⱦɫ�峤����5����ô����Ҫ5�������
	int jobNo;//��ҵ��
	int *a = new int[num];//����һ������num��Ԫ�ص�����a[num]
	for (i = 0; i < num; i++)//Ϊ ÿ�� �����  ��ֵ
	{
		a[i] = i + min;//����Ⱦɫ�峤��=5����ônum=5����ô�����(����)�϶���1,2,3,4,5
	}                  //a[0]=1,a[1]=2,a[2]=3,a[3]=4,a[4]=5
	int index2;
	for (i = 0; i < num; i++)
	{
		CChromosome t2;
		//��������indexȡֵΪ (int)(num-i-1),
		index2 = (int)((float)(num - i) * rand() / ((RAND_MAX + 1) * 1.0));//����i=0ʱ��(int)(5-0-1),index��ȡֵΪ0.1,2,3,4
		jobNo = a[index2];//��index=2����ôa[2]=3,jobNo=3,Ҳ����˵��ҵ3��ѡ��
		t2.job_number = jobNo;
		t.v_chromosome1.push_back(t2);//����ҵ3 β�� �� �ø����Ⱦɫ������ �� ��һ������λ��
		a[index2] = a[num - i - 1];//��ʱ����ҵ3�Ѿ���ѡ���ˣ��������һ��Ԫ�����滻����Ϊɶ�أ���Ϊִ���´�ѭ��ʱ��i=1,��ô
	}//indexȡֵΪ0,1,2,3�ˣ���ôindex=4,��ôa[4]�����һ������ȡ�����ˣ���Ϊ��������ȡ������ǰ������Ѿ���ȡ�����ĸ��廥��Ԫ�ؼ���
	delete[] a;//��ʱ��a[0]=1,a[1]=2,a[2]=5,a[3]=4������i=1ѭ����i=1ʱ��indexȡֵΪ0,1,2,3����ʱ��ҵ3�պò����ظ�ȡ��������ҵ5������ȡ��


	vector <CChromosome>().swap(t.v_chromosome2);
	//step21:initialize operation sequence...
	int* p_temp = new int[number_of_jobs2 * number_of_operations];//Ⱦɫ�幤�򲿷֣�����=job����Ŀ��ÿ��job�Ĺ�����Ŀ����������ÿ��job��3������
	int index3 = 0;
	for (int j = 0; j < number_of_jobs2; j++)
	{
		for (int k = 0; k < number_of_operations; k++)
		{
			p_temp[index3] = j + 1;
			index3 = index3 + 1;
		}
	}	
	int total_operations_number = number_of_jobs2 * number_of_operations;
	int num2 = number_of_jobs2 * number_of_operations;
	int rand_num;
	for (int o = 0; o < total_operations_number; o++)
	{
		CChromosome t3;
		rand_num = rand() % num2;
		index3 = p_temp[rand_num];
		t3.job_number = index3;
		t3.operation_number = index3;
		t.v_chromosome2.push_back(t3);
		p_temp[rand_num] = p_temp[num2 - 1];
		num2 = num2 - 1;
	}
	delete[] p_temp;

	for (int j = 0; j < number_of_jobs2; j++)//�ж���ÿ��job�ĵڼ�������
	{
		int current_job_number = j + 1;
		int count = 0;
		//cout << "current_job_number = " << current_job_number << endl;
		for (int c = 0; c < total_operations_number; c++)
		{
			if (current_job_number == t.v_chromosome2[c].job_number)
			{
				count = count + 1;
				t.v_chromosome2[c].operation_index = count;
				//cout << "count = " << count << endl;
			}
			continue;	
		}
	}

	//step22:initialize machine assignment...
	//���ȣ�Ҫ���ÿ��job��ÿ������Ŀ��û�����
	vector<vector<vector<int>>>().swap(v_available_machines);
	for (int j = 0; j < number_of_jobs2; j++)
	{
		vector <vector<int>> v1;
		v_available_machines.push_back(v1);	
		for (int o = 0; o < number_of_operations; o++)
		{
			vector <int> v2;
			v_available_machines[j].push_back(v2);
			int machine_number;
			for (int m = 0; m < number_of_machines; m++)
			{
				if (p_b_fjsp_processing_time[o][m][j] != 0.0)
				{
					machine_number = m + 1;
					//cout << "machine_number = " << machine_number << endl;
					v_available_machines[j][o].push_back(machine_number);
				}				
			}
			//cout << endl;
		}
		//cout << endl;
	}
	//cout << "ÿ��job��ÿ������Ŀ��û�������" << endl;
	//for (int j = 0; j < v_available_machines.size(); j++)
	//{
	//	cout << "job " << j + 1 << " �ļ�������Ŀ��û������ֱ��ǣ�" << endl;
	//	for (int o = 0; o < v_available_machines[j].size(); o++)
	//	{
	//		for (int m = 0; m < v_available_machines[j][o].size(); m++)
	//		{
	//			cout << v_available_machines[j][o][m] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//system("pause");

	//Ȼ�󣬴���������������
	for (int j = 0; j < number_of_jobs2; j++)
	{
		//cout << "j " << j << endl;
		CChromosome t4;
		//��ȡ��job��ÿ������Ŀ��û�����
		for (int o = 0; o < number_of_operations; o++)
		{			
			int operation_machine_size = v_available_machines[j][o].size();
			//cout << "operation_machine_size = " << operation_machine_size << endl;
			int rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			int rand_machine_number = v_available_machines[j][o][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
			t4.job_number = j + 1;
			t4.machine_number = rand_machine_number;
			t.v_chromosome2.push_back(t4);
		}
		//cout << endl;
	}
	//cout << endl;

	//int total_num1 = t.v_chromosome1.size();
	//cout << "DFSP�������䣺" << endl;
	//for (int k = 0; k < number_of_jobs1; k++)
	//{
	//	cout << t.v_chromosome1[k].factory_number << " ";
	//}
	//cout << endl;
	////for (int k = 0; k < number_of_jobs1; k++)
	////{
	////	cout << t.v_chromosome1[k].job_number << " ";
	////}
	////cout << endl;
	//cout << "DFSP��ҵ˳��" << endl;
	//for (int k = number_of_jobs1; k < total_num1; k++)
	//{
	//	cout << t.v_chromosome1[k].job_number << " ";
	//}
	//cout << endl;

	//int total_num2 = t.v_chromosome2.size();
	//cout << "FJSP�����б�" << endl;
	//for (int k = 0; k < total_operations_number ; k++)
	//{
	//	cout << t.v_chromosome2[k].operation_number << " ";
	//}
	//cout << endl;
	////for (int k = 0; k < total_operations_number; k++)
	////{
	////	cout << t.v_chromosome2[k].job_number << " ";
	////}
	////cout << endl;
	////for (int k = 0; k < total_operations_number; k++)
	////{
	////	cout << t.v_chromosome2[k].operation_index << " ";
	////}
	////cout << endl;
	//cout << "FJSP�������䣺" << endl;
	//for (int k = total_operations_number; k < total_num2; k++)
	//{
	//	cout << t.v_chromosome2[k].machine_number << " ";
	//}
	//cout << endl;
	////for (int k = total_operations_number; k < total_num2; k++)
	////{
	////	cout << t.v_chromosome2[k].job_number << " ";
	////}
	////cout << endl;
	//system("pause");
}

void CGenetic::assign(CIndividual& t)//������������
{
	vector <vector<int>>().swap(t.v_job_assignment);
	for (int i = 0; i < number_of_factories; i++)
	{
		vector <int> v;
		t.v_job_assignment.push_back(v);
	}
	
	for (int j = 0; j < number_of_jobs1; j++)
	{
		if (t.v_chromosome1[j].factory_number == 1)
		{
			int job_number = t.v_chromosome1[j].job_number;
			t.v_job_assignment[0].push_back(job_number);
		}
		else if (t.v_chromosome1[j].factory_number == 2)
		{
			int job_number = t.v_chromosome1[j].job_number;
			t.v_job_assignment[1].push_back(job_number);
		}
		else if (t.v_chromosome1[j].factory_number == 3)
		{
			int job_number = t.v_chromosome1[j].job_number;
			t.v_job_assignment[2].push_back(job_number);
		}
		else if (t.v_chromosome1[j].factory_number == 4)
		{
			int job_number = t.v_chromosome1[j].job_number;
			t.v_job_assignment[3].push_back(job_number);
		}

	}
	//���ÿ������Ĺ����������
	//cout << "job�Ĺ������������" << endl;
	//for (int f = 0; f < number_of_factories; f++)
	//{
	//	int f_size = t.v_job_assignment[f].size();
	//	for (int r = 0; r < f_size; r++)
	//	{
	//		cout << t.v_job_assignment[f][r] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	////�����������ҵ�������
	t.v_factory_job_assignment = t.v_job_assignment;
	for (int i = 0; i < number_of_factories; i++)
	{
		int f_size = t.v_job_assignment[i].size();
		for (int j = 0; j < f_size; j++)
		{
			//cout << t.v_job_assignment[i][j] << " ";
			int job_number = t.v_job_assignment[i][j];
			//cout << "job_number=" << job_number << endl;
			int job_index = job_number - 1;
			//cout << "job_index = " << job_index << endl;
			int location_index = 0;//��ȡ��ǰ������Ⱦɫ���е�λ������
			for (int num = number_of_jobs1; num < t.v_chromosome1.size(); num++)
			{
				if (job_index + 1 == t.v_chromosome1[num].job_number)
				{
					location_index = num;
					break;
				}
			}
			//cout << "location_index = " << location_index << endl;//��ȡ��ǰ������Ⱦɫ���е�λ������
			t.v_factory_job_assignment[i][j] = location_index;
		}
		//cout << endl;
	}
	//cout << endl;

	//for (int i = 0; i < number_of_factories; i++)
	//{
	//	int f_size = t.v_factory_job_assignment[i].size();
	//	for (int j = 0; j < f_size; j++)
	//	{
	//		cout << t.v_factory_job_assignment[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	//��ÿ�������е�job����������Ⱦɫ���г��ֵ�˳�����ð������
	for (int i = 0; i < number_of_factories; i++)
	{
		int f_size = t.v_factory_job_assignment[i].size();
		for (int j = 0; j < f_size - 1; j++)
		{
			for (int k = 0; k < f_size - 1 - j; k++)
			{
				if (t.v_factory_job_assignment[i][k + 1] < t.v_factory_job_assignment[i][k])
				{
					int temp1 = t.v_factory_job_assignment[i][k];
					t.v_factory_job_assignment[i][k] = t.v_factory_job_assignment[i][k + 1];
					t.v_factory_job_assignment[i][k + 1] = temp1;

					int temp2 = t.v_job_assignment[i][k];
					t.v_job_assignment[i][k] = t.v_job_assignment[i][k + 1];
					t.v_job_assignment[i][k + 1] = temp2;
				}
			}
		}
	}
	//cout << "after" << endl;
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

	//for (int i = 0; i < number_of_factories; i++)
	//{
	//	int f_size = t.v_factory_job_assignment[i].size();
	//	for (int j = 0; j < f_size; j++)
	//	{
	//		cout << t.v_factory_job_assignment[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
}