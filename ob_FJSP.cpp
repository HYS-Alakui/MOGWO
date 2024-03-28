#include <iomanip>
#include "Genetic.h"
#include "Individual.h"
#include "random.h"
#include <cmath>

void CGenetic::evaluate_FJSP(CIndividual& t)//������Ӧ��
{
	//step1����ȡÿ�����������Ĵ��ӹ�����
	vector <vector<CChromosome>> v_factory_operation;
	for (int f = 0; f < 1; f++)
	{
		vector<CChromosome> v;
		v_factory_operation.push_back(v);
	}
	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	{
		int j_num = t.v_chromosome2[j].job_number;//�ҳ��ù��������job
		//cout << "j_num = " << j_num << endl;	
		int o_num = t.v_chromosome2[j].operation_index;//�ҳ��ù����ǵڼ�������
		//cout << "o_num = " << o_num << endl;
		int m_num_index = number_of_jobs2 * number_of_operations + (j_num - 1) * number_of_operations + o_num - 1;
		int m_num = t.v_chromosome2[m_num_index].machine_number;//�ҵ���job�ù������������
		//cout << "m_num = " << m_num << endl;

		CChromosome ttt;
		ttt.job_number = j_num;
		ttt.operation_index = o_num;
		ttt.machine_number = m_num;
		v_factory_operation[0].push_back(ttt);
	}
	//cout << "ÿ�����������Ĺ������Ϣ(�������У��������ţ����������Ļ���)��" << endl;
	//for (int f = 0; f < v_factory_operation.size(); f++)
	//{
	//	cout << "F" << f+1 << "---opera_seque_job��";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{		
	//		cout << v_factory_operation[f][n].job_number << " ";
	//	}
	//	cout << endl;
	//	cout << "F" << f+1 << "---operation_index��";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{
	//		cout << v_factory_operation[f][n].operation_index << " ";
	//	}
	//	cout << endl;
	//	cout << "F" << f+1 << "----machine_number��";
	//	for (int n = 0; n < v_factory_operation[f].size(); n++)
	//	{
	//		cout << v_factory_operation[f][n].machine_number << " ";
	//	}
	//	cout << endl <<endl;
	//}
	//cout << endl;
	//system("pause");

	//step2��ÿ���Ǳ�׼����ÿ������Ķ��Ƽӹ�ʱ��
	p_c_fjsp_processing_time = new int**[number_of_operations];//��һ������number_of_factories��Ԫ�ص�����1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_c_fjsp_processing_time[i] = new int*[number_of_machines];//����1�� ÿ��Ԫ�� ��ָ��һ�� ����number_of_machines��Ԫ�ص�����2
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


	//step3:��ÿ�������Ļ����ӹ��Ĺ����job�š���Ӧ�Ĺ���š�����Ŀ�ʼ���깤ʱ��
	double** p_operation_completion_time;
	p_operation_completion_time = new double*[number_of_jobs2];
	for (int j = 0; j < number_of_jobs2; j++)
	{
		p_operation_completion_time[j] = new double[number_of_operations];
	}
	for (int j = 0; j < number_of_jobs2; j++)//�Կ��ٵ���Ⱥ��ʼ��
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

	vector<vector<int> > M_J(number_of_machines); //�û����ӹ��Ĺ����Ӧ����ҵ���
	vector<vector<int> > M_O(number_of_machines);//�û����ӹ��Ĺ����Ӧ�ĵڼ�������
	vector<vector<double> > m_s_t(number_of_machines);//�û����ӹ���ÿ������Ŀ�ʼʱ��
	vector<vector<double> > m_f_t(number_of_machines);//�û����ӹ���ÿ��������깤ʱ��
	for (int i = 0; i < 1; i++)
	{
		for (int o = 0; o < v_factory_operation[i].size(); o++)
		{
			int machine_index = v_factory_operation[i][o].machine_number;//�ù������ڻ���
			int Job_index = v_factory_operation[i][o].job_number;//������ҵ��
			int Operation_index = v_factory_operation[i][o].operation_index;//��������ҵ�е�˳��
			if (Operation_index == 1)//����ҵ�ĵ�һ������
			{
				if (M_J[machine_index - 1].empty())//�û�����δ�й���
				{
					M_J[machine_index - 1].push_back(Job_index);
					M_O[machine_index - 1].push_back(Operation_index);
					m_s_t[machine_index - 1].push_back(max_design_value);
					m_f_t[machine_index - 1].push_back(max_design_value + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
				}
				else if (!M_J[machine_index - 1].empty())
				{//�û��������й���
					int successinsert = 0;//�Ƿ�����ȥ��
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
					if (successinsert != 1) //δ���룬�������
					{
						M_J[machine_index - 1].push_back(Job_index);
						M_O[machine_index - 1].push_back(Operation_index);
						m_s_t[machine_index - 1].push_back(m_f_t[machine_index - 1][m_f_t[machine_index - 1].size() - 1]);
						m_f_t[machine_index - 1].push_back(m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
					}
				}
			}
			//������ҵ�ĵ�һ������
			else if (Operation_index != 1)
			{
				//�ҵ��ù����ǰ����Ļ����ţ��洢ǰ�����������������ϵĽ���ʱ��
				int find_index = number_of_jobs2 *number_of_operations + (Job_index - 1) * number_of_operations + (Operation_index - 1) - 1;
				int mach = t.v_chromosome2[find_index].machine_number;//ǰ����Ļ�����
				//�ҵ��ù����ǰ�������俪ʼʱ�����ǰ������깤ʱ��
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

				if (M_J[machine_index - 1].empty()) //�û�����δ�й���		
				{
					m_s_t[machine_index - 1].push_back(finishtime);
					m_f_t[machine_index - 1].push_back(m_s_t[machine_index - 1][m_s_t[machine_index - 1].size() - 1] + p_c_fjsp_processing_time[Operation_index - 1][machine_index - 1][Job_index - 1]);
					M_J[machine_index - 1].push_back(Job_index);
					M_O[machine_index - 1].push_back(Operation_index);
				}
				else if (!M_J[machine_index - 1].empty()) //�û��������й���
				{
					int successinsert = 0;//�Ƿ�����ȥ��
					vector<double>Itime;//�û�����ÿ������֮��Ŀ���ʱ��
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
	//���������ÿ��job��ÿ�������ڲ�ͬ�����ϵ��깤ʱ��
	//cout << "ÿ̨�����ӹ��Ĺ����Ӧ����ҵ���" << endl;
	//for (int mj = 0; mj < M_J.size(); mj++)
	//{
	//	for (int mk = 0; mk < M_J[mj].size(); mk++)
	//	{
	//		cout << M_J[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "ÿ̨�����ӹ��Ĺ����Ӧ�Ĺ������" << endl;
	//for (int mj = 0; mj < M_O.size(); mj++)
	//{
	//	for (int mk = 0; mk < M_O[mj].size(); mk++)
	//	{
	//		cout << M_O[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "ÿ̨�����ӹ��Ĺ���Ŀ�ʼʱ��" << endl;
	//for (int mj = 0; mj < m_s_t.size(); mj++)
	//{
	//	for (int mk = 0; mk < m_s_t[mj].size(); mk++)
	//	{
	//		cout << m_s_t[mj][mk] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//cout << "ÿ̨�����ӹ��Ĺ���Ľ���ʱ��" << endl;//���������������ҵ���������깤ʱ��Ĺ������ڵĻ������Լ�λ�ú�
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

	////step4����ÿ��job��ÿ��������깤ʱ��
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
	
	////step5����ÿ��job�ĵ��깤ʱ��
	for (int w = 0; w < number_of_jobs2; w++)
	{
		p_completion_time2[w] = p_operation_completion_time[w][number_of_operations - 1];
		//cout << p_completion_time2[w] << endl;
	}

	/////step6����makespan
	int max_completion_time;
	max_completion_time = p_completion_time2[0];
	for (int i = 0; i < number_of_jobs2; i++)
	{
		if (max_completion_time < p_completion_time2[i])
		{
			max_completion_time = p_completion_time2[i];
		}
	}
	FJSP_makespan = max_completion_time;//��ȡ�ø����makespan
	//cout << "FJSP_makespan = " << FJSP_makespan <<endl;
	t.FJSP_makespan_value = FJSP_makespan;
	//system("pause");

	////step7:�������׶εĳɱ���ÿ̨�������е�λʱ��ӹ��ɱ����ʸû����ϵĳɱ�=�û����ӹ��Ĺ���ļӹ�ʱ�����λʱ��ӹ��ɱ����������л�������
	////����������Ҫ����һ�����飬����ÿ̨�����ļӹ��ɱ��Ի�ȡ�ؼ�����
	double* p_machine_cost = new double[number_of_machines];//����ÿ�������ļӹ��ɱ�
	for (int pp = 0; pp < number_of_machines; pp++)//��ʼ��
	{
		p_machine_cost[pp] = 0;
	}
	total_production_cost2 = 0;//Ŀ��1�ĵ�һ����
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
	
	/*********************************��ȡFJSP�ؼ�����***************************************************/
	int key_machine_idx = 0;
	double max_machine_cost_value = 0;
	//cout << "ÿ̨�����ĳɱ���" << endl;
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
	//cout << "FJSP�Ĺؼ����������ǣ�" << t.key_machine_index << endl;
	vector<int>().swap(t.Keymachine_Operation);
	vector<int>().swap(t.Keymachine_Operation_Xuhao);
	for (int qq = 0; qq < M_J[key_machine_idx].size(); qq++)
	{
		//cout << "�����ţ�" << M_J[key_machine_idx][qq] << " ";
		t.Keymachine_Operation.push_back(M_J[key_machine_idx][qq]);
		//cout << "������ţ�" << M_O[key_machine_idx][qq] << endl;
		t.Keymachine_Operation_Xuhao.push_back(M_O[key_machine_idx][qq]);
	}
	//for (int g = 0; g < t.Keymachine_Operation.size(); g++)
	//{
	//	cout << "�����ţ�" << t.Keymachine_Operation[g] << endl;
	//}
	//for (int g = 0; g < t.Keymachine_Operation_Xuhao.size(); g++)
	//{
	//	cout << "������ţ�" << t.Keymachine_Operation_Xuhao[g] << endl;
	//}
	//system("pause");

	/*********************************��ȡFJSP�ؼ�·��***************************************************/
	vector<int>Job;//�ؼ�·������ҵ��ţ�����
	vector<int>Operation;//�ؼ�·����ҵ�Ĺ����ţ�����
	vector<int>Machine;//�ؼ�·����ҵ�Ĺ������ڵĻ��������ţ�����
	vector<double>s_t;//�ؼ�·����ҵ�Ĺ���Ŀ�ʼʱ�䣨����
	vector<double>f_t;//�ؼ�·����ҵ�Ĺ���Ľ���ʱ�䣨����
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
			//��ȡ��ǰ��ҵǰ�滹�ж��ٵ�����,����ǰ��ҵ�����3 ��ô����ҵǰ����У�3-1��*number_of_operations������
			for (int r = 0; r < M_J[max_machine_index][max_position_index] - 1; r++)
			{
				Sum_number = Sum_number + number_of_operations;
			}
			//cout << "Sum_number =" << Sum_number << endl;
			//��ȡ��ǰ��ҵ�ؼ������ǰһ�����������Ļ������
			int MACHINE = t.v_chromosome2[number_of_jobs2 * number_of_operations + Sum_number + M_O[max_machine_index][max_position_index] - 1 - 1].machine_number;//��jobǰһ������Ļ������
			//cout << "MACHINE =" << MACHINE << endl;
			for (int q = 0; q < M_J[MACHINE - 1].size(); q++) //�����ؼ������ϵĹ���
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
			if (m_s_t[max_machine_index][max_position_index] == m_f_t[max_machine_index][max_position_index - 1])//���ؼ�����Ŀ�ʼʱ��==��λ��ǰһ��������깤ʱ��
			{
				//cout << "ͬһ����ǰ������������β����" << endl;
				max_position_index = max_position_index - 1;//���¹ؼ����򣺵�ǰ������ǰһ������
				//cout << "cccM_J[max_machine_index][max_position_index] - 1 =" << M_J[max_machine_index][max_position_index] - 1 << endl;
				Job.push_back(M_J[max_machine_index][max_position_index]);
				Operation.push_back(M_O[max_machine_index][max_position_index]);
				Machine.push_back(max_machine_index);
				s_t.push_back(m_s_t[max_machine_index][max_position_index]);
				f_t.push_back(m_f_t[max_machine_index][max_position_index]);
			}
			else if (m_s_t[max_machine_index][max_position_index] != m_f_t[max_machine_index][max_position_index - 1])//���ؼ�����Ŀ�ʼʱ�䣡=��λ��ǰһ��������깤ʱ��
			{
				//cout << "������,��ҪѰ�ҵ�ǰ�ؼ���������job����һ������" << endl;
				int break_1 = 0;
				int Sum_number = 0;
				for (int r = 0; r < M_J[max_machine_index][max_position_index] - 1; r++)
				{
					Sum_number = Sum_number + number_of_operations;
				}
				int MACHINE = t.v_chromosome2[number_of_jobs2 * number_of_operations + Sum_number + M_O[max_machine_index][max_position_index] - 1 -1].machine_number;//��һ�����������
				//cout << "��job��ǰһ���������ڻ������MACHINE =" << MACHINE << endl;
				for (int q = 0; q < M_J[MACHINE - 1].size(); q++) //������λ������
				{
					if (M_J[max_machine_index][max_position_index] == M_J[MACHINE - 1][q])
					{//��ҵ��ͬ
						if (M_O[max_machine_index][max_position_index] == M_O[MACHINE - 1][q] + 1)
						{//��ǰ����
							if (m_s_t[max_machine_index][max_position_index] == m_f_t[MACHINE - 1][q])
							{
								max_position_index = q;//���¹ؼ�����job����һ����������λ��
								//cout << "max_position_index = " << max_position_index << endl;
								max_machine_index = MACHINE - 1;//������-1
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

	//FJSP�ؼ�·��
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
	//cout << "�ؼ�·���漰��job�����ţ�" << endl;
	//for (int k = 0; k < t.Job_C.size(); k++)
	//{
	//	int job_index = t.Job_C[k] - 1;
	//	cout << job_index << " ";
	//}
	//cout << endl;
	//cout << "�ؼ�·���漰��operation��������ź�machine�����ţ�" << endl;
	//for (int k = 0; k < t.Operation_C.size(); k++)
	//{
	//	int operation_index = t.Operation_C[k] - 1;
	//	cout << operation_index << " ";
	//	int machine_index = t.Machine_C[k];
	//	cout << machine_index << endl;//����������
	//	cout << "start��" << s_t[k] << " ";//��֤
	//	cout << "finish��" << f_t[k] << endl;//��֤
	//}
	//cout << endl;
	//system("pause");


	for (int i = 0; i < number_of_jobs2; i++)
	{
		delete[] p_operation_completion_time[i];
	}
	delete[] p_operation_completion_time;

	delete[] p_completion_time2;//�ͷ�new���ٵ�һά�ռ�

	delete[] p_machine_cost;
}