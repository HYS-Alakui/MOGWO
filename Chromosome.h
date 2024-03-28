#pragma once
class CChromosome
{
private:
public:

	int job_number;//作业号取值范围是[1,number_of_jobs]
	int factory_number;//工厂号取值范围是[1,number_of_factories]
	int operation_number;//取值是[1,number_of_jobs]
	int operation_index;//判断是第几道工序,取值是[1,number_of_operations]
	int machine_number;

	vector <vector <int>> v_available_machines;
};