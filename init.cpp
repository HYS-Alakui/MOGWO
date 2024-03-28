#include "Genetic.h"
#include "Individual.h"
#include "rankSequ.h"
#include "headfile.h"
#include "random.h"
#include "Chromosome.h"
#include <iomanip>
#include <vector>
#include <algorithm>

void CGenetic::init_parameters()//初始化参数
{	
	number_of_objectives = 2;//目标数量
	current_number_of_fitness_evaluations = 0;//当前适应度评估次数
	number_of_jobs = number_of_jobs1 + number_of_jobs2;
	//cout << "number_of_jobs = " << number_of_jobs << endl;
	total_number_of_fitness_evaluations = 40 * number_of_jobs * number_of_machines;//停止条件：总适应度评估次数	
	//cout << total_number_of_fitness_evaluations << endl;
	number_of_individuals = 80;//个体数目
	iteration_num = 0;
		
	//求每个非标准件的设计时间=累加每个非标准件包含的工序的设计时间
	p_nonpart_design_time = new double[number_of_jobs2];
	for (int i = 0; i < number_of_jobs2; i++)
	{
		p_nonpart_design_time[i] = 0;
		for (int j = 0; j < number_of_operations; j++)
		{
			p_nonpart_design_time[i] += p_b_fjsp_design_time[j][i];
		}
		//cout << "每个非标准件的设计时间：" << p_nonpart_design_time[i] << endl;
	}
	//cout << endl;

	//找出最大的设计时间
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

	//求每个非标准件的设计成本=累加每个非标准件包含的工序的设计成本
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
		//cout << "每个非标准件的设计成本：" << p_nonpart_design_cost[i] << endl;
	}	
	total_design_cost = 0;
	for (int i = 0; i < number_of_jobs2; i++)
	{
		total_design_cost += p_nonpart_design_cost[i];
	}
	//cout << "total_design_cost = " << total_design_cost << endl;
	//system("pause");
}//以上 完成 初始化参数，与genetic.h和finfout.cpp对应着看

