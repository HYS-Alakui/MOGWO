#include "Genetic.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

void CGenetic::GWO()//评估适应度
{
	//cout << "------------3、执行四种交叉---------" << endl;
	//cout << "------------4、执行三种变异---------" << endl;
	vector <CIndividual>().swap(v_new_individuals);
	vector <CIndividual>().swap(v_Chromo_temp);//清空容器
	vector <CIndividual> v_Chromo_temp(v_Chromo);//拷贝构造，方便后续使用
	//cout << "拷贝后临时种群：" << endl;
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
	for (int i = 0; i < v_Chromo.size(); i++)//每个老个体对应一个新个体，故循环v_Chromo.size()次！
	{
		//cout << "The index of individual ：i = " << i << endl;
		//cout << "best_size = " << best_size << endl;//层数
		int best_individual_index1, best_individual_index2, best_individual_index3;//确定当前个体的afa,beta,geta狼
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
			if (best_size == 2)//剩下一个从第二层任意选
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

		//为了避免收敛和陷入局部最优，以一定的概率进行
		//step1:随机产生一个概率，若该概率≤p_gwo_probi，则随机选中一头决策狼和当前个体进行交叉得到子代
		//step1:否则，将当前个体和随机一头附属狼进行交叉得到子代
		//step1:p_gwo_probi会随着迭代次数的增加降低，避免算法早熟。
		int current_individual_index = i;
		p_gwo_probi =1 - (current_number_of_fitness_evaluations / total_number_of_fitness_evaluations) ;
		//p_gwo_probi = sqrt(p_gwo_probi);
		//cout << "p_gwo_probi = " << p_gwo_probi << endl;
		int rank_value = v_Chromo_temp[current_individual_index].rank;//获取当前个体的rank值
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
			crossover(fathIndiv, mothIndiv, chIndiv1, chIndiv2);//对这两个作业进行交叉，调用交叉函数，在two_indiv中
			//system("pause");
			mutate(chIndiv1, 1.0);//防止收敛，再对这两个个体进行变异
			//system("pause");
			assign(chIndiv1);
			//判断是否有工厂为空，若有工厂为空则重新随机生成工厂向量
			for (int f = 0; f < number_of_factories; f++)
			{
				int f_size = chIndiv1.v_job_assignment[f].size();
				if (f_size == 0)
				{
					int index_f;
					for (int j = 0; j < number_of_jobs1; j++)//染色体工厂部分，长度与job的数目相等
					{
						index_f = rand() % number_of_factories + 1;//取值范围是[1,number_of_factories]
						chIndiv1.v_chromosome1[j].factory_number = index_f;
					}
					break;
				}
			}
			assign(chIndiv1);
			evaluate_DFSP(chIndiv1);//计算子代1的目标值
			evaluate_FJSP(chIndiv1);//计算子代1的目标值
			evaluate(chIndiv1);//计算子代1的目标值
			//for (int ob = 0; ob < number_of_objectives; ob++)
			//{
			//	cout << "chIndiv1.v_objective_value = " << chIndiv1.v_objective_value[ob] << " ";
			//}
			//cout << endl;
			//system("pause");
			mutate(chIndiv2, 1.0);
			assign(chIndiv2);
			//判断是否有工厂为空，若有工厂为空则重新随机生成工厂向量
			for (int f = 0; f < number_of_factories; f++)
			{
				int f_size = chIndiv2.v_job_assignment[f].size();
				if (f_size == 0)
				{
					int index_f;
					for (int j = 0; j < number_of_jobs1; j++)//染色体工厂部分，长度与job的数目相等
					{
						index_f = rand() % number_of_factories + 1;//取值范围是[1,number_of_factories]
						chIndiv2.v_chromosome1[j].factory_number = index_f;
					}
					break;
				}
			}
			assign(chIndiv2);
			evaluate_DFSP(chIndiv2);//计算子代1的目标值
			evaluate_FJSP(chIndiv2);//计算子代1的目标值
			evaluate(chIndiv2);//计算子代1的目标值
			//for (int ob = 0; ob < number_of_objectives; ob++)
			//{
			//	cout << "chIndiv2.v_objective_value = " << chIndiv2.v_objective_value[ob] << " ";
			//}
			//cout << endl;
			//system("pause");

			////判断两个个体的支配关系，选较优秀的子代个体；
			int domRel = 3;
			domRelation(chIndiv1, chIndiv2, domRel);

			if (domRel == 1)//子代1支配子代2
			{
				v_new_individuals.push_back(chIndiv1);//将子代1 尾插 到 子代种群中	
			}
			else
			{
				v_new_individuals.push_back(chIndiv2);//将子代2 尾插 到 子代种群中
			}

			//cout << "由决策狼和当前狼产生的最终子代：" << endl;
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
			//随机选中一个附属狼和当前狼进行交叉得到子代
			int fushu_wolf_index;
			if (best_size > 4)
			{
				//产生一个数，范围是4至best_size-1//[a, b)的随机整数，使用(rand() % (b - a)) + a;
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

			crossover(fathIndiv, mothIndiv, chIndiv1, chIndiv2);//对这两个作业进行交叉，调用交叉函数，在two_indiv中
			//system("pause");
			mutate(chIndiv1, 1.0);//防止收敛，再对这两个个体进行变异
			//system("pause");
			assign(chIndiv1);
			//判断是否有工厂为空，若有工厂为空则重新随机生成工厂向量
			for (int f = 0; f < number_of_factories; f++)
			{
				int f_size = chIndiv1.v_job_assignment[f].size();
				if (f_size == 0)
				{
					int index_f;
					for (int j = 0; j <number_of_jobs1; j++)//染色体工厂部分，长度与job的数目相等
					{
						index_f = rand() % number_of_factories + 1;//取值范围是[1,number_of_factories]
						chIndiv1.v_chromosome1[j].factory_number = index_f;
					}
					break;
				}
			}
			assign(chIndiv1);
			evaluate_DFSP(chIndiv1);//计算子代1的目标值
			evaluate_FJSP(chIndiv1);//计算子代1的目标值
			evaluate(chIndiv1);//计算子代1的目标值
			//for (int ob = 0; ob < number_of_objectives; ob++)
			//{
			//	cout << "chIndiv1.v_objective_value = " << chIndiv1.v_objective_value[ob] << " ";
			//}
			//cout << endl;
			//system("pause");
			mutate(chIndiv2, 1.0);
			assign(chIndiv2);
			//判断是否有工厂为空，若有工厂为空则重新随机生成工厂向量
			for (int f = 0; f < number_of_factories; f++)
			{
				int f_size = chIndiv2.v_job_assignment[f].size();
				if (f_size == 0)
				{
					int index_f;
					for (int j = 0; j < number_of_jobs1; j++)//染色体工厂部分，长度与job的数目相等
					{
						index_f = rand() % number_of_factories + 1;//取值范围是[1,number_of_factories]
						chIndiv2.v_chromosome1[j].factory_number = index_f;
					}
					break;
				}
			}
			assign(chIndiv2);
			evaluate_DFSP(chIndiv2);//计算子代1的目标值
			evaluate_FJSP(chIndiv2);//计算子代1的目标值
			evaluate(chIndiv2);//计算子代1的目标值
			//for (int ob = 0; ob < number_of_objectives; ob++)
			//{
			//	cout << "chIndiv2.v_objective_value = " << chIndiv2.v_objective_value[ob] << " ";
			//}
			//cout << endl;
			//system("pause");

			////判断两个个体的支配关系，选较优秀的子代个体；
			int domRel = 3;
			domRelation(chIndiv1, chIndiv2, domRel);
			if (domRel == 1)//子代1支配子代2
			{
				v_new_individuals.push_back(chIndiv1);//将子代1 尾插 到 子代种群中	
			}
			else
			{
				v_new_individuals.push_back(chIndiv2);//将子代2 尾插 到 子代种群中
			}
			//cout << "由附属狼和当前狼产生的最终子代：" << endl;
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

	//cout << "新种群：" << endl;
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