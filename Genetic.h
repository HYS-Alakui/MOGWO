#include "Individual.h"
#include "RankSequ.h"
#include "headfile.h"
#include "Event.h"
#include "Entity.h"
#include "Job.h"
#include "Chromosome.h"

#ifndef _SYSTEMENGINEERINGINSTITUTE_
#define _SYSTEMENGINEERINGINSTITUTE_

class CGenetic//������ ����Ϊ CGenetic ��Ĳ�֣���ͷ�ļ���ɾ��������ʵ�ֲ��֣�ֻ������������������Դ�ļ���ֻ���º�����ʵ�ֲ���
{
private:
	//�㷨�����Ҫ����ı���
	vector <CIndividual> v_Chromo;//��Ⱥ ����
	vector <CIndividual> v_Chromo_temp;//��Ⱥ ����
	vector <CRankSequ> v_rankSequ;//����ֲ� ����
	vector <CIndividual> v_new_individuals;//��һ����Ⱥ����
	vector <CIndividual> v_new_individuals_temp;//��ʱ��ѽ���Ⱥ
	vector <CIndividual> v_KLS_individuals;
	vector <CIndividual> v_LS2_individuals;
	vector <CIndividual> v_LS2_individuals_temp;
	vector <CIndividual> v_KLS2_individuals;
	vector <vector<vector <int>>> v_available_machines;//ÿ��job��ÿ��operation�Ŀ��û�����
	vector <vector<CRankSequ>> v_cluster;//����ÿ���֧���ĸ���
	vector <CIndividual> v_archive;//��֧��⼯ ����
	//vector <CIndividual> v_omega_individuals;//�洢��ǰ��Ⱥ�еķ�֧����壨���أ�
	//vector <CIndividual> v_Omega_individuals;//�洢��ǰ��Ⱥ�в��ظ��ķ�֧�����
	//vector <CIndividual> v_Omega_individuals_temp;
	//vector <CIndividual> v_iga_individuals;

	int number_of_individuals;//��Ⱥ��ģ
	int iteration_num;
	double mutProb;
	int cluster_number;
	double time1;
	int number_of_objectives; //Ŀ����Ŀ
	int number_of_factories;//������Ŀ
	int number_of_machines;//������Ŀ
	int number_of_jobs; //��ҵ��Ŀ
	int number_of_jobs1; //��ҵ��Ŀ
	int number_of_jobs2; //��ҵ��Ŀ
	int number_of_operations;//ÿ��job�Ĺ�����Ŀ
	double current_number_of_fitness_evaluations;//��ǰ��������
	double total_number_of_fitness_evaluations;//ֹͣ����������Ӧ����������
	double *** p_b_flow_processing_time;//ÿ����׼�����ڷֲ�ʽ��ˮ����ÿ������ÿ̨�����ϵļӹ�ʱ��
	double *** p_b_fjsp_processing_time;//ÿ���Ǳ�׼������������ҵ����ÿ������ÿ̨�����ϵļӹ�ʱ��
	int *** p_c_fjsp_processing_time;//ÿ���Ǳ�׼������������ҵ����ÿ������ÿ̨�����ϵĶ��Ƽӹ�ʱ��
	double *p_unit_machine_cost1;//��λʱ������ӹ��ɱ�
	double *p_unit_machine_cost2;//��λʱ������ӹ��ɱ�
	double **p_degree;//��λʱ������ӹ��ɱ�
	double **p_b_fjsp_design_time;//ÿ���Ǳ�׼������������ҵ����ÿ�������ϵ����ʱ��
	double **p_unit_design_cost;//��λʱ������ӹ��ɱ�
	double **p_nonpart_o_design_cost;//ÿ���Ǳ�׼����ÿ���������Ƴɱ�
	double *p_nonpart_design_time;//ÿ���Ǳ�׼�������ʱ��	
	double *p_nonpart_design_cost;//ÿ���Ǳ�׼�������ʱ��	
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
	  void finData(char* filename);//�����������finfout.cpp�У���main.cpp�У�ͨ������ �������Instance����ΪfinData() Ϊ�� ���Լ��������� ��ֵ
	  void run();//���к���
	  void init_parameters();//��ʼ��������������init.cpp��
	  void generInitPopu();//��ʼ����Ⱥ����,��init.cpp��
	  void randomWay(CIndividual& t);//����һ���������ĺ�������init.cpp��
	  void assign(CIndividual& t);
	  void evaluate_DFSP(CIndividual& t);//������Ӧ�Ⱥ���
	  void evaluate_FJSP(CIndividual& t);//������Ӧ�Ⱥ���
	  void evaluate(CIndividual& t);//������Ӧ�Ⱥ���
	  void cluster();//�ִ�
	  void domRelation(const CIndividual& A, const CIndividual& B, int& domRel);//�жϸ���֧���ϵ��������genetic.cpp��
	  void GWO();
	  void crossover(CIndividual& fathIndiv, CIndividual& mothIndiv, CIndividual& chIndiv1, CIndividual& chIndiv2);//���溯��
	  void mutate(CIndividual& t, double rate);//���캯�� PS����Ҫע����ǽ���ͱ��춼�Ƕ������еĸ�����в���
	  void LS();//������Ⱥ�еĸ���ִ�л��ڹؼ�·���ľֲ�����
	  void LS2();//�Ի��ڹؼ�·���ֲ������������Ⱥ�ٽ���������ּ���Ż��ڶ���Ŀ��
	  void generate_newindividual1(CIndividual& t1, CIndividual& t2);//�ֲ����������¸���
	  void generate_newindividual2(CIndividual& t1, CIndividual& t2);//�ֲ����������¸���
	  void next_pop();
	  void crodiversity(vector <CRankSequ>& v_rankSequ, int& start, int& end);//ӵ��������������genetic.cpp��
	  void select();//��2N������ѡ��N�����庯��
	  //void rank_fix();
	  //void IGA();
	  void select2();
	  void next_pop2();
	  void update_pareto();
	  void foutData(char* filename, double & time);//���뺯��,��finfout.cpp�У���main.cpp�У�ͨ������ �������Instance����ΪfoutData() Ϊ�� ���Լ�Ŀ��ֵ ��ֵ	 
};

#endif
