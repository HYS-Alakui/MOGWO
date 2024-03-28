#include <iomanip>
#include "Genetic.h"
#include "Individual.h"
#include "rankSequ.h"
#include "headfile.h"

void CGenetic::finData(char* filename)//�������ݣ������ļ���filename��
{
	ifstream fin;//������
	int i;
	fin.open(filename);//�� .\\data\\findex0-findex1.txt
	cout << filename << endl;

	if (!fin)
	{
		cout << "open the file failure when read in data." << endl;//��ȡ����ʱ���ļ�ʧ�ܡ�
		cout << filename << endl;
		system("pause");
	}
	fin >> number_of_factories >> number_of_machines >> number_of_jobs1 >> number_of_operations>>number_of_machines>>number_of_jobs2;//���� ������Ŀ��������Ŀ����ҵ��Ŀ2-10-3-5
	//cout << number_of_factories << " ";
	//cout << number_of_machines << " ";
	//cout << number_of_jobs1 << " ";
	//cout << number_of_operations << " ";
	//cout << number_of_machines << " ";
	//cout << number_of_jobs2 << endl<<endl;
	
	//DFSP�ӹ�ʱ��
	p_b_flow_processing_time = new double**[number_of_factories];//��һ������number_of_factories��Ԫ�ص�����1
	for (int i = 0; i < number_of_factories; i++)
	{
		p_b_flow_processing_time[i] = new double*[number_of_machines];//����1�� ÿ��Ԫ�� ��ָ��һ�� ����number_of_machines��Ԫ�ص�����2
		for (int j = 0; j < number_of_machines; j++)
		{
			p_b_flow_processing_time[i][j] = new double[number_of_jobs1];
		}
	}

	for (int i = 0; i < number_of_factories; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			for (int k = 0; k < number_of_jobs1; k++)
			{
				fin >> p_b_flow_processing_time[i][j][k];
			}
		}
	}
	//for (int i = 0; i < number_of_factories; i++)
	//{
	//	for (int j = 0; j < number_of_machines; j++)
	//	{
	//		for (int k = 0; k < number_of_jobs1; k++)
	//		{
	//			cout<< left << setw(6) << p_b_flow_processing_time[i][j][k]<<" ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	//DFSP��λ�����ӹ��ɱ�
	p_unit_machine_cost1 = new double[number_of_machines];
	for (int i = 0; i < number_of_machines; i++)
	{
		fin >> p_unit_machine_cost1[i];
		//cout << p_unit_machine_cost1[i] <<" ";
	}
	//cout << endl;


	//FJSP�ӹ�ʱ��
	p_b_fjsp_processing_time = new double**[number_of_operations];//��һ������number_of_factories��Ԫ�ص�����1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_b_fjsp_processing_time[i] = new double*[number_of_machines];//����1�� ÿ��Ԫ�� ��ָ��һ�� ����number_of_machines��Ԫ�ص�����2
		for (int j = 0; j < number_of_machines; j++)
		{
			p_b_fjsp_processing_time[i][j] = new double[number_of_jobs2];
		}
	}
	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			for (int k = 0; k < number_of_jobs2; k++)
			{
				fin >> p_b_fjsp_processing_time[i][j][k];
			}
		}
	}
	//for (int i = 0; i < number_of_operations; i++)
	//{
	//	for (int j = 0; j < number_of_machines; j++)
	//	{
	//		for (int k = 0; k < number_of_jobs2; k++)
	//		{
	//			cout << left << setw(6) << p_b_fjsp_processing_time[i][j][k] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//cout << endl;


	//FJSP��λ�����ӹ��ɱ�
	p_unit_machine_cost2 = new double[number_of_machines];
	for (int i = 0; i < number_of_machines; i++)
	{
		fin >> p_unit_machine_cost2[i];
		//cout << p_unit_machine_cost2[i] << " ";
	}
	//cout << endl<<endl<<endl;
	
	//ÿ�����ÿ������ĸ��Ի�����
	p_degree = new double*[number_of_operations];//��һ������number_of_factories��Ԫ�ص�����1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_degree[i] = new double[number_of_jobs2];//����1�� ÿ��Ԫ�� ��ָ��һ�� ����number_of_machines��Ԫ�ص�����2
	}
	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_jobs2; j++)
		{
			fin >> p_degree[i][j];
		}
	}
	//for (int i = 0; i < number_of_operations; i++)
	//{
	//	for (int j = 0; j < number_of_jobs2; j++)
	//	{
	//		cout << left << setw(6) << p_degree[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	//ÿ�����ÿ����������ʱ��
	p_b_fjsp_design_time = new double*[number_of_operations];//��һ������number_of_factories��Ԫ�ص�����1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_b_fjsp_design_time[i] = new double[number_of_jobs2];//����1�� ÿ��Ԫ�� ��ָ��һ�� ����number_of_machines��Ԫ�ص�����2
	}
	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_jobs2; j++)
		{
			fin >> p_b_fjsp_design_time[i][j];
		}
	}
	//for (int i = 0; i < number_of_operations; i++)
	//{
	//	for (int j = 0; j < number_of_jobs2; j++)
	//	{
	//		cout << left << setw(6) << p_b_fjsp_design_time[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	//ÿ�����ÿ���������Ƴɱ�
	p_unit_design_cost = new double*[number_of_operations];//��һ������number_of_factories��Ԫ�ص�����1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_unit_design_cost[i] = new double[number_of_jobs2];//����1�� ÿ��Ԫ�� ��ָ��һ�� ����number_of_machines��Ԫ�ص�����2
	}
	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_jobs2; j++)
		{
			fin >> p_unit_design_cost[i][j];
		}
	}
	//for (int i = 0; i < number_of_operations; i++)
	//{
	//	for (int j = 0; j < number_of_jobs2; j++)
	//	{
	//		cout << left << setw(6) << p_unit_design_cost[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;

	fin.close();//��������
	//system("pause");
}

