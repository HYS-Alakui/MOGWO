#include "Genetic.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"

void CGenetic::LS()
{
	//cout << "------------5、局部搜索---------" << endl;
	//对经过交叉和变异阶段的新种群中的个体进行基于关键路径的局部搜索
	vector <CIndividual>().swap(v_KLS_individuals);
	vector <CIndividual>().swap(v_new_individuals_temp);//清空容器
	vector <CIndividual> v_new_individuals_temp(v_new_individuals);//拷贝构造，方便后续使用
	//cout << "拷贝后临时新种群：" << endl;
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

	for (int i = 0; i < v_new_individuals_temp.size(); i++)//针对新种群中的每个个体执行基于知识的邻域搜索
	{
		//cout << "i = " << i << endl;
		//cout << "v_new_individuals_temp[i].key_cell = " << v_new_individuals_temp[i].key_cell << endl;
		if (v_new_individuals_temp[i].key_cell == 0)
		{
			//cout << "DFSP关键路径涉及的job_index和machine_index：" << endl;
			//for (int k = 0; k < v_new_individuals_temp[i].critical_path_operation.size(); k++)
			//{
			//	int job_index = v_new_individuals_temp[i].critical_path_operation[k] - 1;
			//	cout << job_index << " ";
			//	int machine_index = v_new_individuals_temp[i].critical_path_machine[k] - 1;
			//	cout << machine_index << endl;//机器索引号
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
			generate_newindividual1(Older, New);//调用下面的generate_newindividual函数

			////比较older和new的优劣，选择好的进入LS种群	
			assign(New);
			evaluate_DFSP(New);
			evaluate_FJSP(New);
			evaluate(New);
			//cout << "New的信息" << endl;
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
			if (domRel == 1)//子代1支配子代2
			{
				v_KLS_individuals.push_back(Older);//将子代1 尾插 到 子代种群中	
			}
			else
			{
				v_KLS_individuals.push_back(New);//将子代2 尾插 到 子代种群中		
			}			
			//cout << "由KLS产生的最终子代：" << endl;
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
			//cout << "关键路径涉及的job索引号：" << endl;
			//for (int k = 0; k < v_new_individuals_temp[i].Job_C.size(); k++)
			//{
			//	int job_index = v_new_individuals_temp[i].Job_C[k] - 1;
			//	cout << job_index << " ";
			//}
			//cout << endl;
			//cout << "关键路径涉及的operation序号索引号：" << endl;
			//for (int k = 0; k < v_new_individuals_temp[i].Operation_C.size(); k++)
			//{
			//	int operation_index = v_new_individuals_temp[i].Operation_C[k] - 1;
			//	cout << operation_index << " ";
			//}
			//cout << endl;
			//cout << "关键路径涉及的machine索引号：" << endl;
			//for (int k = 0; k < v_new_individuals_temp[i].Operation_C.size(); k++)
			//{
			//	int machine_index = v_new_individuals_temp[i].Machine_C[k];
			//	cout << machine_index << " ";//机器索引号
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
			generate_newindividual2(Older, New);//调用下面的generate_newindividual函数

			////比较older和new的优劣，选择好的进入LS种群	
			assign(New);
			evaluate_DFSP(New);
			evaluate_FJSP(New);
			evaluate(New);
			//cout << "New的信息" << endl;
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
			if (domRel == 1)//子代1支配子代2
			{
				v_KLS_individuals.push_back(Older);//将子代1 尾插 到 子代种群中	
			}
			else
			{
				v_KLS_individuals.push_back(New);//将子代2 尾插 到 子代种群中		
			}
			//cout << "由KLS产生的最终子代：" << endl;
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
	//cout<<"KLS1种群"<<endl;
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
	//cout << "Older的信息" << endl;
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
 
	////step1:获取该个体的关键job和非关键job
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
	////step2:执行四种邻域结构
	//Case1:随机选中两个关键job，然后在作业序列上互换两个job，工厂向量不变
	//Case2:随机选中两个关键job，然后把靠后的job插入靠前的job的前面，工厂向量不变
	//Case3:随机选中一个关键job和一个非关键job，然后在作业序列上互换两个job,工厂向量也要变化
	//Case4:随机选中一个关键job，然后更换它的工厂编号。
	int rand_select_number = (rand() % 4) + 1;
	//cout << "rand_select_number = " << rand_select_number << endl;
	if (rand_select_number == 1)
	{
		//cout << "执行Case1" << endl;
		int ls_size = key_jobs.size();
		//cout << "ls_size = " << ls_size << endl;
		if (ls_size >= 2)
		{
			//随机选中两个关键job
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

			//找出染色体中这两个作业的位置索引
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

			//交换两个作业在作业序列中的位置
			int ls_temp = New.v_chromosome1[ls_index1].job_number;
			New.v_chromosome1[ls_index1].job_number = New.v_chromosome1[ls_index2].job_number;
			New.v_chromosome1[ls_index2].job_number = ls_temp;
			////输出LS后的染色体序列
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
		//cout << "执行Case2" << endl;
		int ls_size = key_jobs.size();
		//cout << "ls_size = " << ls_size << endl;
		if (ls_size >= 2)
		{
			//随机选中两个关键job
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

			//找出染色体中这两个作业的位置索引
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

			//将选中的靠后一点的job在染色体中删除
			New.v_chromosome1.erase(New.v_chromosome1.begin() + ls_index2);
			int current_size = New.v_chromosome1.size();
			//cout << "current_size = " << current_size << endl;
			//然后再把它插入到靠前一点的job的前面位置
			CChromosome ttt;
			ttt.job_number = ls_job2;
			New.v_chromosome1.insert(New.v_chromosome1.begin() + ls_index1, ttt);
			current_size = New.v_chromosome1.size();
			//cout << "current_size = " << current_size << endl;
			//输出LS后的染色体序列
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
		//cout << "执行Case3" << endl;
		int ls_size1 = key_jobs.size();
		//cout << "ls_size1 = " << ls_size1 << endl;
		//随机选中1个关键job
		int ls1 = rand() % ls_size1;
		//cout << "ls1 = " << ls1 << endl;
		int ls_job1;
		ls_job1 = key_jobs[ls1];
		//cout << "ls_job1 = " << ls_job1 << endl;
		//随机选中1个非关键job
		int ls_size2 = unkey_jobs.size();
		//cout << "ls_size2 = " << ls_size2 << endl;
		int ls2 = rand() % ls_size2;
		//cout << "ls2 = " << ls2 << endl;
		int ls_job2;
		ls_job2 = unkey_jobs[ls2];
		//cout << "ls_job2 = " << ls_job2 << endl;
		//找出染色体中这两个作业的位置索引
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

		//交换两个作业在作业序列中的位置
		int ls_temp = New.v_chromosome1[ls_index1].job_number;
		New.v_chromosome1[ls_index1].job_number = New.v_chromosome1[ls_index2].job_number;
		New.v_chromosome1[ls_index2].job_number = ls_temp;
		int ls_temp2 = New.v_chromosome1[ls_job1 - 1].factory_number;
		New.v_chromosome1[ls_job1 - 1].factory_number = New.v_chromosome1[ls_job2 - 1].factory_number;
		New.v_chromosome1[ls_job2 - 1].factory_number = ls_temp2;
		////输出LS后的染色体序列
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
		//cout << "执行Case4" << endl;
		int ls_size = key_jobs.size();
		//cout << "ls_size = " << ls_size << endl;
		//随机选中1个关键job
		int ls = rand() % ls_size;
		//cout << "ls = " << ls << endl;
		int ls_job;
		ls_job = key_jobs[ls];
		//cout << "ls_job = " << ls_job << endl;
		//更换该job的工厂索引
		int ls_factory_number = (rand() % number_of_factories) + 1;
		while ((ls_factory_number - 1) == Older.key_factory_index)
		{
			ls_factory_number = (rand() % number_of_factories) + 1;
		}
		//cout << "ls_factory_number = " << ls_factory_number << endl;	
		New.v_chromosome1[ls_job - 1].factory_number = ls_factory_number;//更换工厂号	
		////输出LS后的染色体序列
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
	//cout << "Older的信息" << endl;
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
	//for (int j = 0; j < Older.Job_C.size(); j++)//job编号
	//{
	//	int job_n = Older.Job_C[j];
	//	cout << job_n << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < Older.Operation_C.size(); j++)//operation序号
	//{
	//	int operation_n = Older.Operation_C[j];
	//	cout << operation_n << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < Older.Operation_C.size(); j++)//machine编号
	//{
	//	int machine_n = Older.Machine_C[j] + 1;
	//	cout << machine_n << " ";
	//}
	//cout << endl;
	//system("pause");
	////step2:执行三种邻域结构
	//Case1:改变工序序列的加工顺序，随机选中两个关键operation，然后进行交换，机器向量不变
	//Case2:改变工序序列的加工顺序，随机选中两个关键operation，然后把靠后的operation插入靠前的operation的前面，机器向量不变
	//Case3:改变机器分配，随机选中一个关键operation，然后更换它的机器编号
	int rand_select_number = (rand() % 3) + 1;
	//cout << "rand_select_number = " << rand_select_number << endl;
	if (rand_select_number == 1)
	{
		//cout << "执行Case1" << endl;
		int ls_size = Older.Job_C.size();
		//cout << "ls_size = " << ls_size << endl;
		if (ls_size >= 2)
		{
			//随机选中两个关键job
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

			////找出染色体中这两个作业的位置索引
			////找第ls_operation1次出现的ls_job1
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

			////交换两个作业在工序序列中的位置
			int ls_temp = New.v_chromosome2[ls_index1].operation_number;
			New.v_chromosome2[ls_index1].operation_number = New.v_chromosome2[ls_index2].operation_number;
			New.v_chromosome2[ls_index2].operation_number = ls_temp;
			//同时，更新它们的job信息
			int temp_job_number = New.v_chromosome2[ls_index1].job_number;
			New.v_chromosome2[ls_index1].job_number = New.v_chromosome2[ls_index2].job_number;
			New.v_chromosome2[ls_index2].job_number = temp_job_number;
			//并根据job信息更新它们的operation_index信息
			for (int k = 0; k < number_of_jobs2; k++)//判断是每个job的第几道工序
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

			//////输出LS后的染色体序列
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
		//cout << "执行Case2" << endl;
		int ls_size = Older.Job_C.size();
		//cout << "ls_size = " << ls_size << endl;
		if (ls_size >= 2)
		{
			//随机选中两个关键job
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

			////找出染色体中这两个作业的位置索引
			////找第ls_operation1次出现的ls_job1
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

			////将靠后的operation插入靠前的operation的前面，机器向量不变
			//先将选中的靠后一点的operation在染色体中删除
			New.v_chromosome2.erase(New.v_chromosome2.begin() + ls_index2);
			int current_size = New.v_chromosome2.size();
			//cout << "current_size = " << current_size << endl;
			//然后再把它插入到靠前一点的operation的前面位置
			CChromosome tttt;
			tttt.operation_number = ls_job2;
			New.v_chromosome2.insert(New.v_chromosome2.begin() + ls_index1, tttt);
			current_size = New.v_chromosome2.size();
			//cout << "current_size = " << current_size << endl;
			//同时，更新它们的job信息
			for (int k = 0; k<number_of_jobs2 * number_of_operations; k++)
			{
				New.v_chromosome2[k].job_number = New.v_chromosome2[k].operation_number;
			}
			//并根据job信息更新它们的operation_index信息
			for (int k = 0; k < number_of_jobs2; k++)//判断是每个job的第几道工序
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

			////输出LS后的染色体序列
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
		//cout << "执行Case3" << endl;
		int ls_size = Older.Job_C.size();
		//cout << "ls_size = " << ls_size << endl;
		//随机选中1个关键job
		int ls = rand() % ls_size;
		//cout << "ls = " << ls << endl;
		int ls_job;
		ls_job = Older.Job_C[ls];
		//cout << "ls_job = " << ls_job << endl;
		int ls_operation;
		ls_operation = Older.Operation_C[ls];
		//cout << "ls_operation = " << ls_operation << endl;
		//获取该job的该道工序的可使用机器数量
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
		////输出LS后的染色体序列
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