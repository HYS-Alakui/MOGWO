#include "Genetic.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

void CGenetic::GWO()//������Ӧ��
{
	//cout << "------------3��ִ�����ֽ���---------" << endl;
	//cout << "------------4��ִ�����ֱ���---------" << endl;
	vector <CIndividual>().swap(v_new_individuals);
	vector <CIndividual>().swap(v_Chromo_temp);//�������
	vector <CIndividual> v_Chromo_temp(v_Chromo);//�������죬�������ʹ��
	//cout << "��������ʱ��Ⱥ��" << endl;
	//for (int i = 0; i < v_Chromo_temp.size(); i++)
	//{
	//	cout << "i = " << i + 1 << endl;
	//	int total_lenth1 = v_Chromo_temp[i].v_chromosome1.size();
	//	for (int j = 0; j < number_of_jobs1; j++)
	//	{
	//		cout << v_Chromo_temp[i].v_chromosome1[j].factory_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs1; j < total_lenth1; j++)
	//	{
	//		cout << v_Chromo_temp[i].v_chromosome1[j].job_number << " ";
	//	}
	//	cout << endl;
	//	int total_lenth2 = v_Chromo_temp[i].v_chromosome2.size();
	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//	{
	//		cout << v_Chromo_temp[i].v_chromosome2[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs2 * number_of_operations; j < total_lenth2; j++)
	//	{
	//		cout << v_Chromo_temp[i].v_chromosome2[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int ob = 0; ob < number_of_objectives; ob++)
	//	{
	//		cout << v_Chromo_temp[i].v_objective_value[ob] << " ";
	//	}
	//	cout << endl << endl;
	//}
	//system("pause");

	double p_gwo_probi = 0.0;
	for (int i = 0; i < v_Chromo.size(); i++)//ÿ���ϸ����Ӧһ���¸��壬��ѭ��v_Chromo.size()�Σ�
	{
		//cout << "The index of individual ��i = " << i << endl;
		//cout << "best_size = " << best_size << endl;//����
		int best_individual_index1, best_individual_index2, best_individual_index3;//ȷ����ǰ�����afa,beta,geta��
		if (best_size >= 3)
		{
			int no1, no2, no3;
			no1 = rand() % v_cluster[0].size();
			//cout << "no1 = " << no1 << endl;
			no2 = rand() % v_cluster[1].size();
			//cout << "no2 = " << no2 << endl;
			no3 = rand() % v_cluster[2].size();
			//cout << "no3 = " << no3 << endl;
			best_individual_index1 = v_cluster[0][no1].chromoNo;
			best_individual_index2 = v_cluster[1][no2].chromoNo;
			best_individual_index3 = v_cluster[2][no3].chromoNo;
		}
		else
		{
			if (best_size == 2)//ʣ��һ���ӵڶ�������ѡ
			{
				int no1, no2, no3;
				no1 = rand() % v_cluster[0].size();
				//cout << "no1 = " << no1 << endl;
				no2 = rand() % v_cluster[1].size();
				//cout << "no2 = " << no2 << endl;
				no3 = rand() % v_cluster[1].size();
				//cout << "no3 = " << no3 << endl;
				best_individual_index1 = v_cluster[0][no1].chromoNo;
				best_individual_index2 = v_cluster[1][no2].chromoNo;
				best_individual_index3 = v_cluster[1][no3].chromoNo;
			}
			else if (best_size == 1)
			{
				int no1, no2, no3;
				no1 = rand() % v_cluster[0].size();
				//cout << "no1 = " << no1 << endl;
				no2 = rand() % v_cluster[0].size();
				//cout << "no2 = " << no2 << endl;
				no3 = rand() % v_cluster[0].size();
				//cout << "no3 = " << no3 << endl;
				best_individual_index1 = v_cluster[0][no1].chromoNo;
				best_individual_index2 = v_cluster[0][no2].chromoNo;
				best_individual_index3 = v_cluster[0][no3].chromoNo;
			}
		}
		//cout << "best_individual_index1 = " << best_individual_index1 << endl;
		//cout << "best_individual_index2 = " << best_individual_index2 << endl;
		//cout << "best_individual_index3 = " << best_individual_index3 << endl;
		//system("pause");

		//Ϊ�˱�������������ֲ����ţ���һ���ĸ��ʽ���
		//step1:�������һ�����ʣ����ø��ʡ�p_gwo_probi�������ѡ��һͷ�����Ǻ͵�ǰ������н���õ��Ӵ�
		//step1:���򣬽���ǰ��������һͷ�����ǽ��н���õ��Ӵ�
		//step1:p_gwo_probi�����ŵ������������ӽ��ͣ������㷨���졣
		int current_individual_index = i;
		p_gwo_probi =1 - (current_number_of_fitness_evaluations / total_number_of_fitness_evaluations) ;
		//p_gwo_probi = sqrt(p_gwo_probi);
		//cout << "p_gwo_probi = " << p_gwo_probi << endl;
		int rank_value = v_Chromo_temp[current_individual_index].rank;//��ȡ��ǰ�����rankֵ
		//cout << "rank_value = " << rank_value<<endl;
		if (rand() / (RAND_MAX * 1.0) <= p_gwo_probi)
		{
			int rand_index, decision_wolf_index;
			if (rank_value == 1)
			{
				decision_wolf_index = best_individual_index1;
			}
			else if (rank_value == 2)
			{
				rand_index = rand() % 2;
				//cout << "rand_index = " << rand_index << endl;
				if (rand_index == 0)
				{
					decision_wolf_index = best_individual_index1;
				}
				else
				{
					decision_wolf_index = best_individual_index2;
				}
			}
			else
			{
				rand_index = rand() % 3;
				//cout << "rand_index = " << rand_index << endl;
				if (rand_index == 0)
				{
					decision_wolf_index = best_individual_index1;
				}
				else if (rand_index == 1)
				{
					decision_wolf_index = best_individual_index2;
				}
				else
				{
					decision_wolf_index = best_individual_index3;
				}
			}
			//cout << "decision_wolf_index = " << decision_wolf_index << endl;
			//cout << "current_individual_index = " << current_individual_index << endl;
			//system("pause");

			CIndividual fathIndiv, mothIndiv, chIndiv1, chIndiv2;
			fathIndiv = v_Chromo_temp[decision_wolf_index];
			mothIndiv = v_Chromo_temp[current_individual_index];
			crossover(fathIndiv, mothIndiv, chIndiv1, chIndiv2);//����������ҵ���н��棬���ý��溯������two_indiv��
			//system("pause");
			mutate(chIndiv1, 1.0);//��ֹ�������ٶ�������������б���
			//system("pause");
			assign(chIndiv1);
			//�ж��Ƿ��й���Ϊ�գ����й���Ϊ��������������ɹ�������
			for (int f = 0; f < number_of_factories; f++)
			{
				int f_size = chIndiv1.v_job_assignment[f].size();
				if (f_size == 0)
				{
					int index_f;
					for (int j = 0; j < number_of_jobs1; j++)//Ⱦɫ�幤�����֣�������job����Ŀ���
					{
						index_f = rand() % number_of_factories + 1;//ȡֵ��Χ��[1,number_of_factories]
						chIndiv1.v_chromosome1[j].factory_number = index_f;
					}
					break;
				}
			}
			assign(chIndiv1);
			evaluate_DFSP(chIndiv1);//�����Ӵ�1��Ŀ��ֵ
			evaluate_FJSP(chIndiv1);//�����Ӵ�1��Ŀ��ֵ
			evaluate(chIndiv1);//�����Ӵ�1��Ŀ��ֵ
			//for (int ob = 0; ob < number_of_objectives; ob++)
			//{
			//	cout << "chIndiv1.v_objective_value = " << chIndiv1.v_objective_value[ob] << " ";
			//}
			//cout << endl;
			//system("pause");
			mutate(chIndiv2, 1.0);
			assign(chIndiv2);
			//�ж��Ƿ��й���Ϊ�գ����й���Ϊ��������������ɹ�������
			for (int f = 0; f < number_of_factories; f++)
			{
				int f_size = chIndiv2.v_job_assignment[f].size();
				if (f_size == 0)
				{
					int index_f;
					for (int j = 0; j < number_of_jobs1; j++)//Ⱦɫ�幤�����֣�������job����Ŀ���
					{
						index_f = rand() % number_of_factories + 1;//ȡֵ��Χ��[1,number_of_factories]
						chIndiv2.v_chromosome1[j].factory_number = index_f;
					}
					break;
				}
			}
			assign(chIndiv2);
			evaluate_DFSP(chIndiv2);//�����Ӵ�1��Ŀ��ֵ
			evaluate_FJSP(chIndiv2);//�����Ӵ�1��Ŀ��ֵ
			evaluate(chIndiv2);//�����Ӵ�1��Ŀ��ֵ
			//for (int ob = 0; ob < number_of_objectives; ob++)
			//{
			//	cout << "chIndiv2.v_objective_value = " << chIndiv2.v_objective_value[ob] << " ";
			//}
			//cout << endl;
			//system("pause");

			////�ж����������֧���ϵ��ѡ��������Ӵ����壻
			int domRel = 3;
			domRelation(chIndiv1, chIndiv2, domRel);

			if (domRel == 1)//�Ӵ�1֧���Ӵ�2
			{
				v_new_individuals.push_back(chIndiv1);//���Ӵ�1 β�� �� �Ӵ���Ⱥ��	
			}
			else
			{
				v_new_individuals.push_back(chIndiv2);//���Ӵ�2 β�� �� �Ӵ���Ⱥ��
			}

			//cout << "�ɾ����Ǻ͵�ǰ�ǲ����������Ӵ���" << endl;
			//for (int n = 0; n < number_of_jobs1; n++)
			//{
			//	cout << v_new_individuals[i].v_chromosome1[n].factory_number << " ";
			//}
			//cout << endl;
			//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
			//{
			//	cout << v_new_individuals[i].v_chromosome1[n].job_number << " ";
			//}
			//cout << endl;
			//for (int n = 0; n < number_of_jobs2*number_of_operations; n++)
			//{
			//	cout << v_new_individuals[i].v_chromosome2[n].operation_number << " ";
			//}
			//cout << endl;
			//for (int n = 0; n < number_of_jobs2*number_of_operations; n++)
			//{
			//	cout << v_new_individuals[i].v_chromosome2[n].operation_index << " ";
			//}
			//cout << endl;
			//for (int n = number_of_jobs2 * number_of_operations; n < v_new_individuals[i].v_chromosome2.size(); n++)
			//{
			//	cout << v_new_individuals[i].v_chromosome2[n].machine_number << " ";
			//}
			//cout << endl;
			//for (int ob = 0; ob < number_of_objectives; ob++)
			//{
			//	cout << "v_new_individuals[" << i << "].v_objective_value  =" << v_new_individuals[i].v_objective_value[ob] << " ";
			//}
			//cout << endl;
			//system("pause");		

		}
		else
		{
			//���ѡ��һ�������Ǻ͵�ǰ�ǽ��н���õ��Ӵ�
			int fushu_wolf_index;
			if (best_size > 4)
			{
				//����һ��������Χ��4��best_size-1//[a, b)�����������ʹ��(rand() % (b - a)) + a;
				int rand_c_num = 4 + (rand() % (best_size - 4));
				//cout << "rand_c_num = " << rand_c_num << endl;
				int rand_c_size = v_cluster[rand_c_num - 1].size();
				//cout << "rand_c_size = " << rand_c_size << endl;
				int no4 = rand() % rand_c_size;
				//cout << "no4 = " << no4 << endl;
				fushu_wolf_index = v_cluster[rand_c_num - 1][no4].chromoNo;
			}
			else if (best_size == 4)
			{
				int rand_c_num =  4;
				//cout << "rand_c_num = " << rand_c_num << endl;
				int rand_c_size = v_cluster[rand_c_num - 1].size();
				//cout << "rand_c_size = " << rand_c_size << endl;
				int no4 = rand() % rand_c_size;
				//cout << "no4 = " << no4 << endl;
				fushu_wolf_index = v_cluster[rand_c_num - 1][no4].chromoNo;
			}
			else
			{
				fushu_wolf_index = rand() % number_of_individuals;
				while (fushu_wolf_index == current_individual_index)
				{
					fushu_wolf_index = rand() % number_of_individuals;
				}
			}
			//cout << "fushu_wolf_index = " << fushu_wolf_index << endl;
			//cout << "current_individual_index = " << current_individual_index << endl;
			//system("pause");

			CIndividual fathIndiv, mothIndiv, chIndiv1, chIndiv2;
			fathIndiv = v_Chromo_temp[fushu_wolf_index];
			mothIndiv = v_Chromo_temp[current_individual_index];

			crossover(fathIndiv, mothIndiv, chIndiv1, chIndiv2);//����������ҵ���н��棬���ý��溯������two_indiv��
			//system("pause");
			mutate(chIndiv1, 1.0);//��ֹ�������ٶ�������������б���
			//system("pause");
			assign(chIndiv1);
			//�ж��Ƿ��й���Ϊ�գ����й���Ϊ��������������ɹ�������
			for (int f = 0; f < number_of_factories; f++)
			{
				int f_size = chIndiv1.v_job_assignment[f].size();
				if (f_size == 0)
				{
					int index_f;
					for (int j = 0; j <number_of_jobs1; j++)//Ⱦɫ�幤�����֣�������job����Ŀ���
					{
						index_f = rand() % number_of_factories + 1;//ȡֵ��Χ��[1,number_of_factories]
						chIndiv1.v_chromosome1[j].factory_number = index_f;
					}
					break;
				}
			}
			assign(chIndiv1);
			evaluate_DFSP(chIndiv1);//�����Ӵ�1��Ŀ��ֵ
			evaluate_FJSP(chIndiv1);//�����Ӵ�1��Ŀ��ֵ
			evaluate(chIndiv1);//�����Ӵ�1��Ŀ��ֵ
			//for (int ob = 0; ob < number_of_objectives; ob++)
			//{
			//	cout << "chIndiv1.v_objective_value = " << chIndiv1.v_objective_value[ob] << " ";
			//}
			//cout << endl;
			//system("pause");
			mutate(chIndiv2, 1.0);
			assign(chIndiv2);
			//�ж��Ƿ��й���Ϊ�գ����й���Ϊ��������������ɹ�������
			for (int f = 0; f < number_of_factories; f++)
			{
				int f_size = chIndiv2.v_job_assignment[f].size();
				if (f_size == 0)
				{
					int index_f;
					for (int j = 0; j < number_of_jobs1; j++)//Ⱦɫ�幤�����֣�������job����Ŀ���
					{
						index_f = rand() % number_of_factories + 1;//ȡֵ��Χ��[1,number_of_factories]
						chIndiv2.v_chromosome1[j].factory_number = index_f;
					}
					break;
				}
			}
			assign(chIndiv2);
			evaluate_DFSP(chIndiv2);//�����Ӵ�1��Ŀ��ֵ
			evaluate_FJSP(chIndiv2);//�����Ӵ�1��Ŀ��ֵ
			evaluate(chIndiv2);//�����Ӵ�1��Ŀ��ֵ
			//for (int ob = 0; ob < number_of_objectives; ob++)
			//{
			//	cout << "chIndiv2.v_objective_value = " << chIndiv2.v_objective_value[ob] << " ";
			//}
			//cout << endl;
			//system("pause");

			////�ж����������֧���ϵ��ѡ��������Ӵ����壻
			int domRel = 3;
			domRelation(chIndiv1, chIndiv2, domRel);
			if (domRel == 1)//�Ӵ�1֧���Ӵ�2
			{
				v_new_individuals.push_back(chIndiv1);//���Ӵ�1 β�� �� �Ӵ���Ⱥ��	
			}
			else
			{
				v_new_individuals.push_back(chIndiv2);//���Ӵ�2 β�� �� �Ӵ���Ⱥ��
			}
			//cout << "�ɸ����Ǻ͵�ǰ�ǲ����������Ӵ���" << endl;
			//for (int n = 0; n < number_of_jobs1; n++)
			//{
			//	cout << v_new_individuals[i].v_chromosome1[n].factory_number << " ";
			//}
			//cout << endl;
			//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
			//{
			//	cout << v_new_individuals[i].v_chromosome1[n].job_number << " ";
			//}
			//cout << endl;
			//for (int n = 0; n < number_of_jobs2*number_of_operations; n++)
			//{
			//	cout << v_new_individuals[i].v_chromosome2[n].operation_number << " ";
			//}
			//cout << endl;
			//for (int n = 0; n < number_of_jobs2*number_of_operations; n++)
			//{
			//	cout << v_new_individuals[i].v_chromosome2[n].operation_index << " ";
			//}
			//cout << endl;
			//for (int n = number_of_jobs2 * number_of_operations; n < v_new_individuals[i].v_chromosome2.size(); n++)
			//{
			//	cout << v_new_individuals[i].v_chromosome2[n].machine_number << " ";
			//}
			//cout << endl;
			//for (int ob = 0; ob < number_of_objectives; ob++)
			//{
			//	cout << "v_new_individuals[" << i << "].v_objective_value  =" << v_new_individuals[i].v_objective_value[ob] << " ";
			//}
			//cout << endl;
			//system("pause");

		}
		//system("pause");
	}

	//cout << "����Ⱥ��" << endl;
	//for (int i = 0; i < v_new_individuals.size(); i++)
	//{
	//	cout << "i= " << i << endl;
	//	for (int j = 0; j < number_of_jobs1; j++)
	//	{
	//		cout << v_new_individuals[i].v_chromosome1[j].factory_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)
	//	{
	//		cout << v_new_individuals[i].v_chromosome1[j].job_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//	{
	//		cout << v_new_individuals[i].v_chromosome2[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//	{
	//		cout << v_new_individuals[i].v_chromosome2[j].operation_index << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs2 * number_of_operations; j < v_new_individuals[i].v_chromosome2.size(); j++)
	//	{
	//		cout << v_new_individuals[i].v_chromosome2[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	for (int k = 0; k < v_new_individuals[i].v_objective_value.size(); k++)
	//	{
	//		cout << v_new_individuals[i].v_objective_value[k] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//system("pause");
}