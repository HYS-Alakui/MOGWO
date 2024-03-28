#include "Genetic.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"

void CGenetic::LS()
{
	//cout << "------------5���ֲ�����---------" << endl;
	//�Ծ�������ͱ���׶ε�����Ⱥ�еĸ�����л��ڹؼ�·���ľֲ�����
	vector <CIndividual>().swap(v_KLS_individuals);
	vector <CIndividual>().swap(v_new_individuals_temp);//�������
	vector <CIndividual> v_new_individuals_temp(v_new_individuals);//�������죬�������ʹ��
	//cout << "��������ʱ����Ⱥ��" << endl;
	//for (int i = 0; i < v_new_individuals_temp.size(); i++)
	//{
	//	cout << "i = " << i << endl;
	//	for (int j = 0; j < number_of_jobs1; j++)
	//	{
	//		cout << v_new_individuals_temp[i].v_chromosome1[j].factory_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs1; j < v_new_individuals_temp[i].v_chromosome1.size(); j++)
	//	{
	//		cout << v_new_individuals_temp[i].v_chromosome1[j].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//	{
	//		cout << v_new_individuals_temp[i].v_chromosome2[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs2 * number_of_operations; j < v_new_individuals_temp[i].v_chromosome2.size(); j++)
	//	{
	//		cout << v_new_individuals_temp[i].v_chromosome2[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int k = 0; k < v_new_individuals_temp[i] .v_objective_value.size(); k++)
	//	{
	//		cout << v_new_individuals_temp[i].v_objective_value[k] << " ";
	//	}
	//	cout << endl;
	//	cout << "v_new_individuals_temp[i].key_cell = " << v_new_individuals_temp[i].key_cell << endl;
	//}
	//system("pause");

	for (int i = 0; i < v_new_individuals_temp.size(); i++)//�������Ⱥ�е�ÿ������ִ�л���֪ʶ����������
	{
		//cout << "i = " << i << endl;
		//cout << "v_new_individuals_temp[i].key_cell = " << v_new_individuals_temp[i].key_cell << endl;
		if (v_new_individuals_temp[i].key_cell == 0)
		{
			//cout << "DFSP�ؼ�·���漰��job_index��machine_index��" << endl;
			//for (int k = 0; k < v_new_individuals_temp[i].critical_path_operation.size(); k++)
			//{
			//	int job_index = v_new_individuals_temp[i].critical_path_operation[k] - 1;
			//	cout << job_index << " ";
			//	int machine_index = v_new_individuals_temp[i].critical_path_machine[k] - 1;
			//	cout << machine_index << endl;//����������
			//}
			//cout << endl;
			//system("pause");

			CIndividual Older, New;
			Older = v_new_individuals_temp[i];
			assign(Older);
			evaluate_DFSP(Older);
			evaluate_FJSP(Older);
			evaluate(Older);
			New = Older;
			generate_newindividual1(Older, New);//���������generate_newindividual����

			////�Ƚ�older��new�����ӣ�ѡ��õĽ���LS��Ⱥ	
			assign(New);
			evaluate_DFSP(New);
			evaluate_FJSP(New);
			evaluate(New);
			//cout << "New����Ϣ" << endl;
			//for (int j = 0; j < number_of_jobs1; j++)
			//{
			//	cout << New.v_chromosome1[j].factory_number << " ";
			//}
			//cout << endl;
			//for (int j = number_of_jobs1; j < New.v_chromosome1.size(); j++)
			//{
			//	cout << New.v_chromosome1[j].job_number << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
			//{
			//	cout << New.v_chromosome2[j].operation_number << " ";
			//}
			//cout << endl;
			//for (int j = number_of_jobs2 * number_of_operations; j < New.v_chromosome2.size(); j++)
			//{
			//	cout << New.v_chromosome2[j].machine_number << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < New.v_objective_value.size(); j++)
			//{
			//	cout << New.v_objective_value[j] << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < New.critical_path_operation.size(); j++)
			//{
			//	int job_index = New.critical_path_operation[j] - 1;
			//	cout << job_index << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < New.critical_path_machine.size(); j++)
			//{
			//	int machine_index = New.critical_path_machine[j] - 1;
			//	cout << machine_index << " ";
			//}
			//cout << endl;
			//system("pause");

			int domRel = 3;
			domRelation(Older, New, domRel);
			//cout << "domRel = " << domRel << endl;
			if (domRel == 1)//�Ӵ�1֧���Ӵ�2
			{
				v_KLS_individuals.push_back(Older);//���Ӵ�1 β�� �� �Ӵ���Ⱥ��	
			}
			else
			{
				v_KLS_individuals.push_back(New);//���Ӵ�2 β�� �� �Ӵ���Ⱥ��		
			}			
			//cout << "��KLS�����������Ӵ���" << endl;
			//for (int j = 0; j < number_of_jobs1; j++)
			//{
			//	cout << v_KLS_individuals[i].v_chromosome1[j].factory_number << " ";
			//}
			//cout << endl;
			//for (int j = number_of_jobs1; j < v_KLS_individuals[i].v_chromosome1.size(); j++)
			//{
			//	cout << v_KLS_individuals[i].v_chromosome1[j].job_number << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
			//{
			//	cout << v_KLS_individuals[i].v_chromosome2[j].operation_number << " ";
			//}
			//cout << endl;
			//for (int j = number_of_jobs2 * number_of_operations; j < v_KLS_individuals[i].v_chromosome2.size(); j++)
			//{
			//	cout << v_KLS_individuals[i].v_chromosome2[j].machine_number << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < v_KLS_individuals[i].v_objective_value.size(); j++)
			//{
			//	cout << v_KLS_individuals[i].v_objective_value[j] << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < v_KLS_individuals[i].critical_path_operation.size(); j++)
			//{
			//	int job_index = v_KLS_individuals[i].critical_path_operation[j] - 1;
			//	cout << job_index << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < v_KLS_individuals[i].critical_path_machine.size(); j++)
			//{
			//	int machine_index = v_KLS_individuals[i].critical_path_machine[j] - 1;
			//	cout << machine_index << " ";
			//}
			//cout << endl;
			//system("pause");
		}
		else
		{
			//cout << "�ؼ�·���漰��job�����ţ�" << endl;
			//for (int k = 0; k < v_new_individuals_temp[i].Job_C.size(); k++)
			//{
			//	int job_index = v_new_individuals_temp[i].Job_C[k] - 1;
			//	cout << job_index << " ";
			//}
			//cout << endl;
			//cout << "�ؼ�·���漰��operation��������ţ�" << endl;
			//for (int k = 0; k < v_new_individuals_temp[i].Operation_C.size(); k++)
			//{
			//	int operation_index = v_new_individuals_temp[i].Operation_C[k] - 1;
			//	cout << operation_index << " ";
			//}
			//cout << endl;
			//cout << "�ؼ�·���漰��machine�����ţ�" << endl;
			//for (int k = 0; k < v_new_individuals_temp[i].Operation_C.size(); k++)
			//{
			//	int machine_index = v_new_individuals_temp[i].Machine_C[k];
			//	cout << machine_index << " ";//����������
			//}
			//cout << endl;
			//system("pause");

			CIndividual Older, New;
			Older = v_new_individuals_temp[i];
			assign(Older);
			evaluate_DFSP(Older);
			evaluate_FJSP(Older);
			evaluate(Older);
			New = Older;
			generate_newindividual2(Older, New);//���������generate_newindividual����

			////�Ƚ�older��new�����ӣ�ѡ��õĽ���LS��Ⱥ	
			assign(New);
			evaluate_DFSP(New);
			evaluate_FJSP(New);
			evaluate(New);
			//cout << "New����Ϣ" << endl;
			//for (int j = 0; j < number_of_jobs1; j++)
			//{
			//	cout << New.v_chromosome1[j].factory_number << " ";
			//}
			//cout << endl;
			//for (int j = number_of_jobs1; j < New.v_chromosome1.size(); j++)
			//{
			//	cout << New.v_chromosome1[j].job_number << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
			//{
			//	cout << New.v_chromosome2[j].operation_number << " ";
			//}
			//cout << endl;
			//for (int j = number_of_jobs2 * number_of_operations; j < New.v_chromosome2.size(); j++)
			//{
			//	cout << New.v_chromosome2[j].machine_number << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < New.v_objective_value.size(); j++)
			//{
			//	cout << New.v_objective_value[j] << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < New.Job_C.size(); j++)
			//{
			//	int job_n = New.Job_C[j];
			//	cout << job_n << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < New.Operation_C.size(); j++)
			//{
			//	int operation_n = New.Operation_C[j];
			//	cout << operation_n << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < New.Operation_C.size(); j++)
			//{
			//	int machine_n = New.Machine_C[j] + 1;
			//	cout << machine_n << " ";
			//}
			//cout << endl;
			//system("pause");

			int domRel = 3;
			domRelation(Older, New, domRel);
			if (domRel == 1)//�Ӵ�1֧���Ӵ�2
			{
				v_KLS_individuals.push_back(Older);//���Ӵ�1 β�� �� �Ӵ���Ⱥ��	
			}
			else
			{
				v_KLS_individuals.push_back(New);//���Ӵ�2 β�� �� �Ӵ���Ⱥ��		
			}
			//cout << "��KLS�����������Ӵ���" << endl;
			//for (int j = 0; j < number_of_jobs1; j++)
			//{
			//	cout << v_KLS_individuals[i].v_chromosome1[j].factory_number << " ";
			//}
			//cout << endl;
			//for (int j = number_of_jobs1; j < v_KLS_individuals[i].v_chromosome1.size(); j++)
			//{
			//	cout << v_KLS_individuals[i].v_chromosome1[j].job_number << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
			//{
			//	cout << v_KLS_individuals[i].v_chromosome2[j].operation_number << " ";
			//}
			//cout << endl;
			//for (int j = number_of_jobs2 * number_of_operations; j < v_KLS_individuals[i].v_chromosome2.size(); j++)
			//{
			//	cout << v_KLS_individuals[i].v_chromosome2[j].machine_number << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < v_KLS_individuals[i].v_objective_value.size(); j++)
			//{
			//	cout << v_KLS_individuals[i].v_objective_value[j] << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < v_KLS_individuals[i].Job_C.size(); j++)
			//{
			//	cout << v_KLS_individuals[i].Job_C[j] << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < v_KLS_individuals[i].Operation_C.size(); j++)
			//{
			//	cout << v_KLS_individuals[i].Operation_C[j] << " ";
			//}
			//cout << endl;
			//for (int j = 0; j < v_KLS_individuals[i].Machine_C.size(); j++)
			//{
			//	cout << v_KLS_individuals[i].Machine_C[j] + 1 << " ";
			//}
			//cout << endl;
		}
		//system("pause");
	}
	//cout<<"KLS1��Ⱥ"<<endl;
	//for (int i = 0; i < v_KLS_individuals.size(); i++)
	//{
	//	cout << "i = " << i << endl;
	//	for (int j = 0; j < number_of_jobs1; j++)
	//	{
	//		cout << v_KLS_individuals[i].v_chromosome1[j].factory_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs1; j < v_KLS_individuals[i].v_chromosome1.size(); j++)
	//	{
	//		cout << v_KLS_individuals[i].v_chromosome1[j].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//	{
	//		cout << v_KLS_individuals[i].v_chromosome2[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs2 * number_of_operations; j < v_KLS_individuals[i].v_chromosome2.size(); j++)
	//	{
	//		cout << v_KLS_individuals[i].v_chromosome2[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int k = 0; k < v_KLS_individuals[i] .v_objective_value.size(); k++)
	//	{
	//		cout << v_KLS_individuals[i].v_objective_value[k] << " ";
	//	}
	//	cout << endl;
	//	cout << "v_KLS_individuals[i].key_cell = " << v_KLS_individuals[i].key_cell << endl;
	//}
	//system("pause");
}