void CGenetic::generInitPopu()//初始化种群
{
	//cout << "------------1、初始化种群---------" << endl;
	vector <CIndividual>().swap(v_Chromo);//巧用swap缩短内存，种群初始化为空；vector.clear()清空内容，但是没有释放内存;但是swap技法可以。 那么如何释放内存呢？我们用swap交换到一个新的类型的vector,将原来的v_Chromo拷贝出去，然后自然销毁，而新的到的v_Chromo是全新的没有存任何数据的。	
	for (int i = 0; i < 0.9 * number_of_individuals; i++)//随机生成
	{
		//cout << "i = " << i << endl;
		CIndividual t;
		randomWay(t);//调用 randomWay函数，将具体对象t（实参）传入形参(CIndividual& t)，然后返回一个随机个体
		//////输出每个个体
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

		assign(t);//根据工厂向量获取工厂数组
		//system("pause");

		//判断是否有工厂为空，若有工厂为空则重新随机生成工厂向量
		for (int f = 0; f < number_of_factories; f++)
		{
			int f_size = t.v_job_assignment[f].size();
			if (f_size == 0)
			{
				int index_f;
				for (int j = 0; j < number_of_jobs1; j++)//染色体工厂部分，长度与job的数目相等
				{
					index_f = rand() % number_of_factories + 1;//取值范围是[1,number_of_factories]
					t.v_chromosome1[j].job_number = j + 1;
					t.v_chromosome1[j].factory_number = index_f;
				}
				break;
			}

		}
		assign(t);//根据工厂向量获取工厂数组
		evaluate_DFSP(t);
		evaluate_FJSP(t);
		evaluate(t);

		//system("pause");
		v_Chromo.push_back(t);
	}

	for (int i = 0.9 * number_of_individuals; i < 0.95 * number_of_individuals; i++)//机器向量使用OMPT规则
	{
		CIndividual t;
		vector <CChromosome>().swap(t.v_chromosome1);//v_chromosome1是对象DFSP的属性，又因为v_chromosome是个容器，巧用swap缩短内存
		//step11:initialize DFSP factory assignment...
		int index1;
		for (int j = 0; j < number_of_jobs1; j++)//染色体工厂部分，长度与job的数目相等
		{
			CChromosome t1;
			index1 = rand() % number_of_factories + 1;//取值范围是[1,number_of_factories]
			t1.factory_number = index1;
			t1.job_number = j + 1;
			t.v_chromosome1.push_back(t1);
		}
		//step12:initialize DFSP job sequence...
		int ii;
		int min = 1;
		int max = number_of_jobs1;
		int num = max - min + 1; //随机数 的 数目，比如作业部分染色体长度是5，那么就需要5个随机数
		int jobNo;//作业号
		int* a = new int[num];//开辟一个包含num个元素的数组a[num]
		for (ii = 0; ii < num; ii++)//为 每个 随机数  赋值
		{
			a[ii] = ii + min;//比如染色体长度=5，那么num=5，那么随机数(基因)肯定是1,2,3,4,5
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
		int* p_temp = new int[number_of_jobs2 * number_of_operations];//染色体工序部分，长度=job的数目×每个job的工序数目；本文设置每个job有3道工序；
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

		for (int j = 0; j < number_of_jobs2; j++)//判断是每个job的第几道工序
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
		//首先，要获得每个job的每道工序的可用机器集
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
			//获取该job的每道工序的可用机器集
			for (int o = 0; o < number_of_operations; o++)
			{
				int operation_machine_size = v_available_machines[j][o].size();
				//cout << "operation_machine_size = " << operation_machine_size << endl;
				//找出每道工序的加工时间最小的机器
				for (int m = 0; m < operation_machine_size; m++)
				{
					int number_m = v_available_machines[j][o][m];
					//cout << number_m << " ";
					//cout << p_b_fjsp_processing_time[o][number_m - 1][j] <<endl;
				}
				int number_m = v_available_machines[j][o][0];//先把该工序的第一台机器的机器号作为最小机器
				int min_machine_number = number_m;//最小机器号
				int min_machine_index = number_m - 1;//最小机器的索引号
				int min_machine_time = p_b_fjsp_processing_time[o][min_machine_index][j];//最小机器上的加工时间				
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

		////输出每个个体
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

		assign(t);//根据工厂向量获取工厂数组
		//system("pause");

		//判断是否有工厂为空，若有工厂为空则重新随机生成工厂向量
		for (int f = 0; f < number_of_factories; f++)
		{
			int f_size = t.v_job_assignment[f].size();
			if (f_size == 0)
			{
				int index_f;
				for (int j = 0; j < number_of_jobs1; j++)//染色体工厂部分，长度与job的数目相等
				{
					index_f = rand() % number_of_factories + 1;//取值范围是[1,number_of_factories]
					t.v_chromosome1[j].job_number = j + 1;
					t.v_chromosome1[j].factory_number = index_f;
				}
				break;
			}

		}
		assign(t);//根据工厂向量获取工厂数组
		evaluate_DFSP(t);
		evaluate_FJSP(t);
		evaluate(t);

		//system("pause");
		v_Chromo.push_back(t);
	}

	for (int i = 0.95 * number_of_individuals; i < number_of_individuals; i++)//机器向量使用OMPT规则
	{
		CIndividual t;
		vector <CChromosome>().swap(t.v_chromosome1);//v_chromosome1是对象DFSP的属性，又因为v_chromosome是个容器，巧用swap缩短内存
		//step11:initialize DFSP factory assignment...
		int index1;
		for (int j = 0; j < number_of_jobs1; j++)//染色体工厂部分，长度与job的数目相等
		{
			CChromosome t1;
			index1 = rand() % number_of_factories + 1;//取值范围是[1,number_of_factories]
			t1.factory_number = index1;
			t1.job_number = j + 1;
			t.v_chromosome1.push_back(t1);
		}
		//step12:initialize DFSP job sequence...
		int ii;
		int min = 1;
		int max = number_of_jobs1;
		int num = max - min + 1; //随机数 的 数目，比如作业部分染色体长度是5，那么就需要5个随机数
		int jobNo;//作业号
		int* a = new int[num];//开辟一个包含num个元素的数组a[num]
		for (ii = 0; ii < num; ii++)//为 每个 随机数  赋值
		{
			a[ii] = ii + min;//比如染色体长度=5，那么num=5，那么随机数(基因)肯定是1,2,3,4,5
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
		int* p_temp = new int[number_of_jobs2 * number_of_operations];//染色体工序部分，长度=job的数目×每个job的工序数目；本文设置每个job有3道工序；
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

		for (int j = 0; j < number_of_jobs2; j++)//判断是每个job的第几道工序
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
		//首先，要获得每个job的每道工序的可用机器集
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

		//初始化所有机器的workload = 0；
		int* p_machine_workload = new int[number_of_machines];
		for (int m = 0; m < number_of_machines; m++)
		{
			p_machine_workload[m] = 0;
		}
		//cout << endl;
		for (int j = 0; j < number_of_jobs2; j++)
		{
			CChromosome t3;
			//获取该job的每道工序的可用机器集
			for (int o = 0; o < number_of_operations; o++)
			{
				int operation_machine_size = v_available_machines[j][o].size();
				//cout << "operation_machine_size = " << operation_machine_size << endl;
				//找出每道工序的当前具有workload最小的机器
				//先输出每道工序此时所有可选机器的workload
				for (int m = 0; m < operation_machine_size; m++)
				{
					int number_m = v_available_machines[j][o][m];
					//cout << number_m << " ";
					//cout << p_machine_workload[number_m - 1] << endl;
				}
				//然后找出具有最小workload的机器
				int number_m = v_available_machines[j][o][0];//先把该工序可选的第一台机器的机器号作为最小机器
				int min_machine_number = number_m;//最小机器号
				int min_machine_index = number_m - 1;//最小机器的索引号
				int min_machine_workload = p_machine_workload[min_machine_index];//最小机器上的workload		
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
				//然后更新该选中的机器的workload
				p_machine_workload[min_machine_number - 1] += p_b_fjsp_processing_time[o][min_machine_number - 1][j];
				t3.job_number = j + 1;
				t3.machine_number = min_machine_number;

				t.v_chromosome2.push_back(t3);
			}
			//cout << endl;
		}
		//cout << endl;
		//system("pause");

		////输出每个个体
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

		assign(t);//根据工厂向量获取工厂数组
		//system("pause");

		//判断是否有工厂为空，若有工厂为空则重新随机生成工厂向量
		for (int f = 0; f < number_of_factories; f++)
		{
			int f_size = t.v_job_assignment[f].size();
			if (f_size == 0)
			{
				int index_f;
				for (int j = 0; j < number_of_jobs1; j++)//染色体工厂部分，长度与job的数目相等
				{
					index_f = rand() % number_of_factories + 1;//取值范围是[1,number_of_factories]
					t.v_chromosome1[j].job_number = j + 1;
					t.v_chromosome1[j].factory_number = index_f;
				}
				break;
			}

		}
		assign(t);//根据工厂向量获取工厂数组
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

void CGenetic::randomWay(CIndividual& t)//该函数是用来产生一个随机个体的
{
	vector <CChromosome>().swap(t.v_chromosome1);//v_chromosome1是对象DFSP的属性，又因为v_chromosome是个容器，巧用swap缩短内存
	//step11:initialize DFSP factory assignment...
	int index1;
	for (int j = 0; j< number_of_jobs1; j++)//染色体工厂部分，长度与job的数目相等
	{
		CChromosome t1;
		index1 = rand() % number_of_factories + 1;//取值范围是[1,number_of_factories]
		t1.factory_number = index1;
		t1.job_number = j + 1;		
		t.v_chromosome1.push_back(t1);
	}
	//step12:initialize DFSP job sequence...
	int i;
	int min = 1;
	int max = number_of_jobs1;
	int num = max - min + 1; //随机数 的 数目，比如作业部分染色体长度是5，那么就需要5个随机数
	int jobNo;//作业号
	int *a = new int[num];//开辟一个包含num个元素的数组a[num]
	for (i = 0; i < num; i++)//为 每个 随机数  赋值
	{
		a[i] = i + min;//比如染色体长度=5，那么num=5，那么随机数(基因)肯定是1,2,3,4,5
	}                  //a[0]=1,a[1]=2,a[2]=3,a[3]=4,a[4]=5
	int index2;
	for (i = 0; i < num; i++)
	{
		CChromosome t2;
		//此随机命令，index取值为 (int)(num-i-1),
		index2 = (int)((float)(num - i) * rand() / ((RAND_MAX + 1) * 1.0));//比如i=0时，(int)(5-0-1),index能取值为0.1,2,3,4
		jobNo = a[index2];//设index=2，那么a[2]=3,jobNo=3,也就是说作业3被选中
		t2.job_number = jobNo;
		t.v_chromosome1.push_back(t2);//将作业3 尾插 到 该个体的染色体数组 的 第一个基因位置
		a[index2] = a[num - i - 1];//此时，作业3已经被选中了，故找最后一个元素来替换它，为啥呢，因为执行下次循环时，i=1,那么
	}//index取值为0,1,2,3了，那么index=4,那么a[4]即最后一个个体取不到了，故为了让它能取到，跟前面这个已经被取到过的个体互换元素即可
	delete[] a;//此时，a[0]=1,a[1]=2,a[2]=5,a[3]=4。进入i=1循环，i=1时，index取值为0,1,2,3；此时作业3刚好不被重复取到，而作业5有望被取到


	vector <CChromosome>().swap(t.v_chromosome2);
	//step21:initialize operation sequence...
	int* p_temp = new int[number_of_jobs2 * number_of_operations];//染色体工序部分，长度=job的数目×每个job的工序数目；本文设置每个job有3道工序；
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

	for (int j = 0; j < number_of_jobs2; j++)//判断是每个job的第几道工序
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
	//首先，要获得每个job的每道工序的可用机器集
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
	//cout << "每个job的每道工序的可用机器集：" << endl;
	//for (int j = 0; j < v_available_machines.size(); j++)
	//{
	//	cout << "job " << j + 1 << " 的几道工序的可用机器集分别是：" << endl;
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

	//然后，创建机器分配向量
	for (int j = 0; j < number_of_jobs2; j++)
	{
		//cout << "j " << j << endl;
		CChromosome t4;
		//获取该job的每道工序的可用机器集
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
	//cout << "DFSP工厂分配：" << endl;
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
	//cout << "DFSP作业顺序：" << endl;
	//for (int k = number_of_jobs1; k < total_num1; k++)
	//{
	//	cout << t.v_chromosome1[k].job_number << " ";
	//}
	//cout << endl;

	//int total_num2 = t.v_chromosome2.size();
	//cout << "FJSP工序列表：" << endl;
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
	//cout << "FJSP机器分配：" << endl;
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

void CGenetic::assign(CIndividual& t)//工厂分配数组
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
	//输出每个个体的工厂分配情况
	//cout << "job的工厂分配情况：" << endl;
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

	////输出工厂的作业分配情况
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
			int location_index = 0;//获取当前工件在染色体中的位置索引
			for (int num = number_of_jobs1; num < t.v_chromosome1.size(); num++)
			{
				if (job_index + 1 == t.v_chromosome1[num].job_number)
				{
					location_index = num;
					break;
				}
			}
			//cout << "location_index = " << location_index << endl;//获取当前工件在染色体中的位置索引
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

	//对每个工厂中的job按照它们在染色体中出现的顺序进行冒泡排序
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