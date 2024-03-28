#include "Genetic.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"

void CGenetic::LS2()
{
	//cout << "------------5���ֲ�����2---------" << endl;
	//���ڹؼ�·���ֲ������������Ⱥ���н�һ���������Ż��ڶ���Ŀ��
	vector <CIndividual>().swap(v_KLS2_individuals);
	vector <CIndividual>().swap(v_LS2_individuals);
	vector <CIndividual>().swap(v_LS2_individuals_temp);//�������
	vector <CIndividual> v_LS2_individuals(v_KLS_individuals);//�������죬�������ʹ��
	vector <CIndividual> v_LS2_individuals_temp(v_KLS_individuals);//�������죬�������ʹ��
	//cout << "��������ʱ����Ⱥ��" << endl;
	//for (int i = 0; i < v_LS2_individuals_temp.size(); i++)
	//{
	//	cout << "i = " << i << endl;
	//	for (int j = 0; j < number_of_jobs1; j++)
	//	{
	//		cout << v_LS2_individuals_temp[i].v_chromosome1[j].factory_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs1; j < v_LS2_individuals_temp[i].v_chromosome1.size(); j++)
	//	{
	//		cout << v_LS2_individuals_temp[i].v_chromosome1[j].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//	{
	//		cout << v_LS2_individuals_temp[i].v_chromosome2[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs2 * number_of_operations; j < v_LS2_individuals_temp[i].v_chromosome2.size(); j++)
	//	{
	//		cout << v_LS2_individuals_temp[i].v_chromosome2[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int k = 0; k < v_LS2_individuals_temp[i] .v_objective_value.size(); k++)
	//	{
	//		cout << v_LS2_individuals_temp[i].v_objective_value[k] << " ";
	//	}
	//	cout << endl;
	//	cout << "v_LS2_individuals_temp[i].key_cell = " << v_LS2_individuals_temp[i].key_cell << endl;
	//}
	////system("pause");


	for (int i = 0; i < v_LS2_individuals_temp.size(); i++)//�ҵ�ÿ��������FJSP�гɱ���ߵĻ�����Ȼ���ȡ�乤���б����ŶԹ�����и��������������ҳɱ���͵Ļ������ɱ� = �ӹ�ʱ�����λ�ɱ�
	{
		//cout << "i = " << i << endl;
		//cout << "Before:" << endl;
		//for (int n = 0; n < number_of_jobs1; n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome1[n].factory_number << " ";
		//}
		//cout << endl;
		//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome1[n].job_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome2[n].operation_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome2[n].job_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome2[n].operation_index << " ";
		//}
		//cout << endl;
		//for (int n = number_of_jobs2 * number_of_operations; n < v_LS2_individuals_temp[i].v_chromosome2.size(); n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome2[n].machine_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < v_LS2_individuals_temp[i].v_objective_value.size(); n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_objective_value[n] << " ";
		//}
		//cout << endl;
		//system("pause");
		////step1: �ҵ�ÿ��������FJSP�гɱ���ߵĻ�����Ȼ���ȡ�乤���б�
		int current_key_machine_index = v_LS2_individuals_temp[i].key_machine_index;
		//cout << "��ǰ������FJSP�Ĺؼ����������ǣ�" << current_key_machine_index << endl;
		//cout << "�û����漰�Ĺ����ź͹�����ţ�" << endl;
		//for (int j = 0; j < v_LS2_individuals_temp[i].Keymachine_Operation.size(); j++)
		//{
		//	cout << "�����ţ�" << v_LS2_individuals_temp[i].Keymachine_Operation[j] << " ";
		//	cout << "������ţ�" << v_LS2_individuals_temp[i].Keymachine_Operation_Xuhao[j] << endl;
		//}
		//system("pause");
		for (int pp = 0; pp < v_LS2_individuals_temp[i].Keymachine_Operation.size(); pp++)
		{			
			//////step2: ѡȡһ�����򣬶Թ�����ʹ�õĻ������и������ҳɱ����ӹ�ʱ�����λ�ɱ�����͵Ļ���
			//int rand_oper_num = v_LS2_individuals_temp[i].Keymachine_Operation[pp];
			////cout << "rand_oper_num = " << rand_oper_num << endl;
			//int rand_oper_xuhao = v_LS2_individuals_temp[i].Keymachine_Operation_Xuhao[pp];
			////cout << "rand_oper_xuhao =" << rand_oper_xuhao << endl;
			////system("pause");
			//double rand_no_value = rand() / (RAND_MAX * 1.0);
			//cout << "rand_no_value =" << rand_no_value << endl;
			//if (rand_no_value <= 0.1)
			//{
			//	//step2.1: ��ȡ��job�ĸõ�����Ŀ�ʹ�û�������
			//	int operation_machine_size = v_available_machines[rand_oper_num - 1][rand_oper_xuhao - 1].size();
			//	//cout << "operation_machine_size = " << operation_machine_size << endl;
			//	//������Щ�������Ҽӹ��ɱ���͵Ļ���
			//	vector<double> v_machine_cost;
			//	for (int j = 0; j < operation_machine_size; j++)
			//	{
			//		int now_machine_no = v_available_machines[rand_oper_num - 1][rand_oper_xuhao - 1][j];
			//		//cout << "now_machine_no =" << now_machine_no << endl;
			//		double now_machine_cost = p_c_fjsp_processing_time[rand_oper_xuhao - 1][now_machine_no - 1][rand_oper_num - 1] * (p_unit_machine_cost2[now_machine_no - 1] / 10);
			//		//cout << "now_machine_cost =" << now_machine_cost << endl;
			//		v_machine_cost.push_back(now_machine_cost);
			//	}
			//	double min_machine_cost = v_machine_cost[0];
			//	int min_machine_cost_pos = 0;
			//	for (int j = 0; j < v_machine_cost.size(); j++)
			//	{
			//		//cout << v_machine_cost[j] << " ";
			//		if (v_machine_cost[j] < min_machine_cost)
			//		{
			//			min_machine_cost = v_machine_cost[j];
			//			min_machine_cost_pos = j;
			//		}
			//	}
			//	//cout << "min_machine_cost =" << min_machine_cost << endl;
			//	//cout << "min_machine_cost_pos =" << min_machine_cost_pos << endl;
			//	int best_machine_number = v_available_machines[rand_oper_num - 1][rand_oper_xuhao - 1][min_machine_cost_pos];
			//	//cout << "best_machine_number = " << best_machine_number << endl;		
			//	//step2.2: ��ȡ��job�ĸõ�������ʹ�õĻ������ɳɱ���С�Ļ���
			//	int index = (rand_oper_num - 1) * number_of_operations + number_of_jobs2 * number_of_operations + (rand_oper_xuhao - 1);
			//	//cout << "index = " << index << endl;
			//	v_LS2_individuals_temp[i].v_chromosome2[index].machine_number = best_machine_number;
			//}

			////step2: ���ѡȡһ�����򣬶Թ�����ʹ�õĻ������и������ҳɱ����ӹ�ʱ�����λ�ɱ�����͵Ļ���
			int rand_oper_pos = rand() % v_LS2_individuals_temp[i].Keymachine_Operation.size();
			//cout << "rand_oper_pos = " << rand_oper_pos << endl;
			int rand_oper_num = v_LS2_individuals_temp[i].Keymachine_Operation[rand_oper_pos];
			//cout << "rand_oper_num = " << rand_oper_num << endl;
			int rand_oper_xuhao = v_LS2_individuals_temp[i].Keymachine_Operation_Xuhao[rand_oper_pos];
			//cout << "rand_oper_xuhao =" << rand_oper_xuhao << endl;
			//system("pause");
			//step2.1: ��ȡ��job�ĸõ�����Ŀ�ʹ�û�������
			int operation_machine_size = v_available_machines[rand_oper_num - 1][rand_oper_xuhao - 1].size();
			//cout << "operation_machine_size = " << operation_machine_size << endl;
			if (operation_machine_size >= 2)
			{
				//������Щ�������Ҽӹ��ɱ���͵Ļ���
				vector<double> v_machine_cost;
				for (int j = 0; j < operation_machine_size; j++)
				{
					int now_machine_no = v_available_machines[rand_oper_num - 1][rand_oper_xuhao - 1][j];
					//cout << "now_machine_no =" << now_machine_no << endl;
					double now_machine_cost = p_c_fjsp_processing_time[rand_oper_xuhao - 1][now_machine_no - 1][rand_oper_num - 1] * p_unit_machine_cost2[now_machine_no - 1];
					//cout << "now_machine_cost =" << now_machine_cost << endl;
					v_machine_cost.push_back(now_machine_cost);
				}
				double min_machine_cost = v_machine_cost[0];
				int min_machine_cost_pos = 0;
				for (int j = 0; j < v_machine_cost.size(); j++)
				{
					//cout << v_machine_cost[j] << " ";
					if (v_machine_cost[j] < min_machine_cost)
					{
						min_machine_cost = v_machine_cost[j];
						min_machine_cost_pos = j;
					}
				}
				//cout << "min_machine_cost =" << min_machine_cost << endl;
				//cout << "min_machine_cost_pos =" << min_machine_cost_pos << endl;
				int best_machine_number = v_available_machines[rand_oper_num - 1][rand_oper_xuhao - 1][min_machine_cost_pos];
				//cout << "best_machine_number = " << best_machine_number << endl;		
				//step2.2: ��ȡ��job�ĸõ�������ʹ�õĻ������ɳɱ���С�Ļ���
				int index = (rand_oper_num - 1) * number_of_operations + number_of_jobs2 * number_of_operations + (rand_oper_xuhao - 1);
				//cout << "index = " << index << endl;
				v_LS2_individuals_temp[i].v_chromosome2[index].machine_number = best_machine_number;
				//system("pause");
			}
		}

		//step2.3: ���½�������
		assign(v_LS2_individuals_temp[i]);
		evaluate_DFSP(v_LS2_individuals_temp[i]);
		evaluate_FJSP(v_LS2_individuals_temp[i]);
		evaluate(v_LS2_individuals_temp[i]);
		//cout << "After:" << endl;
		//for (int n = 0; n < number_of_jobs1; n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome1[n].factory_number << " ";
		//}
		//cout << endl;
		//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome1[n].job_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome2[n].operation_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome2[n].job_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome2[n].operation_index << " ";
		//}
		//cout << endl;
		//for (int n = number_of_jobs2 * number_of_operations; n < v_LS2_individuals_temp[i].v_chromosome2.size(); n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_chromosome2[n].machine_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < v_LS2_individuals_temp[i].v_objective_value.size(); n++)
		//{
		//	cout << v_LS2_individuals_temp[i].v_objective_value[n] << " ";
		//}
		//cout << endl;
		//system("pause");
		////step3: �Ƚ�LSǰ��ĸ��壬�����õ�
		int domRel = 3;
		domRelation(v_LS2_individuals[i], v_LS2_individuals_temp[i], domRel);
		if (domRel == 1)//�Ӵ�1֧���Ӵ�2
		{
			v_KLS2_individuals.push_back(v_LS2_individuals[i]);//���Ӵ�1 β�� �� �Ӵ���Ⱥ��	
		}
		else
		{
			v_KLS2_individuals.push_back(v_LS2_individuals_temp[i]);//���Ӵ�2 β�� �� �Ӵ���Ⱥ��		
		}

		//if (v_LS2_individuals[i].v_objective_value[1] < v_LS2_individuals_temp[i].v_objective_value[1])//�Ӵ�1֧���Ӵ�2
		//{
		//	v_KLS2_individuals.push_back(v_LS2_individuals[i]);//���Ӵ�1 β�� �� �Ӵ���Ⱥ��	
		//}
		//else
		//{
		//	v_KLS2_individuals.push_back(v_LS2_individuals_temp[i]);//���Ӵ�2 β�� �� �Ӵ���Ⱥ��		
		//}

		//cout << "��KLS2�����������Ӵ���" << endl;
		//for (int j = 0; j < number_of_jobs1; j++)
		//{
		//	cout << v_KLS2_individuals[i].v_chromosome1[j].factory_number << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs1; j < v_KLS2_individuals[i].v_chromosome1.size(); j++)
		//{
		//	cout << v_KLS2_individuals[i].v_chromosome1[j].job_number << " ";
		//}
		//cout << endl;
		//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
		//{
		//	cout << v_KLS2_individuals[i].v_chromosome2[j].operation_number << " ";
		//}
		//cout << endl;
		//for (int j = number_of_jobs2 * number_of_operations; j < v_KLS2_individuals[i].v_chromosome2.size(); j++)
		//{
		//	cout << v_KLS2_individuals[i].v_chromosome2[j].machine_number << " ";
		//}
		//cout << endl;
		//for (int j = 0; j < v_KLS2_individuals[i].v_objective_value.size(); j++)
		//{
		//	cout << v_KLS2_individuals[i].v_objective_value[j] << " ";
		//}
		//cout << endl;
		//system("pause");
	}
	//cout << "KLS2��Ⱥ��" << endl;
	//for (int i = 0; i < v_KLS2_individuals.size(); i++)
	//{
	//	cout << "i = " << i << endl;
	//	for (int j = 0; j < number_of_jobs1; j++)
	//	{
	//		cout << v_KLS2_individuals[i].v_chromosome1[j].factory_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs1; j < v_KLS2_individuals[i].v_chromosome1.size(); j++)
	//	{
	//		cout << v_KLS2_individuals[i].v_chromosome1[j].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//	{
	//		cout << v_KLS2_individuals[i].v_chromosome2[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs2 * number_of_operations; j < v_KLS2_individuals[i].v_chromosome2.size(); j++)
	//	{
	//		cout << v_KLS2_individuals[i].v_chromosome2[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < v_KLS2_individuals[i].v_objective_value.size(); j++)
	//	{
	//		cout << v_KLS2_individuals[i].v_objective_value[j] << " ";
	//	}
	//	cout << endl;
	//}
	//system("pause");
}