#include "Event.h"
#include "Genetic.h"
#include "headfile.h"
#include "Individual.h"
#include "random.h"
#include "RankSequ.h"
#include "Chromosome.h"

//�㷨����������
void CGenetic::run()
{
	init_parameters();//��ʼ������
	//system("pause");
	generInitPopu();//��ʼ����Ⱥ(����������Ӧ�Ⱥ�����evaluate)
	//system("pause");
	while (current_number_of_fitness_evaluations < total_number_of_fitness_evaluations)
	{    
		iteration_num++;
		cluster();
		GWO();
		next_pop();	
		cout << current_number_of_fitness_evaluations << endl;
		cout << "iteration_num ="<<iteration_num << endl;//��ǰ��������
		int iter_number = 0.1 * (number_of_jobs * number_of_machines);
		//cout << "iter_number =" << iter_number << endl;
		
		if (iteration_num % iter_number == 0)//ÿ�����ִ��ILS��IGA
		{
			LS();
			LS2();
			next_pop2();	
		}
		//system("pause");
		////////�Ե�ǰ��Ⱥ�еĲ��ظ��ķ�֧������IGA����
		//if (iteration_num % 20 == 0)//ÿ�����ִ��ILS��IGA
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
	update_pareto();//�����֧�伯���еĽ�	
	system("pause");
}