void CGenetic::foutData(char* filename, double & time)
{
	int i, archive_size;
	ofstream fout;
	fout.open(filename);//���� .\\result_NSGAII\\result - findex0 - findex1\\findex2.txt
	if (!fout)
	{
		cout << "open the file failure when output the data" << endl;
		//cerr<<"in function: fout_data"<<endl;
		cout << filename << endl;
		system("pause");
	}
	//���� ���㷨��������filename�ļ�
	archive_size = v_archive.size();//��ȡ��֧��⼯�ϵĳ��ȣ����ж��ٸ�Ԫ��
	fout << archive_size << endl;//��֧�������
	for (i = 0; i < archive_size; i++)
	{
		fout << v_archive[i].v_objective_value[0] << " ";//�����ǰ��֧���ĵ�1��Ŀ��ֵ
		fout << v_archive[i].v_objective_value[1] << " ";//�����ǰ��֧���ĵ�2��Ŀ��ֵ
		fout << endl;
	}
	fout << time << endl;//����ʱ��
	//���� ��� ��֧��� �� ����Ŀ��ֵ
	fout.close();	//�������

	
	//�ӹ�ʱ��
	for (int i = 0; i < number_of_factories; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			delete[] p_b_flow_processing_time[i][j];
		}
		delete[] p_b_flow_processing_time[i];
	}
	delete p_b_flow_processing_time;

	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			delete[] p_b_fjsp_processing_time[i][j];
		}
		delete[] p_b_fjsp_processing_time[i];
	}
	delete[] p_b_fjsp_processing_time;

	delete[] p_unit_machine_cost1;
	delete[] p_unit_machine_cost2;

	for (int i = 0; i < number_of_operations; i++)
	{
		delete[] p_degree[i];
	}
	delete[] p_degree;
	

	for (int i = 0; i < number_of_operations; i++)
	{
		delete[] p_b_fjsp_design_time[i];
	}
	delete[] p_b_fjsp_design_time;

	for (int i = 0; i < number_of_operations; i++)
	{
		delete[] p_unit_design_cost[i];
	}
	delete[] p_unit_design_cost;	

	for (int i = 0; i < number_of_operations; i++)
	{
		for (int j = 0; j < number_of_machines; j++)
		{
			delete[] p_c_fjsp_processing_time[i][j];
		}
		delete[] p_c_fjsp_processing_time[i];
	}
	delete[] p_c_fjsp_processing_time;	
}