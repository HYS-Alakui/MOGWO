#include "Individual.h"
#include "RankSequ.h"
#include "headfile.h"
#include "Event.h"
#include "Entity.h"
#include "Job.h"
#include "Chromosome.h"

#ifndef _SYSTEMENGINEERINGINSTITUTE_
#define _SYSTEMENGINEERINGINSTITUTE_

class CGenetic//定义类 类名为 CGenetic 类的拆分，在头文件中删掉函数的实现部分，只保留函数的声明；在源文件中只留下函数的实现部分
{
private:
	//算法层次需要定义的变量
	vector <CIndividual> v_Chromo;//种群 容器
	vector <CIndividual> v_Chromo_temp;//种群 容器
	vector <CRankSequ> v_rankSequ;//排序分层 容器
	vector <CIndividual> v_new_individuals;//新一代种群个体
	vector <CIndividual> v_new_individuals_temp;//临时最佳解种群
	vector <CIndividual> v_KLS_individuals;
	vector <CIndividual> v_LS2_individuals;
	vector <CIndividual> v_LS2_individuals_temp;
	vector <CIndividual> v_KLS2_individuals;
	vector <vector<vector <int>>> v_available_machines;//每个job的每个operation的可用机器集
	vector <vector<CRankSequ>> v_cluster;//储存每层非支配解的个体
	vector <CIndividual> v_archive;//非支配解集 容器
	//vector <CIndividual> v_omega_individuals;//存储当前种群中的非支配个体（含重）
	//vector <CIndividual> v_Omega_individuals;//存储当前种群中不重复的非支配个体
	//vector <CIndividual> v_Omega_individuals_temp;
	//vector <CIndividual> v_iga_individuals;

	int number_of_individuals;//种群规模
	int iteration_num;
	double mutProb;
	int cluster_number;
	double time1;
	int number_of_objectives; //目标数目
	int number_of_factories;//工厂数目
	int number_of_machines;//机器数目
	int number_of_jobs; //作业数目
	int number_of_jobs1; //作业数目
	int number_of_jobs2; //作业数目
	int number_of_operations;//每个job的工序数目
	double current_number_of_fitness_evaluations;//当前评估次数
	double total_number_of_fitness_evaluations;//停止条件：总适应度评估次数
	double *** p_b_flow_processing_time;//每个标准工件在分布式流水车间每个工厂每台机器上的加工时间
	double *** p_b_fjsp_processing_time;//每个非标准工件在柔性作业车间每道工序每台机器上的加工时间
	int *** p_c_fjsp_processing_time;//每个非标准工件在柔性作业车间每道工序每台机器上的定制加工时间
	double *p_unit_machine_cost1;//单位时间机器加工成本
	double *p_unit_machine_cost2;//单位时间机器加工成本
	double **p_degree;//单位时间机器加工成本
	double **p_b_fjsp_design_time;//每个非标准工件在柔性作业车间每道工序上的设计时间
	double **p_unit_design_cost;//单位时间机器加工成本
	double **p_nonpart_o_design_cost;//每个非标准件的每道工序的设计成本
	double *p_nonpart_design_time;//每个非标准件的设计时间	
	double *p_nonpart_design_cost;//每个非标准件的设计时间	
	int max_design_value;
	int best_size;

	double makespan;
	double total_cost;
	double total_production_cost1;
	double total_production_cost2;
	double DFSP_makespan;
	double FJSP_makespan;
	double total_design_cost;	

public:
	  void finData(char* filename);//输出函数，在finfout.cpp中；在main.cpp中，通过访问 具体对象Instance的行为finData() 为其 属性即算例参数 赋值
	  void run();//运行函数
	  void init_parameters();//初始化参数函数，在init.cpp中
	  void generInitPopu();//初始化种群函数,在init.cpp中
	  void randomWay(CIndividual& t);//产生一个随机个体的函数，在init.cpp中
	  void assign(CIndividual& t);
	  void evaluate_DFSP(CIndividual& t);//评估适应度函数
	  void evaluate_FJSP(CIndividual& t);//评估适应度函数
	  void evaluate(CIndividual& t);//评估适应度函数
	  void cluster();//分簇
	  void domRelation(const CIndividual& A, const CIndividual& B, int& domRel);//判断个体支配关系函数，在genetic.cpp中
	  void GWO();
	  void crossover(CIndividual& fathIndiv, CIndividual& mothIndiv, CIndividual& chIndiv1, CIndividual& chIndiv2);//交叉函数
	  void mutate(CIndividual& t, double rate);//变异函数 PS：需要注意的是交叉和变异都是对领域中的个体进行操作
	  void LS();//对新种群中的个体执行基于关键路径的局部搜索
	  void LS2();//对基于关键路径局部搜索后的新种群再进行搜索，旨在优化第二个目标
	  void generate_newindividual1(CIndividual& t1, CIndividual& t2);//局部搜索生成新个体
	  void generate_newindividual2(CIndividual& t1, CIndividual& t2);//局部搜索生成新个体
	  void next_pop();
	  void crodiversity(vector <CRankSequ>& v_rankSequ, int& start, int& end);//拥挤度排序函数，在genetic.cpp中
	  void select();//从2N个个体选择N个个体函数
	  //void rank_fix();
	  //void IGA();
	  void select2();
	  void next_pop2();
	  void update_pareto();
	  void foutData(char* filename, double & time);//输入函数,在finfout.cpp中；在main.cpp中，通过访问 具体对象Instance的行为foutData() 为其 属性即目标值 赋值	 
};

#endif
