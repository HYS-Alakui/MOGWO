#pragma once
class CChromosome
{
private:
public:

	int job_number;//��ҵ��ȡֵ��Χ��[1,number_of_jobs]
	int factory_number;//������ȡֵ��Χ��[1,number_of_factories]
	int operation_number;//ȡֵ��[1,number_of_jobs]
	int operation_index;//�ж��ǵڼ�������,ȡֵ��[1,number_of_operations]
	int machine_number;

	vector <vector <int>> v_available_machines;
};