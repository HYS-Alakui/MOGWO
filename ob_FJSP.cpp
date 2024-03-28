#include <iomanip>
#include "Genetic.h"
#include "Individual.h"
#include "random.h"
#include <cmath>

void CGenetic::evaluate_FJSP(CIndividual& t)//评估适应度
{
	//step1：获取每个工厂包含的待加工工序
	vector <vector<CChromosome>> v_factory_operation;
	for (int f = 0; f < 1; f++)
	{
		vector<CChromosome> v;
		v_factory_operation.push_back(v);
	}
	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	{
		int j_num = t.v_chromosome2[j].job_number;//找出该工序的所属job
		//cout << "j_num = " << j_num << endl;	
		int o_num = t.v_chromosome2[j].operation_index;//找出该工序是第几道工序
		//cout << "o_num = " << o_num << endl;
		int m_num_index = number_of_jobs2 * number_of_operations + (j_num - 1) * number_of_operations + o_num - 1;
		int m_num = t.v_chromosome2[m_num_index].machine_number;//找到该job该工序的所属机器
		//cout << "m_num = " << m_num << endl;

		CChromosome ttt;
		ttt.job_number = j_num;
		ttt.operation_index = o_num;
		ttt.machine_number = m_num;
		v_factory_operation[0].push_back(ttt);
	}
	//cout << "每个工厂包含的工序的信息(工序序列；工序的序号；工序所属的机器)：" << endl;
	//for (int f = 0; f < v_factory_operation.size(); f++)
	//{
	//	cout << "F" << f+1 << "---opera_seque_job：";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{		
	//		cout << v_factory_operation[f][n].job_number << " ";
	//	}
	//	cout << endl;
	//	cout << "F" << f+1 << "---operation_index：";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{
	//		cout << v_factory_operation[f][n].operation_index << " ";
	//	}
	//	cout << endl;
	//	cout << "F" << f+1 << "----machine_number：";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{
	//		cout << v_factory_operation[f][n].machine_number << " ";
	//	}
	//	cout << endl <<endl;
	//}
	//cout << endl;
	//system("pause");

	//step2：每个非标准件的每道工序的定制加工时间
	p_c_fjsp_processing_time = new int**[number_of_operations];//是一个包含number_of_factories个元素的数组1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_c_fjsp_processing_time[i] = new int*[number_of_machines];//数组1中 每个元素 都指向一个 包含number_of_machines个元素的数组2
		for (int j = 0; j < number_of_machines; j++)
		{
			p_c_fjsp_processing_time[i][j] = new int[number_of_jobs2];
		}
	}
	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			for (int k = 0; k < number_of_jobs2; k++)
			{
				p_c_fjsp_processing_time[i][j][k] = (1 + (p_degree[i][k]/3)) * p_b_fjsp_processing_time[i][j][k];
				//cout << p_c_fjsp_processing_time[i][j][k] << " ";
			}
			//cout << endl;
		}
		//cout << endl;
	}
	//cout << endl;
	//system("pause");


	//step3:求每个工厂的机器加工的工序的job号、对应的工序号、工序的开始和完工时间
	double** p_operation_completion_time;
	p_operation_completion_time = new double*[number_of_jobs2];
	for (int j = 0; j < number_of_jobs2; j++)
	{
		p_operation_completion_time[j] = new double[number_of_operations];
	}
	for (int j = 0; j < number_of_jobs2; j++)//对开辟的种群初始化
	{
		for (int o = 0; o < number_of_operations; o++)
		{
			p_operation_completion_time[j][o] = 0;
		}
	}
	//cout << endl;
	double* p_completion_time2 = new double[number_of_jobs2];
	for (int j = 0; j < number_of_jobs2; j++)
	{
		p_completion_time2[j] = 0;
	}

	vector<vector<int> > M_J(number_of_machines); //该机器加工的工序对应的作业编号
	vector<vector<int> > M_O(number_of_machines);//该机器加工的工序对应的第几个工序；
	vector<vector<double> > m_s_t(number_of_machines);//该机器加工的每个工序的开始时间
	vector<vector<double> > m_f_t(number_of_machines);//该机器加工的每个工序的完工时间
	for (int i = 0; i < 1; i++)
	{
		for (int o = 0; o < v_factory_operation[i].size(); o++)
		{
			int machine_index = v_factory_operation[i][o].machine_number;//该工序所在机器
			int Job_index = v_factory_operation[i][o].job_number;//工序作业号
			int Operation_index = v_factory_operation[i][o].operation_index;//工序在作业中的顺序
			if (Operation_index == 1)//是作业的第一个工序
			{
				if (M_J[machine_index - 1].empty())//该机器上未有工序
				{
					M_J[machine_index - 1].push_back(Job_index);
					M_O[machine_index - 1].push_back(Operation_index);
					m_s_t[machine_index - 1].push_back(max_design_value);
					m_f_t[machine_index - 1].push_back(max_design_value + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
				}
				else if (!M_J[machine_index - 1].empty())
				{//该机器上已有工序
					int successinsert = 0;//是否插入进去了
					for (int k = 0; k < M_J[machine_index - 1].size(); k++)
					{
						if (k == 0)
						{
							double Itime = m_s_t[machine_index - 1][k] - max_design_value;
							if (p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= Itime)
							{
								M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
								M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
								m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, max_design_value);
								m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
								successinsert = 1;
								break;
							}
						}
						else if (k != 0)
						{
							double Itime = m_s_t[machine_index - 1][k] - m_f_t[machine_index - 1][k - 1];
							if (p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= Itime)
							{
								M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
								M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
								m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, m_f_t[machine_index - 1][k - 1]);
								m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
								successinsert = 1;
								break;
							}
						}
					}
					if (successinsert != 1) //未插入，放在最后
					{
						M_J[machine_index - 1].push_back(Job_index);
						M_O[machine_index - 1].push_back(Operation_index);
						m_s_t[machine_index - 1].push_back(m_f_t[machine_index - 1][m_f_t[machine_index - 1].size() - 1]);
						m_f_t[machine_index - 1].push_back(m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
					}
				}
			}
			//不是作业的第一个工序
			else if (Operation_index != 1)
			{
				//找到该工序的前工序的机器号，存储前工序在它所属机器上的结束时间
				int find_index = number_of_jobs2 *number_of_operations + (Job_index - 1) * number_of_operations + (Operation_index - 1) - 1;
				int mach = t.v_chromosome2[find_index].machine_number;//前工序的机器号
				//找到该工序的前工序，让其开始时间等于前工序的完工时间
				double finishtime = 0;
				for (int s = 0; s < M_J[mach - 1].size(); s++)
				{
					if (M_J[mach - 1][s] == Job_index)
					{
						if (M_O[mach - 1][s] == Operation_index - 1)
						{
							finishtime = m_f_t[mach - 1][s];
						}
					}
				}

				if (M_J[machine_index - 1].empty()) //该机器上未有工序		
				{
					m_s_t[machine_index - 1].push_back(finishtime);
					m_f_t[machine_index - 1].push_back(m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
					M_J[machine_index - 1].push_back(Job_index);
					M_O[machine_index - 1].push_back(Operation_index);
				}
				else if (!M_J[machine_index - 1].empty()) //该机器上已有工序
				{
					int successinsert = 0;//是否插入进去了
					vector<double>Itime;//该机器上每个工序之间的空闲时间
					for (int k = 0; k < M_J[machine_index - 1].size(); k++)
					{
						if (finishtime < m_s_t[machine_index - 1][k])
						{
							if (k == 0)
							{
								//double Itime = m_s_t[machine_index - 1][k] - 0;
								if (finishtime + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= m_s_t[machine_index - 1][k])
								{
									m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, finishtime);
									m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
									M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
									M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
									successinsert = 1;
									break;
								}
							}
							else if (k != 0)
							{
								double Itime = m_s_t[machine_index - 1][k] - m_f_t[machine_index - 1][k - 1];
								if (p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= Itime)
								{
									if (finishtime <= m_f_t[machine_index - 1][k - 1])
									{
										m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, m_f_t[machine_index - 1][k - 1]);
										m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
										M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
										M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
										successinsert = 1;
										break;
									}
									else if (finishtime > m_f_t[machine_index - 1][k - 1] && finishtime + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1] <= m_s_t[machine_index - 1][k])
									{
										m_s_t[machine_index - 1].insert(m_s_t[machine_index - 1].begin() + k, finishtime);
										m_f_t[machine_index - 1].insert(m_f_t[machine_index - 1].begin() + k, m_s_t[machine_index - 1][k] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
										M_J[machine_index - 1].insert(M_J[machine_index - 1].begin() + k, Job_index);
										M_O[machine_index - 1].insert(M_O[machine_index - 1].begin() + k, Operation_index);
										successinsert = 1;
										break;
									}
								}
							}
						}
					}
					if (successinsert != 1)
					{
						if (finishtime <= m_f_t[machine_index - 1][m_f_t[machine_index - 1].size() - 1]) {
							m_s_t[machine_index - 1].push_back(m_f_t[machine_index - 1][m_f_t[machine_index - 1].size() - 1]);
							m_f_t[machine_index - 1].push_back(m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
							M_J[machine_index - 1].push_back(Job_index);
							M_O[machine_index - 1].push_back(Operation_index);
						}
						else if (finishtime > m_f_t[machine_index - 1][m_f_t[machine_index - 1].size() - 1]) {
							m_s_t[machine_index - 1].push_back(finishtime);
							m_f_t[machine_index - 1].push_back(m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
							M_J[machine_index - 1].push_back(Job_index);
							M_O[machine_index - 1].push_back(Operation_index);
						}
					}
				}
			}
		}
	}
	//以上求出了每个job的每道工序在不同机器上的完工时间
	//cout << "每台机器加工的工序对应的作业编号" << endl;
	//for (int mj = 0; mj < M_J.size(); mj++)
	//{
	//	for (int mk = 0; mk < M_J[mj].size(); mk++)
	//	{
	//		cout << M_J[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "每台机器加工的工序对应的工序序号" << endl;
	//for (int mj = 0; mj < M_O.size(); mj++)
	//{
	//	for (int mk = 0; mk < M_O[mj].size(); mk++)
	//	{
	//		cout << M_O[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "每台机器加工的工序的开始时间" << endl;
	//for (int mj = 0; mj < m_s_t.size(); mj++)
	//{
	//	for (int mk = 0; mk < m_s_t[mj].size(); mk++)
	//	{
	//		cout << m_s_t[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "每台机器加工的工序的结束时间" << endl;//根据这个数组可以找到具有最大完工时间的工序所在的机器号以及位置号
	int max_operation_index = 0;
	int max_machine_index = 0;
	int max_position_index = 0;
	int max_operation_value = 0;
	for (int mj = 0; mj < m_f_t.size(); mj++)
	{
		for (int mk = 0; mk < m_f_t[mj].size(); mk++)
		{
			//cout << m_f_t[mj][mk] << " ";
			if (m_f_t[mj][mk] > max_operation_value)
			{
				max_operation_value = m_f_t[mj][mk];
				max_operation_index = M_J[mj][mk] - 1;
				max_machine_index = mj;
				max_position_index = mk;
			}
		}
		//cout << endl;
	}
	//cout << endl;
	//cout << "max_operation_index = " << max_operation_index << endl;
	//cout << "max_machine_index = " << max_machine_index << endl;
	//cout << "max_position_index = " << max_position_index << endl;
	//cout << "max_operation_value = " << max_operation_value << endl;

	////step4：求每个job的每道工序的完工时间
	for (int u = 0; u < M_J.size(); u++)
	{
		for (int v = 0; v < M_J[u].size(); v++)
		{
			int current_job_number = M_J[u][v];
			int current_job_operation_index = M_O[u][v];
			p_operation_completion_time[current_job_number - 1][current_job_operation_index - 1] = m_f_t[u][v];
		}
		//cout << endl;
	}
	//cout << endl;
	
	////step5：求每个job的的完工时间
	for (int w = 0; w < number_of_jobs2; w++)
	{
		p_completion_time2[w] = p_operation_completion_time[w][number_of_operations - 1];
		//cout << p_completion_time2[w] << endl;
	}

	/////step6：求makespan
	int max_completion_time;
	max_completion_time = p_completion_time2[0];
	for (int i = 0; i < number_of_jobs2; i++)
	{
		if (max_completion_time < p_completion_time2[i])
		{
			max_completion_time = p_completion_time2[i];
		}
	}
	FJSP_makespan = max_completion_time;//获取该个体的makespan
	//cout << "FJSP_makespan = " << FJSP_makespan <<endl;
	t.FJSP_makespan_value = FJSP_makespan;
	//system("pause");

	////step7:求生产阶段的成本：每台机器都有单位时间加工成本，故该机器上的成本=该机器加工的工序的加工时间×单位时间加工成本；汇总所有机器即可
	////此外这里需要开辟一个数组，储存每台机器的加工成本以获取关键机器
	double* p_machine_cost = new double[number_of_machines];//储存每个机器的加工成本
	for (int pp = 0; pp < number_of_machines; pp++)//初始化
	{
		p_machine_cost[pp] = 0;
	}
	total_production_cost2 = 0;//目标1的第一部分
	for (int i = 0; i < v_factory_operation.size(); i++)
	{
		for (int j = 0; j < v_factory_operation[i].size(); j++)
		{
			int job_index = v_factory_operation[i][j].job_number - 1;
			int operation_index = v_factory_operation[i][j].operation_index - 1;
			int machine_index = v_factory_operation[i][j].machine_number - 1;
			double machine_cost = p_c_fjsp_processing_time[operation_index][machine_index][job_index] * p_unit_machine_cost2[machine_index];		
			//cout << "machine_cost =  "<< machine_cost << endl;
			p_machine_cost[machine_index] += machine_cost;
			total_production_cost2 = total_production_cost2 + p_c_fjsp_processing_time[operation_index][machine_index][job_index] * p_unit_machine_cost2[machine_index];
			//cout << "total_production_cost2 = " << total_production_cost2 << endl;
		}
		//cout << endl;
	}
	//cout << endl;
	//cout << "FJSP_makespan = " << FJSP_makespan <<endl;
	//cout << "t.FJSP_makespan_value = " << t.FJSP_makespan_value <<endl;
	//cout << "total_production_cost2 = " << total_production_cost2 << endl;
	
	/*********************************获取FJSP关键机器***************************************************/
	int key_machine_idx = 0;
	double max_machine_cost_value = 0;
	//cout << "每台机器的成本：" << endl;
	for (int pp = 0; pp < number_of_machines; pp++)
	{
		//cout << p_machine_cost[pp] << endl;
		if (p_machine_cost[pp] > max_machine_cost_value)
		{
			max_machine_cost_value = p_machine_cost[pp];
			key_machine_idx = pp;
		}
	}	
	t.key_machine_index = key_machine_idx;
	//cout << "FJSP的关键机器索引是：" << t.key_machine_index << endl;
	vector<int>().swap(t.Keymachine_Operation);
	vector<int>().swap(t.Keymachine_Operation_Xuhao);
	for (int qq = 0; qq < M_J[key_machine_idx].size(); qq++)
	{
		//cout << "工序编号：" << M_J[key_machine_idx][qq] << " ";
		t.Keymachine_Operation.push_back(M_J[key_machine_idx][qq]);
		//cout << "工序序号：" << M_O[key_machine_idx][qq] << endl;
		t.Keymachine_Operation_Xuhao.push_back(M_O[key_machine_idx][qq]);
	}
	//for (int g = 0; g < t.Keymachine_Operation.size(); g++)
	//{
	//	cout << "工序编号：" << t.Keymachine_Operation[g] << endl;
	//}
	//for (int g = 0; g < t.Keymachine_Operation_Xuhao.size(); g++)
	//{
	//	cout << "工序序号：" << t.Keymachine_Operation_Xuhao[g] << endl;
	//}
	//system("pause");

	/*********************************获取FJSP关键路径***************************************************/
	vector<int>Job;//关键路径的作业编号（倒）
	vector<int>Operation;//关键路径作业的工序编号（倒）
	vector<int>Machine;//关键路径作业的工序所在的机器索引号（倒）
	vector<double>s_t;//关键路径作业的工序的开始时间（倒）
	vector<double>f_t;//关键路径作业的工序的结束时间（倒）
	Job.push_back(M_J[max_machine_index][max_position_index]);
	Operation.push_back(M_O[max_machine_index][max_position_index]);
	Machine.push_back(max_machine_index);
	s_t.push_back(m_s_t[max_machine_index][max_position_index]);
	f_t.push_back(m_f_t[max_machine_index][max_position_index]);
	//cout << "max_design_value = " << max_design_value << endl;
	//cout << "aaaM_J[max_machine_index][max_position_index] - 1 =" << M_J[max_machine_index][max_position_index] - 1 << endl;
	while (m_s_t[max_machine_index][max_position_index] > max_design_value)
	{
		if (max_position_index == 0)
		{
			int break_2 = 0;
			int Sum_number = 0;
			//获取当前作业前面还有多少道工序,若当前作业编号是3 那么该作业前面就有（3-1）*number_of_operations道工序
			for (int r = 0; r < M_J[max_machine_index][max_position_index] - 1; r++)
			{
				Sum_number = Sum_number + number_of_operations;
			}
			//cout << "Sum_number =" << Sum_number << endl;
			//获取当前作业关键工序的前一个工序所属的机器编号
			int MACHINE = t.v_chromosome2[number_of_jobs2 * number_of_operations + Sum_number + M_O[max_machine_index][max_position_index] - 1 - 1].machine_number;//该job前一道工序的机器编号
			//cout << "MACHINE =" << MACHINE << endl;
			for (int q = 0; q < M_J[MACHINE - 1].size(); q++) //遍历关键机器上的工序
			{
				if (M_J[max_machine_index][max_position_index] == M_J[MACHINE - 1][q])
				{
					if (M_O[max_machine_index][max_position_index] == M_O[MACHINE - 1][q] + 1)
					{
						if (m_s_t[max_machine_index][max_position_index] == m_f_t[MACHINE - 1][q])
						{
							max_position_index = q;
							max_machine_index = MACHINE - 1;
							//cout << "bbbM_J[max_machine_index][max_position_index] - 1 =" << M_J[max_machine_index][max_position_index] - 1 << endl;
							Job.push_back(M_J[max_machine_index][max_position_index]);
							Operation.push_back(M_O[max_machine_index][max_position_index]);
							Machine.push_back(max_machine_index);
							s_t.push_back(m_s_t[max_machine_index][max_position_index]);
							f_t.push_back(m_f_t[max_machine_index][max_position_index]);
							break_2 = 1;
							break;
						}
					}
				}
			}
			if (break_2 == 1) 
			{
				continue;
			}
		}
		else if (max_position_index >= 1)
		{
			if (m_s_t[max_machine_index][max_position_index] == m_f_t[max_machine_index][max_position_index - 1])//若关键工序的开始时间==该位置前一道工序的完工时间
			{
				//cout << "同一机器前后两道工序首尾链接" << endl;
				max_position_index = max_position_index - 1;//更新关键工序：当前机器的前一道工序
				//cout << "cccM_J[max_machine_index][max_position_index] - 1 =" << M_J[max_machine_index][max_position_index] - 1 << endl;
				Job.push_back(M_J[max_machine_index][max_position_index]);
				Operation.push_back(M_O[max_machine_index][max_position_index]);
				Machine.push_back(max_machine_index);
				s_t.push_back(m_s_t[max_machine_index][max_position_index]);
				f_t.push_back(m_f_t[max_machine_index][max_position_index]);
			}
			else if (m_s_t[max_machine_index][max_position_index] != m_f_t[max_machine_index][max_position_index - 1])//若关键工序的开始时间！=该位置前一道工序的完工时间
			{
				//cout << "不连接,需要寻找当前关键工序所属job的上一道工序" << endl;
				int break_1 = 0;
				int Sum_number = 0;
				for (int r = 0; r < M_J[max_machine_index][max_position_index] - 1; r++)
				{
					Sum_number = Sum_number + number_of_operations;
				}
				int MACHINE = t.v_chromosome2[number_of_jobs2 * number_of_operations + Sum_number + M_O[max_machine_index][max_position_index] - 1 -1].machine_number;//上一道工序机器号
				//cout << "该job的前一道工序所在机器编号MACHINE =" << MACHINE << endl;
				for (int q = 0; q < M_J[MACHINE - 1].size(); q++) //遍历找位置索引
				{
					if (M_J[max_machine_index][max_position_index] == M_J[MACHINE - 1][q])
					{//作业相同
						if (M_O[max_machine_index][max_position_index] == M_O[MACHINE - 1][q] + 1)
						{//紧前工序
							if (m_s_t[max_machine_index][max_position_index] == m_f_t[MACHINE - 1][q])
							{
								max_position_index = q;//更新关键工序：job的上一道工序所在位置
								//cout << "max_position_index = " << max_position_index << endl;
								max_machine_index = MACHINE - 1;//机器号-1
								//cout << "max_machine_index = " << max_machine_index << endl;
								//cout << "dddM_J[max_machine_index][max_position_index] - 1 =" << M_J[max_machine_index][max_position_index] - 1 << endl;
								Job.push_back(M_J[max_machine_index][max_position_index]);
								Operation.push_back(M_O[max_machine_index][max_position_index]);
								Machine.push_back(max_machine_index);
								s_t.push_back(m_s_t[max_machine_index][max_position_index]);
								f_t.push_back(m_f_t[max_machine_index][max_position_index]);
								break_1 = 1;
								break;
							}
						}
					}
				}
				if (break_1 == 1) 
				{
					continue;
				}
			}
		}
	}

	//FJSP关键路径
	vector<int>().swap(t.Job_C);
	vector<int>().swap(t.Operation_C);
	vector<int>().swap(t.Machine_C);
	for (int g = Job.size() - 1; g >= 0; g--) 
	{
		t.Job_C.push_back(Job[g]);
	}
	for (int g = Operation.size() - 1; g >= 0; g--) 
	{
		t.Operation_C.push_back(Operation[g]);
	}
	for (int g = Machine.size() - 1; g >= 0; g--) 
	{
		t.Machine_C.push_back(Machine[g]);
	}
	//cout << "关键路径涉及的job索引号：" << endl;
	//for (int k = 0; k < t.Job_C.size(); k++)
	//{
	//	int job_index = t.Job_C[k] - 1;
	//	cout << job_index << " ";
	//}
	//cout << endl;
	//cout << "关键路径涉及的operation序号索引号和machine索引号：" << endl;
	//for (int k = 0; k < t.Operation_C.size(); k++)
	//{
	//	int operation_index = t.Operation_C[k] - 1;
	//	cout << operation_index << " ";
	//	int machine_index = t.Machine_C[k];
	//	cout << machine_index << endl;//机器索引号
	//	cout << "start：" << s_t[k] << " ";//验证
	//	cout << "finish：" << f_t[k] << endl;//验证
	//}
	//cout << endl;
	//system("pause");


	for (int i = 0; i < number_of_jobs2; i++)
	{
		delete[] p_operation_completion_time[i];
	}
	delete[] p_operation_completion_time;

	delete[] p_completion_time2;//释放new开辟的一维空间

	delete[] p_machine_cost;
}