void CGenetic::generate_newindividual1(CIndividual& Older, CIndividual& New)
{
	//cout << "Older����Ϣ" << endl;
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	cout << Older.v_chromosome1[j].factory_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs1; j < Older.v_chromosome1.size(); j++)
	//{
	//	cout << Older.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//{
	//	cout << Older.v_chromosome2[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < Older.v_chromosome2.size(); j++)
	//{
	//	cout << Older.v_chromosome2[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < Older.v_objective_value.size(); j++)
	//{
	//	cout << Older.v_objective_value[j] << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < Older.critical_path_operation.size(); j++)
	//{
	//	int job_index = Older.critical_path_operation[j] - 1;
	//	cout << job_index << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < Older.critical_path_machine.size(); j++)
	//{
	//	int machine_index = Older.critical_path_machine[j] - 1;
	//	cout <<machine_index << " ";
	//}
	//cout << endl;
	//system("pause");
 
	////step1:��ȡ�ø���Ĺؼ�job�ͷǹؼ�job
	vector<int> key_jobs;
	vector<int> unkey_jobs;
	bool pd_value;
	pd_value = true;
	int k_f_index = Older.key_factory_index;
	//cout << "k_f_index = " << k_f_index << endl;
	for (int j = 0; j < number_of_jobs1; j++)
	{
		int current_job_number = j + 1;
		for (int k = 0; k < Older.critical_path_operation.size(); k++)
		{
			int now_job_number = Older.critical_path_operation[k];
			if (current_job_number == now_job_number)
			{
				pd_value = true;
				break;
			}
			else
			{
				pd_value = false;
			}
		}
		if (pd_value == false)
		{
			unkey_jobs.push_back(current_job_number);
		}
	}
	//cout << "unkey_jobs:" << endl;
	//for (int j = 0; j < unkey_jobs.size(); j++)
	//{
	//	cout << unkey_jobs[j] << " ";
	//}
	//cout << endl;
	for (int j = 0; j < number_of_jobs1; j++)
	{
		int current_job_number = j + 1;
		for (int k = 0; k < unkey_jobs.size(); k++)
		{
			int now_job_number = unkey_jobs[k];
			if (current_job_number == now_job_number)
			{
				pd_value = true;
				break;
			}
			else
			{
				pd_value = false;
			}
		}
		if (pd_value == false)
		{
			key_jobs.push_back(current_job_number);
		}
	}
	//cout << "key_jobs:" << endl;
	//for (int j = 0; j < key_jobs.size(); j++)
	//{
	//	cout << key_jobs[j] << " ";
	//}
	//cout << endl;
	////step2:ִ����������ṹ
	//Case1:���ѡ�������ؼ�job��Ȼ������ҵ�����ϻ�������job��������������
	//Case2:���ѡ�������ؼ�job��Ȼ��ѿ����job���뿿ǰ��job��ǰ�棬������������
	//Case3:���ѡ��һ���ؼ�job��һ���ǹؼ�job��Ȼ������ҵ�����ϻ�������job,��������ҲҪ�仯
	//Case4:���ѡ��һ���ؼ�job��Ȼ��������Ĺ�����š�
	int rand_select_number = (rand() % 4) + 1;
	//cout << "rand_select_number = " << rand_select_number << endl;
	if (rand_select_number == 1)
	{
		//cout << "ִ��Case1" << endl;
		int ls_size = key_jobs.size();
		//cout << "ls_size = " << ls_size << endl;
		if (ls_size >= 2)
		{
			//���ѡ�������ؼ�job
			int ls1 = rand() % ls_size;
			int ls2 = rand() % ls_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % ls_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			//cout << "ls1 = " << ls1 << endl;
			//cout << "ls2= " << ls2 << endl;
			int ls_job1, ls_job2;
			ls_job1 = key_jobs[ls1];
			ls_job2 = key_jobs[ls2];
			//cout << "ls_job1 = " << ls_job1 << endl;
			//cout << "ls_job2 = " << ls_job2 << endl;

			//�ҳ�Ⱦɫ������������ҵ��λ������
			int ls_index1, ls_index2;
			for (int jj = number_of_jobs1; jj < 2 * number_of_jobs1; jj++)
			{
				if (Older.v_chromosome1[jj].job_number == ls_job1)
				{
					ls_index1 = jj;
					break;
				}
			}
			for (int jj = number_of_jobs1; jj < 2 * number_of_jobs1; jj++)
			{
				if (Older.v_chromosome1[jj].job_number == ls_job2)
				{
					ls_index2 = jj;
					break;
				}
			}
			//cout << "ls_index1 = " << ls_index1 << endl;
			//cout << "ls_index2 = " << ls_index2 << endl;

			//����������ҵ����ҵ�����е�λ��
			int ls_temp = New.v_chromosome1[ls_index1].job_number;
			New.v_chromosome1[ls_index1].job_number = New.v_chromosome1[ls_index2].job_number;
			New.v_chromosome1[ls_index2].job_number = ls_temp;
			////���LS���Ⱦɫ������
			//for (int n = 0; n < number_of_jobs1; n++)
			//{
			//	cout << New.v_chromosome1[n].factory_number << " ";
			//}
			//cout << endl;
			//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
			//{
			//	cout << New.v_chromosome1[n].job_number << " ";
			//}
			//cout << endl << endl;
		}
	}
	else if (rand_select_number == 2)
	{
		//cout << "ִ��Case2" << endl;
		int ls_size = key_jobs.size();
		//cout << "ls_size = " << ls_size << endl;
		if (ls_size >= 2)
		{
			//���ѡ�������ؼ�job
			int ls1 = rand() % ls_size;
			int ls2 = rand() % ls_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % ls_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			//cout << "ls1 = " << ls1 << endl;
			//cout << "ls2= " << ls2 << endl;
			int ls_job1, ls_job2;
			ls_job1 = key_jobs[ls1];
			ls_job2 = key_jobs[ls2];
			//cout << "ls_job1 = " << ls_job1 << endl;
			//cout << "ls_job2 = " << ls_job2 << endl;

			//�ҳ�Ⱦɫ������������ҵ��λ������
			int ls_index1, ls_index2;
			for (int jj = number_of_jobs1; jj < 2 * number_of_jobs1; jj++)
			{
				if (Older.v_chromosome1[jj].job_number == ls_job1)
				{
					ls_index1 = jj;
					break;
				}
			}
			for (int jj = number_of_jobs1; jj < 2 * number_of_jobs1; jj++)
			{
				if (Older.v_chromosome1[jj].job_number == ls_job2)
				{
					ls_index2 = jj;
					break;
				}
			}
			//cout << "ls_index1 = " << ls_index1 << endl;
			//cout << "ls_index2 = " << ls_index2 << endl;

			//��ѡ�еĿ���һ���job��Ⱦɫ����ɾ��
			New.v_chromosome1.erase(New.v_chromosome1.begin() + ls_index2);
			int current_size = New.v_chromosome1.size();
			//cout << "current_size = " << current_size << endl;
			//Ȼ���ٰ������뵽��ǰһ���job��ǰ��λ��
			CChromosome ttt;
			ttt.job_number = ls_job2;
			New.v_chromosome1.insert(New.v_chromosome1.begin() + ls_index1, ttt);
			current_size = New.v_chromosome1.size();
			//cout << "current_size = " << current_size << endl;
			//���LS���Ⱦɫ������
			//for (int n = 0; n < number_of_jobs1; n++)
			//{
			//	cout << New.v_chromosome1[n].factory_number << " ";
			//}
			//cout << endl;
			//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
			//{
			//	cout << New.v_chromosome1[n].job_number << " ";
			//}
			//cout << endl << endl;
		}

	}
	else if (rand_select_number == 3)
	{
		//cout << "ִ��Case3" << endl;
		int ls_size1 = key_jobs.size();
		//cout << "ls_size1 = " << ls_size1 << endl;
		//���ѡ��1���ؼ�job
		int ls1 = rand() % ls_size1;
		//cout << "ls1 = " << ls1 << endl;
		int ls_job1;
		ls_job1 = key_jobs[ls1];
		//cout << "ls_job1 = " << ls_job1 << endl;
		//���ѡ��1���ǹؼ�job
		int ls_size2 = unkey_jobs.size();
		//cout << "ls_size2 = " << ls_size2 << endl;
		int ls2 = rand() % ls_size2;
		//cout << "ls2 = " << ls2 << endl;
		int ls_job2;
		ls_job2 = unkey_jobs[ls2];
		//cout << "ls_job2 = " << ls_job2 << endl;
		//�ҳ�Ⱦɫ������������ҵ��λ������
		int ls_index1, ls_index2;
		for (int jj = number_of_jobs1; jj < 2 * number_of_jobs1; jj++)
		{
			if (Older.v_chromosome1[jj].job_number == ls_job1)
			{
				ls_index1 = jj;
				break;
			}
		}
		for (int jj = number_of_jobs1; jj < 2 * number_of_jobs1; jj++)
		{
			if (Older.v_chromosome1[jj].job_number == ls_job2)
			{
				ls_index2 = jj;
				break;
			}
		}
		//cout << "ls_index1 = " << ls_index1 << endl;
		//cout << "ls_index2 = " << ls_index2 << endl;

		//����������ҵ����ҵ�����е�λ��
		int ls_temp = New.v_chromosome1[ls_index1].job_number;
		New.v_chromosome1[ls_index1].job_number = New.v_chromosome1[ls_index2].job_number;
		New.v_chromosome1[ls_index2].job_number = ls_temp;
		int ls_temp2 = New.v_chromosome1[ls_job1 - 1].factory_number;
		New.v_chromosome1[ls_job1 - 1].factory_number = New.v_chromosome1[ls_job2 - 1].factory_number;
		New.v_chromosome1[ls_job2 - 1].factory_number = ls_temp2;
		////���LS���Ⱦɫ������
		//for (int n = 0; n < number_of_jobs1; n++)
		//{
		//	cout << New.v_chromosome1[n].factory_number << " ";
		//}
		//cout << endl;
		//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
		//{
		//	cout << New.v_chromosome1[n].job_number << " ";
		//}
		//cout << endl << endl;
	}
	else
	{
		//cout << "ִ��Case4" << endl;
		int ls_size = key_jobs.size();
		//cout << "ls_size = " << ls_size << endl;
		//���ѡ��1���ؼ�job
		int ls = rand() % ls_size;
		//cout << "ls = " << ls << endl;
		int ls_job;
		ls_job = key_jobs[ls];
		//cout << "ls_job = " << ls_job << endl;
		//������job�Ĺ�������
		int ls_factory_number = (rand() % number_of_factories) + 1;
		while ((ls_factory_number - 1) == Older.key_factory_index)
		{
			ls_factory_number = (rand() % number_of_factories) + 1;
		}
		//cout << "ls_factory_number = " << ls_factory_number << endl;	
		New.v_chromosome1[ls_job - 1].factory_number = ls_factory_number;//����������	
		////���LS���Ⱦɫ������
		//for (int n = 0; n < number_of_jobs1; n++)
		//{
		//	cout << New.v_chromosome1[n].factory_number << " ";
		//}
		//cout << endl;
		//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
		//{
		//	cout << New.v_chromosome1[n].job_number << " ";
		//}
		//cout << endl << endl;
	}
}

