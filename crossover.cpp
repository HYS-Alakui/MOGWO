#include "headfile.h"
#include "Individual.h"
#include "Genetic.h"
#include "rankSequ.h"
#include "Chromosome.h"

void CGenetic::crossover(CIndividual& fathIndiv, CIndividual& mothIndiv, CIndividual& chIndiv1, CIndividual& chIndiv2)//����4�����󣺸��ף�ĸ�ף��Ӵ�1���Ӵ�2
{
	//cout << "���׵Ĺ�������ҵ������Ϣ��" << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << fathIndiv.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
	//{
	//	cout << fathIndiv.v_chromosome1[n].job_number << " ";
	//}
	//cout << endl;

	//cout << "ĸ�׵Ĺ�������ҵ������Ϣ��" << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << mothIndiv.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
	//{
	//	cout << mothIndiv.v_chromosome1[n].job_number << " ";
	//}
	//cout << endl;


	//cout << "�Ӵ���ʼ����" << endl;
	vector <CChromosome>().swap(chIndiv1.v_chromosome1);//����Ӵ�����
	vector <CChromosome>().swap(chIndiv2.v_chromosome1);//����Ӵ�����
	for (int j = 0; j < number_of_jobs1; j++)//�Ӵ������ʼ����һ��ʼ���ȴ��������ٶԶ����job_numberȫ����ֵΪ0
	{
		CChromosome	tt1;
		tt1.factory_number = 0;
		chIndiv1.v_chromosome1.push_back(tt1);
		CChromosome	tt2;
		tt2.factory_number = 0;
		chIndiv2.v_chromosome1.push_back(tt2);
	}
	for (int j = 0; j < number_of_jobs1; j++)//�Ӵ������ʼ����һ��ʼ���ȴ��������ٶԶ����factory_numberȫ����ֵΪ0
	{
		CChromosome	tt3;
		tt3.job_number = 0;
		chIndiv1.v_chromosome1.push_back(tt3);
		CChromosome	tt4;
		tt4.job_number = 0;
		chIndiv2.v_chromosome1.push_back(tt4);
	}

	////step1:�Թ�������ִ�о��Ƚ���
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	//�������һ��0-1����������=0����ȡ���׻���������=1����ȡĸ�׻���
	//	int rand_m_number1 = rand() % 2;
	//	//cout << "rand_number1 = " << rand_m_number1 << endl;
	//	if (rand_m_number1 == 0)
	//	{
	//		chIndiv1.v_chromosome1[j].factory_number = fathIndiv.v_chromosome1[j].factory_number;
	//	}
	//	else if (rand_m_number1 == 1)
	//	{
	//		chIndiv1.v_chromosome1[j].factory_number = mothIndiv.v_chromosome1[j].factory_number;
	//	}
	//}
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	//�������һ��0-1����������=0����ȡ���׻���������=1����ȡĸ�׻���
	//	int rand_m_number2 = rand() % 2;
	//	//cout << "rand_number2 = " << rand_m_number2 << endl;
	//	if (rand_m_number2 == 0)
	//	{
	//		chIndiv2.v_chromosome1[j].factory_number = fathIndiv.v_chromosome1[j].factory_number;
	//	}
	//	else if (rand_m_number2 == 1)
	//	{
	//		chIndiv2.v_chromosome1[j].factory_number = mothIndiv.v_chromosome1[j].factory_number;
	//	}
	//}
	//cout << "����������Ӵ��Ĺ������У�" << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << chIndiv1.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << chIndiv2.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	////������ҵ��Ϣ
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	chIndiv1.v_chromosome1[n].job_number = n + 1;
	//	chIndiv2.v_chromosome1[n].job_number = n + 1;
	//}
	//cout << endl;
	//system("pause");

	//step1:�Թ�������ִ�����㽻��
	int cutpoint23, cutpoint24, temp22, facNo;
	cutpoint23 = rand() % number_of_jobs1;
	cutpoint24 = rand() % number_of_jobs1;
	while (cutpoint23 == cutpoint24)//�������е���ͬ
	{
		cutpoint24 = rand() % number_of_jobs1;
	}
	if (cutpoint23 > cutpoint24)
	{
		temp22 = cutpoint23;
		cutpoint23 = cutpoint24;
		cutpoint24 = temp22;
	}
	//cout << "cutpoint23 = " << cutpoint23 << endl;
	//cout << "cutpoint24 = " << cutpoint24 << endl;
	for (int j = cutpoint23; j < cutpoint24; j++)
	{
		facNo = fathIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv1.v_chromosome1[j].factory_number = facNo;
		//cout << "chIndiv1.v_chromosome1[j].factory_number  = " << chIndiv1.v_chromosome1[j].factory_number << endl;
		facNo = mothIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv2.v_chromosome1[j].factory_number = facNo;
		//cout << "chIndiv2.v_chromosome1[j].factory_number  = " << chIndiv2.v_chromosome1[j].factory_number << endl;
	}
	for (int j = 0; j < cutpoint23; j++)
	{
		facNo =  mothIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv1.v_chromosome1[j].factory_number = facNo;
		//cout << "chIndiv1.v_chromosome1[j].factory_number = " << chIndiv1.v_chromosome1[j].factory_number << endl;
		facNo = fathIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv2.v_chromosome1[j].factory_number =facNo;
		//cout << "chIndiv2.v_chromosome1[j].factory_number = " << chIndiv2.v_chromosome1[j].factory_number << endl;
	}
	for (int j = cutpoint24; j < number_of_jobs1; j++)
	{
		facNo =  mothIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv1.v_chromosome1[j].factory_number = facNo;
		//cout << "chIndiv1.v_chromosome1[j].factory_number = " << chIndiv1.v_chromosome1[j].factory_number << endl;
		facNo = fathIndiv.v_chromosome1[j].factory_number;
		//cout << "facNo = " << facNo << endl;
		chIndiv2.v_chromosome1[j].factory_number = facNo;
		//cout << "chIndiv2.v_chromosome1[j].factory_number = " << chIndiv2.v_chromosome1[j].factory_number << endl;
	}
	//������ҵ��Ϣ
	for (int n = 0; n < number_of_jobs1; n++)
	{
		chIndiv1.v_chromosome1[n].job_number = n + 1;
		chIndiv2.v_chromosome1[n].job_number = n + 1;
	}
	//cout << endl;
	//cout << "����������Ӵ��Ĺ������У�" << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << chIndiv1.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	//for (int n = 0; n < number_of_jobs1; n++)
	//{
	//	cout << chIndiv2.v_chromosome1[n].factory_number << " ";
	//}
	//cout << endl;
	//system("pause");

	//step2:����ҵ����ִ��ѭ������
	int position_number = number_of_jobs1 + rand() % number_of_jobs1;
	//cout << "position_number = " << position_number << endl;
	int start_job = fathIndiv.v_chromosome1[position_number].job_number;
	//cout << "start_job = " << start_job << endl;
	int fa_p_index = position_number;
	vector<int>v_fa_p_index;//���游��Ⱦɫ���� �� �ϵĻ���λ��
	v_fa_p_index.push_back(fa_p_index);
	int next_job = mothIndiv.v_chromosome1[fa_p_index].job_number;
	//cout << "next_job = " << next_job << endl;
	while (next_job != start_job)//Ѱ�� ���ϵ�job��λ������
	{
		for (int j = number_of_jobs1; j < 2 *number_of_jobs1; j++)
		{
			if (fathIndiv.v_chromosome1[j].job_number == next_job)
			{
				fa_p_index = j;
				v_fa_p_index.push_back(fa_p_index);
				//cout << "fa_p_index = " << fa_p_index << endl;
			}
		}
		next_job = mothIndiv.v_chromosome1[fa_p_index].job_number;
		//cout << "next_job = " << next_job << endl;
	}

	for (int j = 0; j < v_fa_p_index.size(); j++)//�Ӵ�1�������׻��ϵĻ���
	{
		int fa_index = v_fa_p_index[j];
		//cout << "fa_index = " << fa_index << endl;
		chIndiv1.v_chromosome1[fa_index].job_number = fathIndiv.v_chromosome1[fa_index].job_number;
	}

	vector<int>v_fa_jobs;//��ȡ����Ⱦɫ���Ϸǻ��Ļ���
	bool pd_value;
	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)
	{
		for (int k = 0; k < v_fa_p_index.size(); k++)
		{
			int fa_p_index = v_fa_p_index[k];
			if (j != fa_p_index)
			{
				pd_value = true;
			}
			else
			{
				pd_value = false;
				break;
			}
		}
		if (pd_value == true)
		{
			v_fa_jobs.push_back(fathIndiv.v_chromosome1[j].job_number);
		}
	}
	//cout << "���ǻ�����" << endl;
	//for (int j = 0; j < v_fa_jobs.size(); j++)
	//{
	//	cout << v_fa_jobs[j] << " ";
	//}
	//cout << endl;


	vector<int>v_mo_jobs;//��ȡĸ��Ⱦɫ���Ϸǻ��ϵĻ���
	bool panduan;
	panduan = false;
	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)
	{
		for (int k = 0; k < v_fa_p_index.size(); k++)
		{
			if (mothIndiv.v_chromosome1[j].job_number != fathIndiv.v_chromosome1[v_fa_p_index[k]].job_number)
			{
				panduan = true;
			}
			else
			{
				panduan = false;
				break;
			}
		}
		if (panduan == true)
		{
			v_mo_jobs.push_back(mothIndiv.v_chromosome1[j].job_number);
		}
	}
	//cout << "ĸ�ǻ�����" << endl;
	//for (int j = 0; j < v_mo_jobs.size(); j++)
	//{
	//	cout << v_mo_jobs[j] << " ";
	//}
	//cout << endl;

	int p_index = 0;
	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)//���Ӵ�1��ȱ�ٵķǻ�������и�ֵ������ĸ�׵ķǻ�����
	{
		if (chIndiv1.v_chromosome1[j].job_number == 0)
		{
			chIndiv1.v_chromosome1[j].job_number = v_mo_jobs[p_index];
			p_index++;
			//cout << "p_index = " << p_index << endl;
		}
	}

	for (int j = 0; j < v_fa_p_index.size(); j++)//�Ӵ�2����ĸ�׻��ϵĻ���
	{
		int fa_index = v_fa_p_index[j];
		chIndiv2.v_chromosome1[fa_index].job_number = mothIndiv.v_chromosome1[fa_index].job_number;
	}
	p_index = 0;
	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)//���Ӵ�2��ȱ�ٵķǻ�������и�ֵ�����Ը��׵ķǻ�����
	{
		if (chIndiv2.v_chromosome1[j].job_number == 0)
		{
			chIndiv2.v_chromosome1[j].job_number = v_fa_jobs[p_index];
			p_index++;
			//cout << "p_index = " << p_index << endl;
		}
	}
	//cout << "CX����������Ӵ�����ҵ���У�" << endl;
	//for (int n = number_of_jobs1; n < 2*number_of_jobs1; n++)
	//{
	//	cout << chIndiv1.v_chromosome1[n].job_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs1; n < 2 * number_of_jobs1; n++)
	//{
	//	cout << chIndiv2.v_chromosome1[n].job_number << " ";
	//}
	//cout << endl;
	vector<int>().swap(v_fa_p_index);
	vector<int>().swap(v_mo_jobs);
	vector<int>().swap(v_fa_jobs);
	//system("pause");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//cout << "���׵Ĺ���ͻ���������Ϣ��" << endl;
	//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
	//{
	//	cout << fathIndiv.v_chromosome2[n].operation_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs2 * number_of_operations; n < fathIndiv.v_chromosome2.size(); n++)
	//{
	//	cout << fathIndiv.v_chromosome2[n].machine_number << " ";
	//}
	//cout << endl;

	//cout << "ĸ�׵Ĺ���ͻ�����Ϣ��" << endl;
	//for (int n = 0; n < number_of_jobs2 * number_of_operations; n++)
	//{
	//	cout << mothIndiv.v_chromosome2[n].operation_number << " ";
	//}
	//cout << endl;
	//for (int n = number_of_jobs2 * number_of_operations; n < mothIndiv.v_chromosome2.size(); n++)
	//{
	//	cout << mothIndiv.v_chromosome2[n].machine_number << " ";
	//}
	//cout << endl;


	vector <CChromosome>().swap(chIndiv1.v_chromosome2);//����Ӵ�����
	vector <CChromosome>().swap(chIndiv2.v_chromosome2);//����Ӵ�����
	////step3�������������֣�����˳�򽻲�
	bool bt;
	int index;
	int cutpoint3, cutpoint4;//���������е㣻
	int temp2, operNo;
	cutpoint3 = rand() % number_of_jobs2*number_of_operations;//ȡֵ��ΧΪ[number_of_jobs , number_of_jobs + total_operations_number)
	cutpoint4 = rand() % number_of_jobs2*number_of_operations;
	while (cutpoint3 == cutpoint4)//�������е���ͬ
	{
		cutpoint3 = rand() % number_of_jobs2*number_of_operations;//�����²���һ���е�2
	}//���� ��Ϊ ���е�1���е�2��ǰ�棬ֱ���ҷ����������
	if (cutpoint3 > cutpoint4)//���е�1���е�2����
	{
		temp2 = cutpoint3;
		cutpoint3 = cutpoint4;//����л�������
		cutpoint4 = temp2;
	}
	//cout << "cutpoint3 = " << cutpoint3 << endl;
	//cout << "cutpoint4 = " << cutpoint4 << endl;
	for (int j = 0; j < number_of_jobs2*number_of_operations; j++)//�Ӵ������ʼ����һ��ʼ���ȴ��������ٶԶ����factory_numberȫ����ֵΪ0
	{
		CChromosome	tt3;
		tt3.operation_number = 0;
		chIndiv1.v_chromosome2.push_back(tt3);
		CChromosome	tt4;
		tt4.operation_number = 0;
		chIndiv2.v_chromosome2.push_back(tt4);
	}

	for (int j = 0; j < cutpoint3; j++)//ע��cutpoint3�ǿ����䣬�����ҵ���ϵ���ҵ��ȡ�����ģ�
	{
		operNo = fathIndiv.v_chromosome2[j].operation_number;//��ȡ����Ⱦɫ����[number_of_jobs,cutpoint3)�������ҵ
		//cout << "operNo = " << operNo << endl;
		chIndiv1.v_chromosome2[j].operation_number = operNo;//������[number_of_jobs,cutpoint3)�ϵ���ҵ ���� ���Ӵ�1��ͬλ��
		//cout << "chIndiv1.v_chromosome[j].operation_number = " << chIndiv1.v_chromosome2[j].operation_number << endl;
		operNo = mothIndiv.v_chromosome2[j].operation_number;//��ȡĸ��Ⱦɫ����[number_of_jobs,cutpoint3)�������ҵ
		//cout << "operNo = " << operNo << endl;
		chIndiv2.v_chromosome2[j].operation_number = operNo;//��ĸ��[number_of_jobs,cutpoint3)�ϵ���ҵ ���� ���Ӵ�2��ͬλ��
		//cout << "chIndiv2.v_chromosome[j].operation_number = " << chIndiv2.v_chromosome2[j].operation_number << endl;
	}
	for (int j = cutpoint4; j < number_of_jobs2*number_of_operations; j++)
	{
		operNo = fathIndiv.v_chromosome2[j].operation_number;//��ȡ����Ⱦɫ����[number_of_jobs,cutpoint3)�������ҵ
		//cout << "operNo = " << operNo << endl;
		chIndiv1.v_chromosome2[j].operation_number = operNo;//������[number_of_jobs,cutpoint3)�ϵ���ҵ ���� ���Ӵ�1��ͬλ��
		//cout << "chIndiv1.v_chromosome2[j].operation_number = " << chIndiv1.v_chromosome2[j].operation_number << endl;
		operNo = mothIndiv.v_chromosome2[j].operation_number;//��ȡĸ��Ⱦɫ����[number_of_jobs,cutpoint3)�������ҵ
		//cout << "operNo = " << operNo << endl;
		chIndiv2.v_chromosome2[j].operation_number = operNo;//��ĸ��[number_of_jobs,cutpoint3)�ϵ���ҵ ���� ���Ӵ�2��ͬλ��
		//cout << "chIndiv2.v_chromosome[j].operation_number = " << chIndiv2.v_chromosome2[j].operation_number << endl;
	}
	////���� �ǽ���ĸ �����е� �������ҵ ֱ�ӿ��� ���Ӵ�1���Ӵ�2����ͬλ��
	////���濪ʼ����Ӵ�1���Ӵ�2[cutpoint3,cutpoint4)֮�����ҵ���Ӵ�1��ʣ�ಿ�ִ�ĸ�������ã��Ӵ�2������
	index = cutpoint3;//��cutpoint3λ�ÿ�ʼ��䣬����ѭ�����λ�ñ���䣬��index++�����������һ��	
	vector<int> v_store_operation;//����һ�������Ѿ��������Ĺ��򣬷���Ƚϣ���Ϊ��ǰ���򲻽�Ҫ�����˻�ȡ�Ļ���Ƚϣ���Ҫ���Ѿ�����ıȽ�
	vector<int>().swap(v_store_operation);
	v_store_operation.push_back(0);//�ȷ���һ��0���������Ƚϣ�����һ��ʼ�ǿյĲ�����size()ѭ��
	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	{
		int times = 0;
		operNo = mothIndiv.v_chromosome2[j].operation_number;//��ĸ����ÿ����ҵ���Ӵ�1���е���ҵ�Ƚ�;
		//cout << "operNo = " << operNo << endl;
		bt = false;
		//compare1
		for (int k = 0; k < cutpoint3; k++)//����ǰĸ����ҵ���Ӵ�1����[number_of_jobs,cutpoint3)��ҵ�Ƚ�
		{
			if (operNo == chIndiv1.v_chromosome2[k].operation_number)//������һ����ͬ�ģ��ۼ����������ظ�����
			{
				times = times + 1;//��¼��job�Ĺ�������˵��ظ�����
				//cout << "times1 = " << times << endl;//times1,times2,times3��������һ����ֵ��ظ�
			}
		}
		//compare2
		for (int k = cutpoint4; k < number_of_jobs2 * number_of_operations; k++)
		{
			if (operNo == chIndiv1.v_chromosome2[k].operation_number)
			{
				times = times + 1;//��¼��job�Ĺ����ڶ˵��ظ�����
				//cout << "times2 = " << times << endl;
			}
		}
		//compare3
		for (int k = 0; k < v_store_operation.size(); k++)//����Ҫ�͹̶������˱Ƚϣ���Ҫ��ղ������Щ����Ƚ�
		{
			if (operNo == v_store_operation[k])
			{
				times = times + 1;
				//cout << "times3 = " << times << endl;
			}
		}
		//�ж�
		if (times == number_of_operations)//���ù����Ѿ�����3��
		{
			bt = true;
			continue;//Ҫcontinue,������һ��job�ıȽ�
		}
		//����
		if (bt == false)//��һֱfalse��δ����true��˵���ù���δ����3��
		{
			chIndiv1.v_chromosome2[index].operation_number = operNo;
			v_store_operation.push_back(operNo);
			//cout << "chIndiv1.v_chromosome[index].operation_number=" << chIndiv1.v_chromosome2[index].operation_number << endl;
			index++;//��ʱԭcutpoint1�Ѿ�������ˣ���++�����������һ��λ��
		}
	}//��������Ӵ�1[cutpoint3,cutpoint4)λ����ҵ����䣬��ĸ�׻�á�
	//system("pause");
	index = cutpoint3;
	vector<int>().swap(v_store_operation);
	v_store_operation.push_back(0);//�ȷ���һ��0���������Ƚϣ�����һ��ʼ�ǿյĲ�����size()ѭ��
	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	{
		int times = 0;
		operNo = fathIndiv.v_chromosome2[j].operation_number;//��ĸ����ÿ����ҵ���Ӵ�1���е���ҵ�Ƚ�;
		//cout << "operNo = " << operNo << endl;
		bt = false;
		//compare1
		for (int k = 0; k < cutpoint3; k++)//����ǰĸ����ҵ���Ӵ�1����[number_of_jobs,cutpoint3)��ҵ�Ƚ�
		{
			if (operNo == chIndiv2.v_chromosome2[k].operation_number)//������һ����ͬ�ģ��ۼ����������ظ�����
			{
				times = times + 1;//��¼��job�Ĺ�������˵��ظ�����
				//cout << "times1 = " << times << endl;//times1,times2,times3��������һ����ֵ��ظ�
			}
		}
		//compare2
		for (int k = cutpoint4; k < number_of_jobs2 * number_of_operations; k++)
		{
			if (operNo == chIndiv2.v_chromosome2[k].operation_number)
			{
				times = times + 1;
				//cout << "times2 = " << times << endl;
			}
		}
		//compare3
		for (int k = 0; k < v_store_operation.size(); k++)//����Ҫ�͹̶������˱Ƚϣ���Ҫ��ղ������Щ����Ƚ�
		{
			if (operNo == v_store_operation[k])
			{
				times = times + 1;
				//cout << "times3 = " << times << endl;
			}
		}
		//�ж�
		if (times == number_of_operations)//���ù����Ѿ�����3��
		{
			bt = true;
			continue;//Ҫcontinue,������һ��job�ıȽ�
		}
		//����
		if (bt == false)//��һֱfalse��δ����true��˵���ù���δ����3��
		{
			chIndiv2.v_chromosome2[index].operation_number = operNo;
			v_store_operation.push_back(operNo);
			//cout << "chIndiv2.v_chromosome2[index].operation_number=" << chIndiv2.v_chromosome2[index].operation_number << endl;
			index++;//��ʱԭcutpoint1�Ѿ�������ˣ���++�����������һ��λ��
		}
	}//��������Ӵ�2[cutpoint3,cutpoint4)λ����ҵ����䣬�Ӹ��׻�á�

	//���乤������������job����Ϣ�͹���˳����Ϣ
	for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	{
		chIndiv1.v_chromosome2[k].job_number = chIndiv1.v_chromosome2[k].operation_number;
		chIndiv2.v_chromosome2[k].job_number = chIndiv2.v_chromosome2[k].operation_number;
	}

	for (int k = 0; k < number_of_jobs2; k++)//�ж���ÿ��job�ĵڼ�������
	{
		int current_job_number = k + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs2 * number_of_operations; c++)
		{
			if (current_job_number == chIndiv1.v_chromosome2[c].job_number)
			{
				count = count + 1;
				chIndiv1.v_chromosome2[c].operation_index = count;
			}
			continue;
		}
	}

	for (int k = 0; k < number_of_jobs2; k++)//�ж���ÿ��job�ĵڼ�������
	{
		int current_job_number = k + 1;
		int count = 0;
		for (int c = 0; c < number_of_jobs2 * number_of_operations; c++)
		{
			if (current_job_number == chIndiv2.v_chromosome2[c].job_number)
			{
				count = count + 1;
				chIndiv2.v_chromosome2[c].operation_index = count;
			}
			continue;
		}
	}

	//////�������������������Ϣ
	//cout<<"����������Ӵ��Ĺ���������"<<endl;
	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv1.v_chromosome2[k].operation_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv1.v_chromosome2[k].job_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv1.v_chromosome2[k].operation_index << " ";
	//}
	//cout << endl << endl;

	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv2.v_chromosome2[k].operation_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv2.v_chromosome2[k].job_number << " ";
	//}
	//cout << endl;
	//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
	//{
	//	cout << chIndiv2.v_chromosome2[k].operation_index << " ";
	//}
	//cout << endl;
	//system("pause");


	//step4:�����������֣������ַ���
	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)//�Ӵ������ʼ����һ��ʼ���ȴ��������ٶԶ����machine_numberȫ����ֵΪ0
	{
		CChromosome	tt5;
		tt5.machine_number = 0;
		chIndiv1.v_chromosome2.push_back(tt5);
		CChromosome	tt6;
		tt6.machine_number = 0;
		chIndiv2.v_chromosome2.push_back(tt6);
	}

	for (int k = number_of_jobs2 * number_of_operations; k < chIndiv1.v_chromosome2.size(); k++)
	{
		//�������һ��0-1����������=0����ȡ���׻���������=1����ȡĸ�׻���
		int rand_m_number1 = rand() % 2;
		//cout << "rand_number1 = " << rand_m_number1 << endl;
		if (rand_m_number1 == 0)
		{
			chIndiv1.v_chromosome2[k].machine_number = fathIndiv.v_chromosome2[k].machine_number;
		}
		else if (rand_m_number1 == 1)
		{
			chIndiv1.v_chromosome2[k].machine_number = mothIndiv.v_chromosome2[k].machine_number;
		}
	}
	for (int k = number_of_jobs2 * number_of_operations; k < chIndiv2.v_chromosome2.size(); k++)
	{
		//�������һ��0-1����������=0����ȡ���׻���������=1����ȡĸ�׻���
		int rand_m_number2 = rand() % 2;
		//cout << "rand_number2 = " << rand_m_number2 << endl;
		if (rand_m_number2 == 0)
		{
			chIndiv2.v_chromosome2[k].machine_number = fathIndiv.v_chromosome2[k].machine_number;
		}
		else if (rand_m_number2 == 1)
		{
			chIndiv2.v_chromosome2[k].machine_number = mothIndiv.v_chromosome2[k].machine_number;
		}
	}
	//cout << endl << endl;
	//�������������job��Ϣ
	int dis = 0;
	for (int j = 0; j < number_of_jobs2; j++)
	{
		for (int o = 0; o < number_of_operations; o++)
		{
			chIndiv1.v_chromosome2[o + dis + number_of_jobs2 * number_of_operations].job_number = j + 1;
			chIndiv2.v_chromosome2[o + dis + number_of_jobs2 * number_of_operations].job_number = j + 1;
		}
		dis = dis + number_of_operations;
	}
	//cout << endl;
	////���������������Ϣ
	//cout << "����������Ӵ��Ļ���������Ϣ��" << endl;
	//for (int k = number_of_jobs2 * number_of_operations; k < chIndiv1.v_chromosome2.size(); k++)
	//{
	//	cout << chIndiv1.v_chromosome2[k].machine_number << " ";
	//}
	//cout << endl;
	//for (int k = number_of_jobs2 * number_of_operations; k < chIndiv2.v_chromosome2.size(); k++)
	//{
	//	cout << chIndiv2.v_chromosome2[k].machine_number << " ";
	//}
	//cout << endl << endl;

	//for (int k = number_of_jobs2 * number_of_operations; k < chIndiv1.v_chromosome2.size(); k++)
	//{
	//	cout << chIndiv1.v_chromosome2[k].job_number << " ";
	//}
	//cout << endl;
	//for (int k = number_of_jobs2 * number_of_operations; k < chIndiv2.v_chromosome2.size(); k++)
	//{
	//	cout << chIndiv2.v_chromosome2[k].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
	//����FJSP�������������������������

	//cout << "�Ӵ�1��" << endl;
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	cout << chIndiv1.v_chromosome1[j].factory_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs1; j < chIndiv1.v_chromosome1.size(); j++)
	//{
	//	cout << chIndiv1.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;

	//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
	//{
	//	cout << chIndiv1.v_chromosome2[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
	//{
	//	cout << chIndiv1.v_chromosome2[j].operation_index << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < chIndiv1.v_chromosome2.size(); j++)
	//{
	//	cout << chIndiv1.v_chromosome2[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < chIndiv1.v_chromosome2.size(); j++)
	//{
	//	cout << chIndiv1.v_chromosome2[j].job_number << " ";
	//}
	//cout << endl;
	//system("pause");

	//cout << "�Ӵ�2��" << endl;
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	cout << chIndiv2.v_chromosome1[j].factory_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs1; j < chIndiv2.v_chromosome1.size(); j++)
	//{
	//	cout << chIndiv2.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;

	//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
	//{
	//	cout << chIndiv2.v_chromosome2[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
	//{
	//	cout << chIndiv2.v_chromosome2[j].operation_index << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < chIndiv2.v_chromosome2.size(); j++)
	//{
	//	cout << chIndiv2.v_chromosome2[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < chIndiv2.v_chromosome2.size(); j++)
	//{
	//	cout << chIndiv2.v_chromosome2[j].job_number << " ";
	//}
	//cout << endl;
	//system("pause");
}


