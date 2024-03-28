#include "headfile.h"
#include "Individual.h"
#include "Genetic.h"
#include "rankSequ.h"
#include "Chromosome.h"

void CGenetic::crossover(CIndividual& fathIndiv, CIndividual& mothIndiv, CIndividual& chIndiv1, CIndividual& chIndiv2)//传入4个对象：父亲，母亲，子代1，子代2
{
	//cout << "父亲的工厂和作业序列信息：" << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << fathIndiv.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
	//{
	//	cout << fathIndiv.v_chromosome1[n].job_number << " ";
	//}
	//cout << endl;

	//cout << "母亲的工厂和作业序列信息：" << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << mothIndiv.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
	//{
	//	cout << mothIndiv.v_chromosome1[n].job_number << " ";
	//}
	//cout << endl;


	//cout << "子代初始化：" << endl;
	vector <CChromosome>().swap(chIndiv1.v_chromosome1);//清空子代容器
	vector <CChromosome>().swap(chIndiv2.v_chromosome1);//清空子代容器
	for (int j = 0; j < number_of_jobs1; j++)//子代个体初始化，一开始得先创建对象，再对对象的job_number全部赋值为0
	{
		CChromosome	tt1;
		tt1.factory_number = 0;
		chIndiv1.v_chromosome1.push_back(tt1);
		CChromosome	tt2;
		tt2.factory_number = 0;
		chIndiv2.v_chromosome1.push_back(tt2);
	}
	for (int j = 0; j < number_of_jobs1; j++)//子代个体初始化，一开始得先创建对象，再对对象的factory_number全部赋值为0
	{
		CChromosome	tt3;
		tt3.job_number = 0;
		chIndiv1.v_chromosome1.push_back(tt3);
		CChromosome	tt4;
		tt4.job_number = 0;
		chIndiv2.v_chromosome1.push_back(tt4);
	}

	////step1:对工厂序列执行均匀交叉
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	//随机产生一个0-1数，若该数=0，则取父亲基因，若该数=1，则取母亲基因。
	//	int rand_m_number1 = rand() % 2;
	//	//cout << "rand_number1 = " << rand_m_number1 << endl;
	//	if (rand_m_number1 == 0)
	//	{
	//		chIndiv1.v_chromosome1[j].factory_number = fathIndiv.v_chromosome1[j].factory_number;
	//	}
	//	else if (rand_m_number1 == 1)
	//	{
	//		chIndiv1.v_chromosome1[j].factory_number = mothIndiv.v_chromosome1[j].factory_number;
	//	}
	//}
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	//随机产生一个0-1数，若该数=0，则取父亲基因，若该数=1，则取母亲基因。
	//	int rand_m_number2 = rand() % 2;
	//	//cout << "rand_number2 = " << rand_m_number2 << endl;
	//	if (rand_m_number2 == 0)
	//	{
	//		chIndiv2.v_chromosome1[j].factory_number = fathIndiv.v_chromosome1[j].factory_number;
	//	}
	//	else if (rand_m_number2 == 1)
	//	{
	//		chIndiv2.v_chromosome1[j].factory_number = mothIndiv.v_chromosome1[j].factory_number;
	//	}
	//}
	//cout << "交叉后两个子代的工厂序列：" << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << chIndiv1.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << chIndiv2.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	////补充作业信息
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	chIndiv1.v_chromosome1[n].job_number = n + 1;
	//	chIndiv2.v_chromosome1[n].job_number = n + 1;
	//}
	//cout << endl;
	//system("pause");

	//step1:对工厂序列执行两点交叉
	int cutpoint23, cutpoint24, temp22, facNo;
	cutpoint23 = rand() % number_of_jobs1;
	cutpoint24 = rand() % number_of_jobs1;
	while (cutpoint23 == cutpoint24)//若两个切点相同
	{
		cutpoint24 = rand() % number_of_jobs1;
	}
	if (cutpoint23 > cutpoint24)
	{
		temp22 = cutpoint23;
		cutpoint23 = cutpoint24;
		cutpoint24 = temp22;
	}
	//cout << "cutpoint23 = " << cutpoint23 << endl;
	//cout << "cutpoint24 = " << cutpoint24 << endl;
	for (int j = cutpoint23; j < cutpoint24; j++)
	{
		facNo = fathIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv1.v_chromosome1[j].factory_number = facNo;
		//cout << "chIndiv1.v_chromosome1[j].factory_number  = " << chIndiv1.v_chromosome1[j].factory_number << endl;
		facNo = mothIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv2.v_chromosome1[j].factory_number = facNo;
		//cout << "chIndiv2.v_chromosome1[j].factory_number  = " << chIndiv2.v_chromosome1[j].factory_number << endl;
	}
	for (int j = 0; j < cutpoint23; j++)
	{
		facNo =  mothIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv1.v_chromosome1[j].factory_number = facNo;
		//cout << "chIndiv1.v_chromosome1[j].factory_number = " << chIndiv1.v_chromosome1[j].factory_number << endl;
		facNo = fathIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv2.v_chromosome1[j].factory_number =facNo;
		//cout << "chIndiv2.v_chromosome1[j].factory_number = " << chIndiv2.v_chromosome1[j].factory_number << endl;
	}
	for (int j = cutpoint24; j < number_of_jobs1; j++)
	{
		facNo =  mothIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv1.v_chromosome1[j].factory_number = facNo;
		//cout << "chIndiv1.v_chromosome1[j].factory_number = " << chIndiv1.v_chromosome1[j].factory_number << endl;
		facNo = fathIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv2.v_chromosome1[j].factory_number = facNo;
		//cout << "chIndiv2.v_chromosome1[j].factory_number = " << chIndiv2.v_chromosome1[j].factory_number << endl;
	}
	//补充作业信息
	for (int n = 0; n < number_of_jobs1; n++)
	{
		chIndiv1.v_chromosome1[n].job_number = n + 1;
		chIndiv2.v_chromosome1[n].job_number = n + 1;
	}
	//cout << endl;
	//cout << "交叉后两个子代的工厂序列：" << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << chIndiv1.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << chIndiv2.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	//system("pause");

	//step2:对作业序列执行循环交叉
	int position_number = number_of_jobs1 + rand() % number_of_jobs1;
	//cout << "position_number = " << position_number << endl;
	int start_job = fathIndiv.v_chromosome1[position_number].job_number;
	//cout << "start_job = " << start_job << endl;
	int fa_p_index = position_number;
	vector<int>v_fa_p_index;//储存父亲染色体上 环 上的基因位置
	v_fa_p_index.push_back(fa_p_index);
	int next_job = mothIndiv.v_chromosome1[fa_p_index].job_number;
	//cout << "next_job = " << next_job << endl;
	while (next_job != start_job)//寻找 环上的job的位置索引
	{
		for (int j = number_of_jobs1; j < 2 *number_of_jobs1; j++)
		{
			if (fathIndiv.v_chromosome1[j].job_number == next_job)
			{
				fa_p_index = j;
				v_fa_p_index.push_back(fa_p_index);
				//cout << "fa_p_index = " << fa_p_index << endl;
			}
		}
		next_job = mothIndiv.v_chromosome1[fa_p_index].job_number;
		//cout << "next_job = " << next_job << endl;
	}

	for (int j = 0; j < v_fa_p_index.size(); j++)//子代1保留父亲环上的基因
	{
		int fa_index = v_fa_p_index[j];
		//cout << "fa_index = " << fa_index << endl;
		chIndiv1.v_chromosome1[fa_index].job_number = fathIndiv.v_chromosome1[fa_index].job_number;
	}

	vector<int>v_fa_jobs;//获取父亲染色体上非环的基因
	bool pd_value;
	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)
	{
		for (int k = 0; k < v_fa_p_index.size(); k++)
		{
			int fa_p_index = v_fa_p_index[k];
			if (j != fa_p_index)
			{
				pd_value = true;
			}
			else
			{
				pd_value = false;
				break;
			}
		}
		if (pd_value == true)
		{
			v_fa_jobs.push_back(fathIndiv.v_chromosome1[j].job_number);
		}
	}
	//cout << "父非环基因：" << endl;
	//for (int j = 0; j < v_fa_jobs.size(); j++)
	//{
	//	cout << v_fa_jobs[j] << " ";
	//}
	//cout << endl;


	vector<int>v_mo_jobs;//获取母亲染色体上非环上的基因
	bool panduan;
	panduan = false;
	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)
	{
		for (int k = 0; k < v_fa_p_index.size(); k++)
		{
			if (mothIndiv.v_chromosome1[j].job_number != fathIndiv.v_chromosome1[v_fa_p_index[k]].job_number)
			{
				panduan = true;
			}
			else
			{
				panduan = false;
				break;
			}
		}
		if (panduan == true)
		{
			v_mo_jobs.push_back(mothIndiv.v_chromosome1[j].job_number);
		}
	}
	//cout << "母非环基因：" << endl;
	//for (int j = 0; j < v_mo_jobs.size(); j++)
	//{
	//	cout << v_mo_jobs[j] << " ";
	//}
	//cout << endl;

	int p_index = 0;
	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)//对子代1上缺少的非环基因进行赋值：来自母亲的非环基因
	{
		if (chIndiv1.v_chromosome1[j].job_number == 0)
		{
			chIndiv1.v_chromosome1[j].job_number = v_mo_jobs[p_index];
			p_index++;
			//cout << "p_index = " << p_index << endl;
		}
	}

	for (int j = 0; j < v_fa_p_index.size(); j++)//子代2保留母亲环上的基因
	{
		int fa_index = v_fa_p_index[j];
		chIndiv2.v_chromosome1[fa_index].job_number = mothIndiv.v_chromosome1[fa_index].job_number;
	}
	p_index = 0;
	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)//对子代2上缺少的非环基因进行赋值：来自父亲的非环基因
	{
		if (chIndiv2.v_chromosome1[j].job_number == 0)
		{
			chIndiv2.v_chromosome1[j].job_number = v_fa_jobs[p_index];
			p_index++;
			//cout << "p_index = " << p_index << endl;
		}
	}
	//cout << "CX交叉后两个子代的作业序列：" << endl;
	//for (int n = number_of_jobs1; n < 2*number_of_jobs1; n++)
	//{
	//	cout << chIndiv1.v_chromosome1[n].job_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
	//{
	//	cout << chIndiv2.v_chromosome1[n].job_number << " ";
	//}
	//cout << endl;
	vector<int>().swap(v_fa_p_index);
	vector<int>().swap(v_mo_jobs);
	vector<int>().swap(v_fa_jobs);
	//system("pause");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//cout << "父亲的工序和机器序列信息：" << endl;
	//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
	//{
	//	cout << fathIndiv.v_chromosome2[n].operation_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs2 * number_of_operations; n < fathIndiv.v_chromosome2.size(); n++)
	//{
	//	cout << fathIndiv.v_chromosome2[n].machine_number << " ";
	//}
	//cout << endl;

	//cout << "母亲的工序和机器信息：" << endl;
	//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
	//{
	//	cout << mothIndiv.v_chromosome2[n].operation_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs2 * number_of_operations; n < mothIndiv.v_chromosome2.size(); n++)
	//{
	//	cout << mothIndiv.v_chromosome2[n].machine_number << " ";
	//}
	//cout << endl;


	vector <CChromosome>().swap(chIndiv1.v_chromosome2);//清空子代容器
	vector <CChromosome>().swap(chIndiv2.v_chromosome2);//清空子代容器
	////step3：工序向量部分，采用顺序交叉
	bool bt;
	int index;
	int cutpoint3, cutpoint4;//工序序列切点；
	int temp2, operNo;
	cutpoint3 = rand() % number_of_jobs2*number_of_operations;//取值范围为[number_of_jobs , number_of_jobs + total_operations_number)
	cutpoint4 = rand() % number_of_jobs2*number_of_operations;
	while (cutpoint3 == cutpoint4)//若两个切点相同
	{
		cutpoint3 = rand() % number_of_jobs2*number_of_operations;//则重新产生一个切点2
	}//我们 人为 让切点1在切点2的前面，直观且方便后续操作
	if (cutpoint3 > cutpoint4)//若切点1在切点2后面
	{
		temp2 = cutpoint3;
		cutpoint3 = cutpoint4;//则进行互换操作
		cutpoint4 = temp2;
	}
	//cout << "cutpoint3 = " << cutpoint3 << endl;
	//cout << "cutpoint4 = " << cutpoint4 << endl;
	for (int j = 0; j < number_of_jobs2*number_of_operations; j++)//子代个体初始化，一开始得先创建对象，再对对象的factory_number全部赋值为0
	{
		CChromosome	tt3;
		tt3.operation_number = 0;
		chIndiv1.v_chromosome2.push_back(tt3);
		CChromosome	tt4;
		tt4.operation_number = 0;
		chIndiv2.v_chromosome2.push_back(tt4);
	}

	for (int j = 0; j < cutpoint3; j++)//注意cutpoint3是开区间，这个作业号上的作业是取不到的；
	{
		operNo = fathIndiv.v_chromosome2[j].operation_number;//获取父亲染色体上[number_of_jobs,cutpoint3)区间的作业
		//cout << "operNo = " << operNo << endl;
		chIndiv1.v_chromosome2[j].operation_number = operNo;//将父亲[number_of_jobs,cutpoint3)上的作业 拷贝 给子代1相同位置
		//cout << "chIndiv1.v_chromosome[j].operation_number = " << chIndiv1.v_chromosome2[j].operation_number << endl;
		operNo = mothIndiv.v_chromosome2[j].operation_number;//获取母亲染色体上[number_of_jobs,cutpoint3)区间的作业
		//cout << "operNo = " << operNo << endl;
		chIndiv2.v_chromosome2[j].operation_number = operNo;//将母亲[number_of_jobs,cutpoint3)上的作业 拷贝 给子代2相同位置
		//cout << "chIndiv2.v_chromosome[j].operation_number = " << chIndiv2.v_chromosome2[j].operation_number << endl;
	}
	for (int j = cutpoint4; j < number_of_jobs2*number_of_operations; j++)
	{
		operNo = fathIndiv.v_chromosome2[j].operation_number;//获取父亲染色体上[number_of_jobs,cutpoint3)区间的作业
		//cout << "operNo = " << operNo << endl;
		chIndiv1.v_chromosome2[j].operation_number = operNo;//将父亲[number_of_jobs,cutpoint3)上的作业 拷贝 给子代1相同位置
		//cout << "chIndiv1.v_chromosome2[j].operation_number = " << chIndiv1.v_chromosome2[j].operation_number << endl;
		operNo = mothIndiv.v_chromosome2[j].operation_number;//获取母亲染色体上[number_of_jobs,cutpoint3)区间的作业
		//cout << "operNo = " << operNo << endl;
		chIndiv2.v_chromosome2[j].operation_number = operNo;//将母亲[number_of_jobs,cutpoint3)上的作业 拷贝 给子代2相同位置
		//cout << "chIndiv2.v_chromosome[j].operation_number = " << chIndiv2.v_chromosome2[j].operation_number << endl;
	}
	////以上 是将父母 两个切点 两侧的作业 直接拷贝 给子代1，子代2的相同位置
	////下面开始填充子代1和子代2[cutpoint3,cutpoint4)之间的作业，子代1该剩余部分从母亲那里获得；子代2：父亲
	index = cutpoint3;//从cutpoint3位置开始填充，若经循环后该位置被填充，则index++，继续填充下一个	
	vector<int> v_store_operation;//建立一个储存已经允许插入的工序，方便比较；因为当前工序不仅要和两端获取的基因比较，还要与已经插入的比较
	vector<int>().swap(v_store_operation);
	v_store_operation.push_back(0);//先放入一个0，方便后面比较，否则一开始是空的不能用size()循环
	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	{
		int times = 0;
		operNo = mothIndiv.v_chromosome2[j].operation_number;//将母亲中每个作业与子代1现有的作业比较;
		//cout << "operNo = " << operNo << endl;
		bt = false;
		//compare1
		for (int k = 0; k < cutpoint3; k++)//将当前母亲作业与子代1现有[number_of_jobs,cutpoint3)作业比较
		{
			if (operNo == chIndiv1.v_chromosome2[k].operation_number)//若存在一个相同的，累加这个工序的重复次数
			{
				times = times + 1;//记录该job的工序在左端的重复次数
				//cout << "times1 = " << times << endl;//times1,times2,times3区分在哪一块出现的重复
			}
		}
		//compare2
		for (int k = cutpoint4; k < number_of_jobs2 * number_of_operations; k++)
		{
			if (operNo == chIndiv1.v_chromosome2[k].operation_number)
			{
				times = times + 1;//记录该job的工序在端的重复次数
				//cout << "times2 = " << times << endl;
			}
		}
		//compare3
		for (int k = 0; k < v_store_operation.size(); k++)//不仅要和固定的两端比较，还要与刚插入的那些工序比较
		{
			if (operNo == v_store_operation[k])
			{
				times = times + 1;
				//cout << "times3 = " << times << endl;
			}
		}
		//判断
		if (times == number_of_operations)//若该工序已经出现3次
		{
			bt = true;
			continue;//要continue,进行下一个job的比较
		}
		//抉择
		if (bt == false)//若一直false，未出现true，说明该工序还未出现3次
		{
			chIndiv1.v_chromosome2[index].operation_number = operNo;
			v_store_operation.push_back(operNo);
			//cout << "chIndiv1.v_chromosome[index].operation_number=" << chIndiv1.v_chromosome2[index].operation_number << endl;
			index++;//此时原cutpoint1已经被填充了，故++，继续填充下一个位置
		}
	}//以上完成子代1[cutpoint3,cutpoint4)位置作业的填充，从母亲获得。
	//system("pause");
	index = cutpoint3;
	vector<int>().swap(v_store_operation);
	v_store_operation.push_back(0);//先放入一个0，方便后面比较，否则一开始是空的不能用size()循环
	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	{
		int times = 0;
		operNo = fathIndiv.v_chromosome2[j].operation_number;//将母亲中每个作业与子代1现有的作业比较;
		//cout << "operNo = " << operNo << endl;
		bt = false;
		//compare1
		for (int k = 0; k < cutpoint3; k++)//将当前母亲作业与子代1现有[number_of_jobs,cutpoint3)作业比较
		{
			if (operNo == chIndiv2.v_chromosome2[k].operation_number)//若存在一个相同的，累加这个工序的重复次数
			{
				times = times + 1;//记录该job的工序在左端的重复次数
				//cout << "times1 = " << times << endl;//times1,times2,times3区分在哪一块出现的重复
			}
		}
		//compare2
		for (int k = cutpoint4; k < number_of_jobs2 * number_of_operations; k++)
		{
			if (operNo == chIndiv2.v_chromosome2[k].operation_number)
			{
				times = times + 1;
				//cout << "times2 = " << times << endl;
			}
		}
		//compare3
		for (int k = 0; k < v_store_operation.size(); k++)//不仅要和固定的两端比较，还要与刚插入的那些工序比较
		{
			if (operNo == v_store_operation[k])
			{
				times = times + 1;
				//cout << "times3 = " << times << endl;
			}
		}
		//判断
		if (times == number_of_operations)//若该工序已经出现3次
		{
			bt = true;
			continue;//要continue,进行下一个job的比较
		}
		//抉择
		if (bt == false)//若一直false，未出现true，说明该工序还未出现3次
		{
			chIndiv2.v_chromosome2[index].operation_number = operNo;
			v_store_operation.push_back(operNo);
			//cout << "chIndiv2.v_chromosome2[index].operation_number=" << chIndiv2.v_chromosome2[index].operation_number << endl;
			index++;//此时原cutpoint1已经被填充了，故++，继续填充下一个位置
		}
	}//以上完成子代2[cutpoint3,cutpoint4)位置作业的填充，从父亲获得。

	//补充工序序列向量的job号信息和工序顺序信息
	for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	{
		chIndiv1.v_chromosome2[k].job_number = chIndiv1.v_chromosome2[k].operation_number;
		chIndiv2.v_chromosome2[k].job_number = chIndiv2.v_chromosome2[k].operation_number;
	}

	for (int k = 0; k < number_of_jobs2; k++)//判断是每个job的第几道工序
	{
		int current_job_number = k + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs2 * number_of_operations; c++)
		{
			if (current_job_number == chIndiv1.v_chromosome2[c].job_number)
			{
				count = count + 1;
				chIndiv1.v_chromosome2[c].operation_index = count;
			}
			continue;
		}
	}

	for (int k = 0; k < number_of_jobs2; k++)//判断是每个job的第几道工序
	{
		int current_job_number = k + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs2 * number_of_operations; c++)
		{
			if (current_job_number == chIndiv2.v_chromosome2[c].job_number)
			{
				count = count + 1;
				chIndiv2.v_chromosome2[c].operation_index = count;
			}
			continue;
		}
	}

	//////输出工序序列向量的信息
	//cout<<"交叉后两个子代的工序向量："<<endl;
	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv1.v_chromosome2[k].operation_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv1.v_chromosome2[k].job_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv1.v_chromosome2[k].operation_index << " ";
	//}
	//cout << endl << endl;

	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv2.v_chromosome2[k].operation_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv2.v_chromosome2[k].job_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv2.v_chromosome2[k].operation_index << " ";
	//}
	//cout << endl;
	//system("pause");


	//step4:机器向量部分，采用字符串
	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)//子代个体初始化，一开始得先创建对象，再对对象的machine_number全部赋值为0
	{
		CChromosome	tt5;
		tt5.machine_number = 0;
		chIndiv1.v_chromosome2.push_back(tt5);
		CChromosome	tt6;
		tt6.machine_number = 0;
		chIndiv2.v_chromosome2.push_back(tt6);
	}

	for (int k = number_of_jobs2 * number_of_operations; k < chIndiv1.v_chromosome2.size(); k++)
	{
		//随机产生一个0-1数，若该数=0，则取父亲基因，若该数=1，则取母亲基因。
		int rand_m_number1 = rand() % 2;
		//cout << "rand_number1 = " << rand_m_number1 << endl;
		if (rand_m_number1 == 0)
		{
			chIndiv1.v_chromosome2[k].machine_number = fathIndiv.v_chromosome2[k].machine_number;
		}
		else if (rand_m_number1 == 1)
		{
			chIndiv1.v_chromosome2[k].machine_number = mothIndiv.v_chromosome2[k].machine_number;
		}
	}
	for (int k = number_of_jobs2 * number_of_operations; k < chIndiv2.v_chromosome2.size(); k++)
	{
		//随机产生一个0-1数，若该数=0，则取父亲基因，若该数=1，则取母亲基因。
		int rand_m_number2 = rand() % 2;
		//cout << "rand_number2 = " << rand_m_number2 << endl;
		if (rand_m_number2 == 0)
		{
			chIndiv2.v_chromosome2[k].machine_number = fathIndiv.v_chromosome2[k].machine_number;
		}
		else if (rand_m_number2 == 1)
		{
			chIndiv2.v_chromosome2[k].machine_number = mothIndiv.v_chromosome2[k].machine_number;
		}
	}
	//cout << endl << endl;
	//补充机器向量的job信息
	int dis = 0;
	for (int j = 0; j < number_of_jobs2; j++)
	{
		for (int o = 0; o < number_of_operations; o++)
		{
			chIndiv1.v_chromosome2[o + dis + number_of_jobs2 * number_of_operations].job_number = j + 1;
			chIndiv2.v_chromosome2[o + dis + number_of_jobs2 * number_of_operations].job_number = j + 1;
		}
		dis = dis + number_of_operations;
	}
	//cout << endl;
	////输出机器向量的信息
	//cout << "交叉后两个子代的机器向量信息：" << endl;
	//for (int k = number_of_jobs2 * number_of_operations; k < chIndiv1.v_chromosome2.size(); k++)
	//{
	//	cout << chIndiv1.v_chromosome2[k].machine_number << " ";
	//}
	//cout << endl;
	//for (int k = number_of_jobs2 * number_of_operations; k < chIndiv2.v_chromosome2.size(); k++)
	//{
	//	cout << chIndiv2.v_chromosome2[k].machine_number << " ";
	//}
	//cout << endl << endl;

	//for (int k = number_of_jobs2 * number_of_operations; k < chIndiv1.v_chromosome2.size(); k++)
	//{
	//	cout << chIndiv1.v_chromosome2[k].job_number << " ";
	//}
	//cout << endl;
	//for (int k = number_of_jobs2 * number_of_operations; k < chIndiv2.v_chromosome2.size(); k++)
	//{
	//	cout << chIndiv2.v_chromosome2[k].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
	//以上FJSP工序向量、机器向量均求出。

	//cout << "子代1：" << endl;
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	cout << chIndiv1.v_chromosome1[j].factory_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs1; j < chIndiv1.v_chromosome1.size(); j++)
	//{
	//	cout << chIndiv1.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;

	//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
	//{
	//	cout << chIndiv1.v_chromosome2[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
	//{
	//	cout << chIndiv1.v_chromosome2[j].operation_index << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < chIndiv1.v_chromosome2.size(); j++)
	//{
	//	cout << chIndiv1.v_chromosome2[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < chIndiv1.v_chromosome2.size(); j++)
	//{
	//	cout << chIndiv1.v_chromosome2[j].job_number << " ";
	//}
	//cout << endl;
	//system("pause");

	//cout << "子代2：" << endl;
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	cout << chIndiv2.v_chromosome1[j].factory_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs1; j < chIndiv2.v_chromosome1.size(); j++)
	//{
	//	cout << chIndiv2.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;

	//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
	//{
	//	cout << chIndiv2.v_chromosome2[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
	//{
	//	cout << chIndiv2.v_chromosome2[j].operation_index << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < chIndiv2.v_chromosome2.size(); j++)
	//{
	//	cout << chIndiv2.v_chromosome2[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < chIndiv2.v_chromosome2.size(); j++)
	//{
	//	cout << chIndiv2.v_chromosome2[j].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}