void CGenetic::generate_newindividual2(CIndividual& Older, CIndividual& New)
{
	//cout << "Older����Ϣ" << endl;
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	cout << Older.v_chromosome1[j].factory_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs1; j < Older.v_chromosome1.size(); j++)
	//{
	//	cout << Older.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//{
	//	cout << Older.v_chromosome2[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < Older.v_chromosome2.size(); j++)
	//{
	//	cout << Older.v_chromosome2[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < Older.v_objective_value.size(); j++)
	//{
	//	cout << Older.v_objective_value[j] << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < Older.Job_C.size(); j++)//job���
	//{
	//	int job_n = Older.Job_C[j];
	//	cout << job_n << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < Older.Operation_C.size(); j++)//operation���
	//{
	//	int operation_n = Older.Operation_C[j];
	//	cout << operation_n << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < Older.Operation_C.size(); j++)//machine���
	//{
	//	int machine_n = Older.Machine_C[j] + 1;
	//	cout << machine_n << " ";
	//}
	//cout << endl;
	//system("pause");
	////step2:ִ����������ṹ
	//Case1:�ı乤�����еļӹ�˳�����ѡ�������ؼ�operation��Ȼ����н�����������������
	//Case2:�ı乤�����еļӹ�˳�����ѡ�������ؼ�operation��Ȼ��ѿ����operation���뿿ǰ��operation��ǰ�棬������������
	//Case3:�ı�������䣬���ѡ��һ���ؼ�operation��Ȼ��������Ļ������
	int rand_select_number = (rand() % 3) + 1;
	//cout << "rand_select_number = " << rand_select_number << endl;
	if (rand_select_number == 1)
	{
		//cout << "ִ��Case1" << endl;
		int ls_size = Older.Job_C.size();
		//cout << "ls_size = " << ls_size << endl;
		if (ls_size >= 2)
		{
			//���ѡ�������ؼ�job
			int ls1 = rand() % ls_size;
			int ls2 = rand() % ls_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % ls_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			//cout << "ls1 = " << ls1 << endl;
			//cout << "ls2= " << ls2 << endl;
			int ls_job1, ls_job2;
			ls_job1 = Older.Job_C[ls1];
			ls_job2 = Older.Job_C[ls2];
			//cout << "ls_job1 = " << ls_job1 << endl;
			//cout << "ls_job2 = " << ls_job2 << endl;

			int ls_operation1, ls_operation2;
			ls_operation1 = Older.Operation_C[ls1];
			ls_operation2 = Older.Operation_C[ls2];
			//cout << "ls_operation1 = " << ls_operation1 << endl;
			//cout << "ls_operation2 = " << ls_operation2 << endl;

			////�ҳ�Ⱦɫ������������ҵ��λ������
			////�ҵ�ls_operation1�γ��ֵ�ls_job1
			int ls_index1, ls_index2;
			int ls_count1 = 0;
			for (int jj = 0; jj < number_of_jobs2 * number_of_operations; jj++)
			{
				if (Older.v_chromosome2[jj].operation_number == ls_job1)
				{
					ls_count1++;
				}
				if (ls_count1 == ls_operation1)
				{
					ls_index1 = jj;
					break;
				}
			}
			int ls_count2 = 0;
			for (int jj = 0; jj < number_of_jobs2 * number_of_operations; jj++)
			{
				if (Older.v_chromosome2[jj].operation_number == ls_job2)
				{
					ls_count2++;
				}
				if (ls_count2 == ls_operation2)
				{
					ls_index2 = jj;
					break;
				}
			}
			//cout << "ls_index1 = " << ls_index1 << endl;
			//cout << "ls_index2 = " << ls_index2 << endl;

			////����������ҵ�ڹ��������е�λ��
			int ls_temp = New.v_chromosome2[ls_index1].operation_number;
			New.v_chromosome2[ls_index1].operation_number = New.v_chromosome2[ls_index2].operation_number;
			New.v_chromosome2[ls_index2].operation_number = ls_temp;
			//ͬʱ���������ǵ�job��Ϣ
			int temp_job_number = New.v_chromosome2[ls_index1].job_number;
			New.v_chromosome2[ls_index1].job_number = New.v_chromosome2[ls_index2].job_number;
			New.v_chromosome2[ls_index2].job_number = temp_job_number;
			//������job��Ϣ�������ǵ�operation_index��Ϣ
			for (int k = 0; k < number_of_jobs2; k++)//�ж���ÿ��job�ĵڼ�������
			{
				int current_job_number = k + 1;
				int count = 0;
				for (int c = 0; c < number_of_jobs2 * number_of_operations; c++)
				{
					if (current_job_number == New.v_chromosome2[c].job_number)
					{
						count = count + 1;
						New.v_chromosome2[c].operation_index = count;
					}
					continue;
				}
			}

			//////���LS���Ⱦɫ������
			//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
			//{
			//	cout << New.v_chromosome2[n].operation_number << " ";
			//}
			//cout << endl;
			//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
			//{
			//	cout << New.v_chromosome2[n].job_number << " ";
			//}
			//cout << endl;
			//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
			//{
			//	cout << New.v_chromosome2[n].operation_index << " ";
			//}
			//cout << endl;
			//for (int n = number_of_jobs2 * number_of_operations; n < New.v_chromosome2.size(); n++)
			//{
			//	cout << New.v_chromosome2[n].machine_number << " ";
			//}
			//cout << endl << endl;
			//system("pause");
		}
	}
	else if (rand_select_number == 2)
	{
		//cout << "ִ��Case2" << endl;
		int ls_size = Older.Job_C.size();
		//cout << "ls_size = " << ls_size << endl;
		if (ls_size >= 2)
		{
			//���ѡ�������ؼ�job
			int ls1 = rand() % ls_size;
			int ls2 = rand() % ls_size;
			while (ls1 == ls2)
			{
				ls2 = rand() % ls_size;
			}
			if (ls1 > ls2)
			{
				int temp = ls1;
				ls1 = ls2;
				ls2 = temp;
			}
			//cout << "ls1 = " << ls1 << endl;
			//cout << "ls2= " << ls2 << endl;
			int ls_job1, ls_job2;
			ls_job1 = Older.Job_C[ls1];
			ls_job2 = Older.Job_C[ls2];
			//cout << "ls_job1 = " << ls_job1 << endl;
			//cout << "ls_job2 = " << ls_job2 << endl;

			int ls_operation1, ls_operation2;
			ls_operation1 = Older.Operation_C[ls1];
			ls_operation2 = Older.Operation_C[ls2];
			//cout << "ls_operation1 = " << ls_operation1 << endl;
			//cout << "ls_operation2 = " << ls_operation2 << endl;

			////�ҳ�Ⱦɫ������������ҵ��λ������
			////�ҵ�ls_operation1�γ��ֵ�ls_job1
			int ls_index1, ls_index2;
			int ls_count1 = 0;
			for (int jj = 0; jj < number_of_jobs2 * number_of_operations; jj++)
			{
				if (Older.v_chromosome2[jj].operation_number == ls_job1)
				{
					ls_count1++;
				}
				if (ls_count1 == ls_operation1)
				{
					ls_index1 = jj;
					break;
				}
			}
			int ls_count2 = 0;
			for (int jj = 0; jj < number_of_jobs2 * number_of_operations; jj++)
			{
				if (Older.v_chromosome2[jj].operation_number == ls_job2)
				{
					ls_count2++;
				}
				if (ls_count2 == ls_operation2)
				{
					ls_index2 = jj;
					break;
				}
			}
			//cout << "ls_index1 = " << ls_index1 << endl;
			//cout << "ls_index2 = " << ls_index2 << endl;

			////�������operation���뿿ǰ��operation��ǰ�棬������������
			//�Ƚ�ѡ�еĿ���һ���operation��Ⱦɫ����ɾ��
			New.v_chromosome2.erase(New.v_chromosome2.begin() + ls_index2);
			int current_size = New.v_chromosome2.size();
			//cout << "current_size = " << current_size << endl;
			//Ȼ���ٰ������뵽��ǰһ���operation��ǰ��λ��
			CChromosome tttt;
			tttt.operation_number = ls_job2;
			New.v_chromosome2.insert(New.v_chromosome2.begin() + ls_index1, tttt);
			current_size = New.v_chromosome2.size();
			//cout << "current_size = " << current_size << endl;
			//ͬʱ���������ǵ�job��Ϣ
			for (int k = 0; k<number_of_jobs2 * number_of_operations; k++)
			{
				New.v_chromosome2[k].job_number = New.v_chromosome2[k].operation_number;
			}
			//������job��Ϣ�������ǵ�operation_index��Ϣ
			for (int k = 0; k < number_of_jobs2; k++)//�ж���ÿ��job�ĵڼ�������
			{
				int current_job_number = k + 1;
				int count = 0;
				for (int c = 0; c < number_of_jobs2 * number_of_operations; c++)
				{
					if (current_job_number == New.v_chromosome2[c].job_number)
					{
						count = count + 1;
						New.v_chromosome2[c].operation_index = count;
					}
					continue;
				}
			}

			////���LS���Ⱦɫ������
			//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
			//{
			//	cout << New.v_chromosome2[n].operation_number << " ";
			//}
			//cout << endl;
			//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
			//{
			//	cout << New.v_chromosome2[n].job_number << " ";
			//}
			//cout << endl;
			//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
			//{
			//	cout << New.v_chromosome2[n].operation_index << " ";
			//}
			//cout << endl;
			//for (int n = number_of_jobs2 * number_of_operations; n < New.v_chromosome2.size(); n++)
			//{
			//	cout << New.v_chromosome2[n].machine_number << " ";
			//}
			//cout << endl << endl;
			//system("pause");
		}
	}
	else
	{
		//cout << "ִ��Case3" << endl;
		int ls_size = Older.Job_C.size();
		//cout << "ls_size = " << ls_size << endl;
		//���ѡ��1���ؼ�job
		int ls = rand() % ls_size;
		//cout << "ls = " << ls << endl;
		int ls_job;
		ls_job = Older.Job_C[ls];
		//cout << "ls_job = " << ls_job << endl;
		int ls_operation;
		ls_operation = Older.Operation_C[ls];
		//cout << "ls_operation = " << ls_operation << endl;
		//��ȡ��job�ĸõ�����Ŀ�ʹ�û�������
		int operation_machine_size = v_available_machines[ls_job - 1][ls_operation - 1].size();
		//cout << "operation_machine_size = " << operation_machine_size << endl;
		if (operation_machine_size >= 2)
		{
			int rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			int rand_machine_number = v_available_machines[ls_job - 1][ls_operation - 1][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
			int index = (ls_job - 1) * number_of_operations + number_of_jobs2 * number_of_operations + (ls_operation - 1);
			//cout << "index = " << index << endl;
			int current_machine_number = New.v_chromosome2[index].machine_number;
			while (current_machine_number == rand_machine_number)
			{
				rand_machine_number_index = rand() % operation_machine_size;
				//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
				rand_machine_number = v_available_machines[ls_job - 1][ls_operation - 1][rand_machine_number_index];
				//cout << "rand_machine_number = " << rand_machine_number << endl;
			}
			New.v_chromosome2[index].machine_number = rand_machine_number;
		}
		////���LS���Ⱦɫ������
		//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
		//{
		//	cout << New.v_chromosome2[n].operation_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
		//{
		//	cout << New.v_chromosome2[n].job_number << " ";
		//}
		//cout << endl;
		//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
		//{
		//	cout << New.v_chromosome2[n].operation_index << " ";
		//}
		//cout << endl;
		//for (int n = number_of_jobs2 * number_of_operations; n < New.v_chromosome2.size(); n++)
		//{
		//	cout << New.v_chromosome2[n].machine_number << " ";
		//}
		//cout << endl << endl;
		//system("pause");
	}
}