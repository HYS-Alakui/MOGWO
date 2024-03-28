#include "headfile.h"
#include "Chromosome.h"

#ifndef _INFORMATIONCOLLEAGE_
#define _INFORMATIONCOLLEAGE_

class CIndividual//����һ���� ����ΪCIndividual
{
private:
public:
	vector <CChromosome> v_chromosome1;          //����ÿ�����󣨸��壩�����������������һ������Ľ���12345���ڶ�������Ľ���54321
	vector <CChromosome> v_chromosome2;

	vector <vector <int>> v_factory_job_assignment;
	vector <vector <int>> v_job_assignment;

	vector<vector<vector<double> > >factory_machine_job_starttime;//�����ڻ�������ҵ�Ŀ�ʼʱ��
	vector<vector<vector<double> > >factory_machine_job_finishtime;//�����ڻ�������ҵ�Ľ���ʱ��

	vector<int>critical_path_operation;//DFSP�Ĺؼ�·�����漰�Ĳ���
	vector<int>critical_path_machine;//DFSP�Ĺؼ�·�����漰�Ĳ�����Ӧ�Ļ���

	vector<int>Job_C;//�ؼ�·������ҵ������
	vector<int>Operation_C;//�ؼ�·����ҵ�Ĺ���ţ�����
	vector<int>Machine_C;//�ؼ�·����ҵ�Ĺ������ڵĻ���������,������-1��

	vector<int>Keymachine_Operation;//�ؼ������ϵĹ���
	vector<int>Keymachine_Operation_Xuhao;//�ؼ������ϵĹ������

	vector <double> v_objective_value; //����һ������ ÿ������ �� Ŀ��ֵ �� ����
	vector <int> v_job_list;//����һ������ ÿ������ �� ��ҵ���� �� ����
	vector <int> v_factory_list;//����һ������ ÿ������ �� ��ҵ���� �� ����	

	int rank;                          //����ֵ rankԽСԽ��ѡ�н�����һ����Ⱥ
	int domination_count;              //�ø��屻��������֧�������v_dominationSet
	vector <int> v_dominationSet;      //�ø���֧����������ļ��� ����һ����������̬���飩����������v_dominationSet

	int key_cell;
	int key_factory_index;//��ѹ���
	int key_machine_index;//��ѻ���
	double DFSP_makespan_value;
	double FJSP_makespan_value;
};
#endif