void CGenetic::mutate(CIndividual& t, double rate)//对个体进行变异，rate是变异率；t是传进来的child1对象，在evovle中
{
	if (rand() / (RAND_MAX * 1.0) <= rate)   //产生一个随机数与rate比较判断是否进行变异，由于设置的是百分百变异，故肯定对该个体进行变异
	{
		//step1:对工厂向量，随机选中两个不同的点，然后进行交换
		int cutpoint3, cutpoint4;//工厂序列切点；
		int facNo1, facNo2;
		cutpoint3 = rand() % number_of_jobs1;//随机产生一个切点1，切点1的范围[0 , number_of_jobs-1]
		cutpoint4 = rand() % number_of_jobs1;//随机产生一个切点2，切点2的范围[0 , number_of_jobs-1]
		while (cutpoint3 == cutpoint4)//若两个切点相同
		{
			cutpoint4 = rand() % number_of_jobs1;//则重新产生一个切点2
		}
		facNo1 = t.v_chromosome1[cutpoint3].factory_number;
		facNo2 = t.v_chromosome1[cutpoint4].factory_number;
		while (facNo1 == facNo2)
		{
			cutpoint4 = rand() % number_of_jobs1;//则重新产生一个切点2
			facNo2 = t.v_chromosome1[cutpoint4].factory_number;
		}
		//cout << "cutpoint3 = " << cutpoint3 << endl;
		//cout << "cutpoint4 = " << cutpoint4 << endl;
		//cout << "facNo1 = " << facNo1 << endl;
		//cout << "facNo2 = " << facNo2 << endl;
		int temp_factory;
		temp_factory = t.v_chromosome1[cutpoint3].factory_number;
		t.v_chromosome1[cutpoint3].factory_number = t.v_chromosome1[cutpoint4].factory_number;
		t.v_chromosome1[cutpoint4].factory_number = temp_factory;
		////输出工厂分配向量的信息
		//for (int j = 0; j <number_of_jobs1; j++)
		//{
		//	cout << t.v_chromosome1[j].factory_number << " ";
		//}
		//cout << endl;
		//system("pause");

		//对这个传进来的个体开始进行变异
		//step2:对作业顺序向量，随机选中两个不同的点，然后进行翻转
		int cutpoint1, cutpoint2;//工厂序列切点；			
		cutpoint1 = number_of_jobs1 + rand() % number_of_jobs1;
		cutpoint2 = number_of_jobs1 + rand() % number_of_jobs1;
		while (cutpoint1 == cutpoint2)//若两个切点相同
		{
			cutpoint2 = number_of_jobs1 + rand() % number_of_jobs1;//则重新产生一个切点2
		}
		int temp_cut;
		if (cutpoint1 > cutpoint2)
		{
			temp_cut = cutpoint1;
			cutpoint1 = cutpoint2;
			cutpoint2 = temp_cut;
		}
		//cout << "cutpoint1 = " << cutpoint1 << endl;
		//cout << "cutpoint2 = " << cutpoint2 << endl;
		int jobNo;
		vector <int> v_job_part_list;
		vector <int>().swap(v_job_part_list);//把两点间的元素放在数组里，好使用reverse翻转
		for (int j = cutpoint1; j <= cutpoint2; j++)
		{
			jobNo = t.v_chromosome1[j].job_number;
			v_job_part_list.push_back(jobNo);
		}
		//for (int j = 0; j < v_job_part_list.size();j++)
		//{
		//	cout << v_job_part_list[j] << " ";
		//}
		//system("pause");
		reverse(v_job_part_list.begin(), v_job_part_list.end()); //对v_operation_part_list中的从v_operation_part_list.begin()（包括它）到v_operation_part_list.end()（包括它）的元素倒置，如v_operation_part_list中元素为1,2,3,4,倒置后为4,3,2,1
		//for (int j = 0; j < v_job_part_list.size(); j++)
		//{
		//	cout << v_job_part_list[j] << " ";
		//}
		//system("pause");
		int jobNo_o;
		for (int j = cutpoint1; j <= cutpoint2; j++)
		{
			jobNo_o = v_job_part_list[j - cutpoint1];
			//cout << "jobNo_o = " << jobNo_o << endl;
			t.v_chromosome1[j].job_number = jobNo_o;//job_number随之更新
		}
		//system("pause");
		////输出工序序列向量的信息
		////for (int k = number_of_jobs1; k < 2* number_of_jobs1; k++)
		////{
		////	cout << t.v_chromosome1[k].job_number << " ";
		////}
		////cout << endl;
		////system("pause");
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//step3:对工序向量，随机选中两个不同的点，然后进行翻转
		int cutpoint5, cutpoint6;//工厂序列切点；			
		cutpoint5 = rand() % (number_of_jobs2 * number_of_operations);
		cutpoint6 = rand() % (number_of_jobs2 * number_of_operations);
		while (cutpoint5 == cutpoint6)//若两个切点相同
		{
			cutpoint6 = rand() % (number_of_jobs2 * number_of_operations);//则重新产生一个切点2
		}
		int temp_cut2;
		if (cutpoint5 > cutpoint6)
		{
			temp_cut2 = cutpoint5;
			cutpoint5 = cutpoint6;
			cutpoint6 = temp_cut2;
		}
		//cout << "cutpoint5 = " << cutpoint5 << endl;
		//cout << "cutpoint6 = " << cutpoint6 << endl;
		int operNo;
		vector <int> v_oper_part_list;
		vector <int>().swap(v_oper_part_list);//把两点间的元素放在数组里，好使用reverse翻转
		for (int j = cutpoint5; j <= cutpoint6; j++)
		{
			operNo = t.v_chromosome2[j].operation_number;
			v_oper_part_list.push_back(operNo);
		}
		//for (int j = 0; j < v_oper_part_list.size(); j++)
		//{
		//	cout << v_oper_part_list[j] << " ";
		//}
		//system("pause");
		reverse(v_oper_part_list.begin(), v_oper_part_list.end()); //对v_operation_part_list中的从v_operation_part_list.begin()（包括它）到v_operation_part_list.end()（包括它）的元素倒置，如v_operation_part_list中元素为1,2,3,4,倒置后为4,3,2,1
		//for (int j = 0; j < v_oper_part_list.size(); j++)
		//{
		//	cout << v_oper_part_list[j] << " ";
		//}
		//system("pause");
		int jobNo_j;
		for (int j = cutpoint5; j <= cutpoint6; j++)
		{
			jobNo_j = v_oper_part_list[j - cutpoint5];
			//cout << "jobNo_j = " << jobNo_j << endl;
			t.v_chromosome2[j].operation_number = jobNo_j;
			t.v_chromosome2[j].job_number = jobNo_j;//job_number随之更新
		}
		//system("pause");

		//operation_index随之更新
		for (int k = 0; k < number_of_jobs2; k++)//判断是每个job的第几道工序
		{
			int current_job_number = k + 1;
			int count = 0;
			for (int c = 0; c < number_of_jobs2 * number_of_operations; c++)
			{
				if (current_job_number == t.v_chromosome2[c].job_number)
				{
					count = count + 1;
					t.v_chromosome2[c].operation_index = count;
				}
				continue;
			}
		}
		//cout << endl;
		////输出工序序列向量的信息
		//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
		//{
		//	cout << t.v_chromosome2[k].operation_number << " ";
		//}
		//cout << endl;
		//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
		//{
		//	cout << t.v_chromosome2[k].operation_index << " ";
		//}
		//cout << endl;
		//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
		//{
		//	cout << t.v_chromosome2[k].job_number << " ";
		//}
		//cout << endl;
		//system("pause");

		//////step4:对机器向量，每个job的每道工序的可选机器从可选机器集中随机产生；不用更新job_number//这种效果不好
		//for (int j = 0; j < number_of_jobs2; j++)
		//{
		//	for (int o = 0; o < number_of_operations; o++)
		//	{
		//		int operation_machine_size = v_available_machines[j][o].size();
		//		int rand_machine_number_index = rand() % operation_machine_size;
		//		int rand_machine_number = v_available_machines[j][o][rand_machine_number_index];
		//		//cout << "rand_machine_number = " << rand_machine_number << endl;
		//		int index = number_of_jobs2 * number_of_operations + j * number_of_operations +  o;
		//		//cout << "index = " << index << endl;
		//		t.v_chromosome2[index].machine_number = rand_machine_number;
		//		t.v_chromosome2[number_of_jobs2 * number_of_operations + j + o].job_number = j + 1;
		//	}
		//}
		
		////step4:对机器向量，随机选1个工序然后更换其机器编号
		////随机选中一个工序的位置索引获取其工序编号和工序序号编号
		int ls = rand() % (number_of_jobs2 * number_of_operations);
		//cout << "ls = " << ls << endl;
		int ls_operation = t.v_chromosome2[ls].operation_number;
		//cout << "ls_operation =" << ls_operation << endl;
		int ls_operation_xuhao = t.v_chromosome2[ls].operation_index;
		//cout << "ls_operation_xuhao =" << ls_operation_xuhao << endl;
		//获取该job的该道工序的可使用机器数量
		int operation_machine_size = v_available_machines[ls_operation - 1][ls_operation_xuhao - 1].size();
		//cout << "operation_machine_size = " << operation_machine_size << endl;
		if (operation_machine_size >= 2)
		{
			int rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			int rand_machine_number = v_available_machines[ls_operation - 1][ls_operation_xuhao - 1][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
			int index = number_of_jobs2 * number_of_operations + (ls_operation - 1) * number_of_operations + (ls_operation_xuhao - 1);
			//cout << "index = " << index << endl;
			int current_machine_number = t.v_chromosome2[index].machine_number;
			//cout << "current_machine_number =" << current_machine_number << endl;
			while (current_machine_number == rand_machine_number)
			{
				rand_machine_number_index = rand() % operation_machine_size;
				//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
				rand_machine_number = v_available_machines[ls_operation - 1][ls_operation_xuhao - 1][rand_machine_number_index];
				//cout << "rand_machine_number = " << rand_machine_number << endl;
			}
			t.v_chromosome2[index].machine_number = rand_machine_number;
		}
		//system("pause");
		//////输出机器向量的信息
		//for (int k = number_of_jobs2 * number_of_operations; k < t.v_chromosome2.size(); k++)
		//{
		//	cout << t.v_chromosome2[k].machine_number << " ";
		//}
		//cout << endl;
		//for (int k = number_of_jobs2 * number_of_operations; k < t.v_chromosome2.size(); k++)
		//{
		//	cout << t.v_chromosome2[k].job_number << " ";
		//}
		//cout << endl;
		////以上 各向量均完成变异
		//system("pause");
	}
	else//不变异
	{
		//cout << "不变异" << endl;
		t = t;
	}
	
	//cout << "变异后child个体：" << endl;
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
}