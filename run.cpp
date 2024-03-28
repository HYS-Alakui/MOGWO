#include "Event.h"
#include "Genetic.h"
#include "headfile.h"
#include "Individual.h"
#include "random.h"
#include "RankSequ.h"
#include "Chromosome.h"

//算法的运行流程
void CGenetic::run()
{
	init_parameters();//初始化参数
	//system("pause");
	generInitPopu();//初始化种群(包含评估适应度函数：evaluate)
	//system("pause");
	while (current_number_of_fitness_evaluations < total_number_of_fitness_evaluations)
	{    
		iteration_num++;
		cluster();
		GWO();
		next_pop();	
		cout << current_number_of_fitness_evaluations << endl;
		cout << "iteration_num ="<<iteration_num << endl;//当前迭代次数
		int iter_number = 0.1 * (number_of_jobs * number_of_machines);
		//cout << "iter_number =" << iter_number << endl;
		
		if (iteration_num % iter_number == 0)//每隔五代执行ILS和IGA
		{
			LS();
			LS2();
			next_pop2();	
		}
		//system("pause");
		////////对当前种群中的不重复的非支配解进行IGA搜索
		//if (iteration_num % 20 == 0)//每隔五代执行ILS和IGA
		//{
		//	rank_fix();
		//	//system("pause");
		//	IGA();
		//	//system("pause");
		//	next_pop2();
		//	//system("pause");
		//}
		////system("pause");
	}
	update_pareto();//输出非支配集合中的解	
	system("pause");
}