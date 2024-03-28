#include <iomanip>
#include "Genetic.h"
#include "Individual.h"
#include "random.h"
#include <cmath>

void CGenetic::evaluate(CIndividual& t)//������Ӧ��
{
	current_number_of_fitness_evaluations++;
	vector <double>().swap(t.v_objective_value);//����ڴ棬��֤ÿ�� ���� �� Ŀ��ֵ���� Ϊ0
	makespan = 0;
	if (t.DFSP_makespan_value > t.FJSP_makespan_value)
	{
		makespan = t.DFSP_makespan_value;
		t.key_cell = 0;
	}
	else
	{
		makespan = t.FJSP_makespan_value;
		t.key_cell = 1;
	}
	//cout << "makespan=" << makespan << endl;
	t.v_objective_value.push_back(makespan);
	total_cost = 0;
	total_cost = total_production_cost1 + total_production_cost2 + total_design_cost;
	//cout << "total_cost=" << total_cost << endl;
	t.v_objective_value.push_back(total_cost);
}