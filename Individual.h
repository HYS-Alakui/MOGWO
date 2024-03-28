#include "headfile.h"
#include "Chromosome.h"

#ifndef _INFORMATIONCOLLEAGE_
#define _INFORMATIONCOLLEAGE_

class CIndividual//定义一个类 类名为CIndividual
{
private:
public:
	vector <CChromosome> v_chromosome1;          //保存每个对象（个体）具体解的容器，比如第一个对象的解是12345，第二个对象的解是54321
	vector <CChromosome> v_chromosome2;

	vector <vector <int>> v_factory_job_assignment;
	vector <vector <int>> v_job_assignment;

	vector<vector<vector<double> > >factory_machine_job_starttime;//工厂内机器上作业的开始时间
	vector<vector<vector<double> > >factory_machine_job_finishtime;//工厂内机器上作业的结束时间

	vector<int>critical_path_operation;//DFSP的关键路径上涉及的操作
	vector<int>critical_path_machine;//DFSP的关键路径上涉及的操作对应的机器

	vector<int>Job_C;//关键路径的作业（正）
	vector<int>Operation_C;//关键路径作业的工序号（正）
	vector<int>Machine_C;//关键路径作业的工序所在的机器（正）,机器号-1；

	vector<int>Keymachine_Operation;//关键机器上的工序
	vector<int>Keymachine_Operation_Xuhao;//关键机器上的工序序号

	vector <double> v_objective_value; //创建一个保存 每个对象 的 目标值 的 容器
	vector <int> v_job_list;//创建一个保存 每个对象 的 作业序列 的 容器
	vector <int> v_factory_list;//创建一个保存 每个对象 的 作业序列 的 容器	

	int rank;                          //排序值 rank越小越被选中进入下一代种群
	int domination_count;              //该个体被其他个体支配的数量v_dominationSet
	vector <int> v_dominationSet;      //该个体支配其他个体的集合 创建一个容器（动态数组），容器名是v_dominationSet

	int key_cell;
	int key_factory_index;//最佳工厂
	int key_machine_index;//最佳机器
	double DFSP_makespan_value;
	double FJSP_makespan_value;
};
#endif