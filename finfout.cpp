#include <iomanip>
#include "Genetic.h"
#include "Individual.h"
#include "rankSequ.h"
#include "headfile.h"

void CGenetic::finData(char* filename)//输入数据（传入文件名filename）
{
	ifstream fin;//输入流
	int i;
	fin.open(filename);//打开 .\\data\\findex0-findex1.txt
	cout << filename << endl;

	if (!fin)
	{
		cout << "open the file failure when read in data." << endl;//读取数据时打开文件失败。
		cout << filename << endl;
		system("pause");
	}
	fin >> number_of_factories >> number_of_machines >> number_of_jobs1 >> number_of_operations>>number_of_machines>>number_of_jobs2;//输入 工厂数目，机器数目和作业数目2-10-3-5
	//cout << number_of_factories << " ";
	//cout << number_of_machines << " ";
	//cout << number_of_jobs1 << " ";
	//cout << number_of_operations << " ";
	//cout << number_of_machines << " ";
	//cout << number_of_jobs2 << endl<<endl;
	
	//DFSP加工时间
	p_b_flow_processing_time = new double**[number_of_factories];//是一个包含number_of_factories个元素的数组1
	for (int i = 0; i < number_of_factories; i++)
	{
		p_b_flow_processing_time[i] = new double*[number_of_machines];//数组1中 每个元素 都指向一个 包含number_of_machines个元素的数组2
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

	//DFSP单位机器加工成本
	p_unit_machine_cost1 = new double[number_of_machines];
	for (int i = 0; i < number_of_machines; i++)
	{
		fin >> p_unit_machine_cost1[i];
		//cout << p_unit_machine_cost1[i] <<" ";
	}
	//cout << endl;


	//FJSP加工时间
	p_b_fjsp_processing_time = new double**[number_of_operations];//是一个包含number_of_factories个元素的数组1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_b_fjsp_processing_time[i] = new double*[number_of_machines];//数组1中 每个元素 都指向一个 包含number_of_machines个元素的数组2
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


	//FJSP单位机器加工成本
	p_unit_machine_cost2 = new double[number_of_machines];
	for (int i = 0; i < number_of_machines; i++)
	{
		fin >> p_unit_machine_cost2[i];
		//cout << p_unit_machine_cost2[i] << " ";
	}
	//cout << endl<<endl<<endl;
	
	//每个零件每道工序的个性化因子
	p_degree = new double*[number_of_operations];//是一个包含number_of_factories个元素的数组1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_degree[i] = new double[number_of_jobs2];//数组1中 每个元素 都指向一个 包含number_of_machines个元素的数组2
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

	//每个零件每道工序的设计时间
	p_b_fjsp_design_time = new double*[number_of_operations];//是一个包含number_of_factories个元素的数组1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_b_fjsp_design_time[i] = new double[number_of_jobs2];//数组1中 每个元素 都指向一个 包含number_of_machines个元素的数组2
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

	//每个零件每道工序的设计成本
	p_unit_design_cost = new double*[number_of_operations];//是一个包含number_of_factories个元素的数组1
	for (int i = 0; i < number_of_operations; i++)
	{
		p_unit_design_cost[i] = new double[number_of_jobs2];//数组1中 每个元素 都指向一个 包含number_of_machines个元素的数组2
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

	fin.close();//结束输入
	//system("pause");
}

void CGenetic::foutData(char* filename, double & time)
{
	int i, archive_size;
	ofstream fout;
	fout.open(filename);//创建 .\\result_NSGAII\\result - findex0 - findex1\\findex2.txt
	if (!fout)
	{
		cout << "open the file failure when output the data" << endl;
		//cerr<<"in function: fout_data"<<endl;
		cout << filename << endl;
		system("pause");
	}
	//以上 将算法结果输出到filename文件
	archive_size = v_archive.size();//获取非支配解集合的长度，即有多少个元素
	fout << archive_size << endl;//非支配解数量
	for (i = 0; i < archive_size; i++)
	{
		fout << v_archive[i].v_objective_value[0] << " ";//输出当前非支配解的第1个目标值
		fout << v_archive[i].v_objective_value[1] << " ";//输出当前非支配解的第2个目标值
		fout << endl;
	}
	fout << time << endl;//运行时间
	//以上 输出 非支配解 的 所有目标值
	fout.close();	//结束输出

	
	//加工时间
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