void CGenetic::mutate(CIndividual& t, double rate)//�Ը�����б��죬rate�Ǳ����ʣ�t�Ǵ�������child1������evovle��
{
	if (rand() / (RAND_MAX * 1.0) <= rate)   //����һ���������rate�Ƚ��ж��Ƿ���б��죬�������õ��ǰٷְٱ��죬�ʿ϶��Ըø�����б���
	{
		//step1:�Թ������������ѡ��������ͬ�ĵ㣬Ȼ����н���
		int cutpoint3, cutpoint4;//���������е㣻
		int facNo1, facNo2;
		cutpoint3 = rand() % number_of_jobs1;//�������һ���е�1���е�1�ķ�Χ[0 , number_of_jobs-1]
		cutpoint4 = rand() % number_of_jobs1;//�������һ���е�2���е�2�ķ�Χ[0 , number_of_jobs-1]
		while (cutpoint3 == cutpoint4)//�������е���ͬ
		{
			cutpoint4 = rand() % number_of_jobs1;//�����²���һ���е�2
		}
		facNo1 = t.v_chromosome1[cutpoint3].factory_number;
		facNo2 = t.v_chromosome1[cutpoint4].factory_number;
		while (facNo1 == facNo2)
		{
			cutpoint4 = rand() % number_of_jobs1;//�����²���һ���е�2
			facNo2 = t.v_chromosome1[cutpoint4].factory_number;
		}
		//cout << "cutpoint3 = " << cutpoint3 << endl;
		//cout << "cutpoint4 = " << cutpoint4 << endl;
		//cout << "facNo1 = " << facNo1 << endl;
		//cout << "facNo2 = " << facNo2 << endl;
		int temp_factory;
		temp_factory = t.v_chromosome1[cutpoint3].factory_number;
		t.v_chromosome1[cutpoint3].factory_number = t.v_chromosome1[cutpoint4].factory_number;
		t.v_chromosome1[cutpoint4].factory_number = temp_factory;
		////�������������������Ϣ
		//for (int j = 0; j <number_of_jobs1; j++)
		//{
		//	cout << t.v_chromosome1[j].factory_number << " ";
		//}
		//cout << endl;
		//system("pause");

		//������������ĸ��忪ʼ���б���
		//step2:����ҵ˳�����������ѡ��������ͬ�ĵ㣬Ȼ����з�ת
		int cutpoint1, cutpoint2;//���������е㣻			
		cutpoint1 = number_of_jobs1 + rand() % number_of_jobs1;
		cutpoint2 = number_of_jobs1 + rand() % number_of_jobs1;
		while (cutpoint1 == cutpoint2)//�������е���ͬ
		{
			cutpoint2 = number_of_jobs1 + rand() % number_of_jobs1;//�����²���һ���е�2
		}
		int temp_cut;
		if (cutpoint1 > cutpoint2)
		{
			temp_cut = cutpoint1;
			cutpoint1 = cutpoint2;
			cutpoint2 = temp_cut;
		}
		//cout << "cutpoint1 = " << cutpoint1 << endl;
		//cout << "cutpoint2 = " << cutpoint2 << endl;
		int jobNo;
		vector <int> v_job_part_list;
		vector <int>().swap(v_job_part_list);//��������Ԫ�ط����������ʹ��reverse��ת
		for (int j = cutpoint1; j <= cutpoint2; j++)
		{
			jobNo = t.v_chromosome1[j].job_number;
			v_job_part_list.push_back(jobNo);
		}
		//for (int j = 0; j < v_job_part_list.size();j++)
		//{
		//	cout << v_job_part_list[j] << " ";
		//}
		//system("pause");
		reverse(v_job_part_list.begin(), v_job_part_list.end()); //��v_operation_part_list�еĴ�v_operation_part_list.begin()������������v_operation_part_list.end()������������Ԫ�ص��ã���v_operation_part_list��Ԫ��Ϊ1,2,3,4,���ú�Ϊ4,3,2,1
		//for (int j = 0; j < v_job_part_list.size(); j++)
		//{
		//	cout << v_job_part_list[j] << " ";
		//}
		//system("pause");
		int jobNo_o;
		for (int j = cutpoint1; j <= cutpoint2; j++)
		{
			jobNo_o = v_job_part_list[j - cutpoint1];
			//cout << "jobNo_o = " << jobNo_o << endl;
			t.v_chromosome1[j].job_number = jobNo_o;//job_number��֮����
		}
		//system("pause");
		////�������������������Ϣ
		////for (int k = number_of_jobs1; k < 2* number_of_jobs1; k++)
		////{
		////	cout << t.v_chromosome1[k].job_number << " ";
		////}
		////cout << endl;
		////system("pause");
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//step3:�Թ������������ѡ��������ͬ�ĵ㣬Ȼ����з�ת
		int cutpoint5, cutpoint6;//���������е㣻			
		cutpoint5 = rand() % (number_of_jobs2 * number_of_operations);
		cutpoint6 = rand() % (number_of_jobs2 * number_of_operations);
		while (cutpoint5 == cutpoint6)//�������е���ͬ
		{
			cutpoint6 = rand() % (number_of_jobs2 * number_of_operations);//�����²���һ���е�2
		}
		int temp_cut2;
		if (cutpoint5 > cutpoint6)
		{
			temp_cut2 = cutpoint5;
			cutpoint5 = cutpoint6;
			cutpoint6 = temp_cut2;
		}
		//cout << "cutpoint5 = " << cutpoint5 << endl;
		//cout << "cutpoint6 = " << cutpoint6 << endl;
		int operNo;
		vector <int> v_oper_part_list;
		vector <int>().swap(v_oper_part_list);//��������Ԫ�ط����������ʹ��reverse��ת
		for (int j = cutpoint5; j <= cutpoint6; j++)
		{
			operNo = t.v_chromosome2[j].operation_number;
			v_oper_part_list.push_back(operNo);
		}
		//for (int j = 0; j < v_oper_part_list.size(); j++)
		//{
		//	cout << v_oper_part_list[j] << " ";
		//}
		//system("pause");
		reverse(v_oper_part_list.begin(), v_oper_part_list.end()); //��v_operation_part_list�еĴ�v_operation_part_list.begin()������������v_operation_part_list.end()������������Ԫ�ص��ã���v_operation_part_list��Ԫ��Ϊ1,2,3,4,���ú�Ϊ4,3,2,1
		//for (int j = 0; j < v_oper_part_list.size(); j++)
		//{
		//	cout << v_oper_part_list[j] << " ";
		//}
		//system("pause");
		int jobNo_j;
		for (int j = cutpoint5; j <= cutpoint6; j++)
		{
			jobNo_j = v_oper_part_list[j - cutpoint5];
			//cout << "jobNo_j = " << jobNo_j << endl;
			t.v_chromosome2[j].operation_number = jobNo_j;
			t.v_chromosome2[j].job_number = jobNo_j;//job_number��֮����
		}
		//system("pause");

		//operation_index��֮����
		for (int k = 0; k < number_of_jobs2; k++)//�ж���ÿ��job�ĵڼ�������
		{
			int current_job_number = k + 1;
			int count = 0;
			for (int c = 0; c < number_of_jobs2 * number_of_operations; c++)
			{
				if (current_job_number == t.v_chromosome2[c].job_number)
				{
					count = count + 1;
					t.v_chromosome2[c].operation_index = count;
				}
				continue;
			}
		}
		//cout << endl;
		////�������������������Ϣ
		//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
		//{
		//	cout << t.v_chromosome2[k].operation_number << " ";
		//}
		//cout << endl;
		//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
		//{
		//	cout << t.v_chromosome2[k].operation_index << " ";
		//}
		//cout << endl;
		//for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
		//{
		//	cout << t.v_chromosome2[k].job_number << " ";
		//}
		//cout << endl;
		//system("pause");

		//////step4:�Ի���������ÿ��job��ÿ������Ŀ�ѡ�����ӿ�ѡ��������������������ø���job_number//����Ч������
		//for (int j = 0; j < number_of_jobs2; j++)
		//{
		//	for (int o = 0; o < number_of_operations; o++)
		//	{
		//		int operation_machine_size = v_available_machines[j][o].size();
		//		int rand_machine_number_index = rand() % operation_machine_size;
		//		int rand_machine_number = v_available_machines[j][o][rand_machine_number_index];
		//		//cout << "rand_machine_number = " << rand_machine_number << endl;
		//		int index = number_of_jobs2 * number_of_operations + j * number_of_operations +  o;
		//		//cout << "index = " << index << endl;
		//		t.v_chromosome2[index].machine_number = rand_machine_number;
		//		t.v_chromosome2[number_of_jobs2 * number_of_operations + j + o].job_number = j + 1;
		//	}
		//}
		
		////step4:�Ի������������ѡ1������Ȼ�������������
		////���ѡ��һ�������λ��������ȡ�乤���ź͹�����ű��
		int ls = rand() % (number_of_jobs2 * number_of_operations);
		//cout << "ls = " << ls << endl;
		int ls_operation = t.v_chromosome2[ls].operation_number;
		//cout << "ls_operation =" << ls_operation << endl;
		int ls_operation_xuhao = t.v_chromosome2[ls].operation_index;
		//cout << "ls_operation_xuhao =" << ls_operation_xuhao << endl;
		//��ȡ��job�ĸõ�����Ŀ�ʹ�û�������
		int operation_machine_size = v_available_machines[ls_operation - 1][ls_operation_xuhao - 1].size();
		//cout << "operation_machine_size = " << operation_machine_size << endl;
		if (operation_machine_size >= 2)
		{
			int rand_machine_number_index = rand() % operation_machine_size;
			//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
			int rand_machine_number = v_available_machines[ls_operation - 1][ls_operation_xuhao - 1][rand_machine_number_index];
			//cout << "rand_machine_number = " << rand_machine_number << endl;
			int index = number_of_jobs2 * number_of_operations + (ls_operation - 1) * number_of_operations + (ls_operation_xuhao - 1);
			//cout << "index = " << index << endl;
			int current_machine_number = t.v_chromosome2[index].machine_number;
			//cout << "current_machine_number =" << current_machine_number << endl;
			while (current_machine_number == rand_machine_number)
			{
				rand_machine_number_index = rand() % operation_machine_size;
				//cout << "rand_machine_number_index = " << rand_machine_number_index << endl;
				rand_machine_number = v_available_machines[ls_operation - 1][ls_operation_xuhao - 1][rand_machine_number_index];
				//cout << "rand_machine_number = " << rand_machine_number << endl;
			}
			t.v_chromosome2[index].machine_number = rand_machine_number;
		}
		//system("pause");
		//////���������������Ϣ
		//for (int k = number_of_jobs2 * number_of_operations; k < t.v_chromosome2.size(); k++)
		//{
		//	cout << t.v_chromosome2[k].machine_number << " ";
		//}
		//cout << endl;
		//for (int k = number_of_jobs2 * number_of_operations; k < t.v_chromosome2.size(); k++)
		//{
		//	cout << t.v_chromosome2[k].job_number << " ";
		//}
		//cout << endl;
		////���� ����������ɱ���
		//system("pause");
	}
	else//������
	{
		//cout << "������" << endl;
		t = t;
	}
	
	//cout << "�����child���壺" << endl;
	//for (int j = 0; j < number_of_jobs1; j++)
	//{
	//	cout << t.v_chromosome1[j].factory_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs1; j < t.v_chromosome1.size(); j++)
	//{
	//	cout << t.v_chromosome1[j].job_number << " ";
	//}
	//cout << endl;

	//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
	//{
	//	cout << t.v_chromosome2[j].operation_number << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
	//{
	//	cout << t.v_chromosome2[j].operation_index << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < t.v_chromosome2.size(); j++)
	//{
	//	cout << t.v_chromosome2[j].machine_number << " ";
	//}
	//cout << endl;
	//for (int j = number_of_jobs2 * number_of_operations; j < t.v_chromosome2.size(); j++)
	//{
	//	cout << t.v_chromosome2[j].job_number << " ";
	//}
	//cout << endl;
	////system("pause");
}