//#include "Genetic.h"
//#include "Individual.h"
//#include "headfile.h"
//#include "Vehicle.h"
//#include "Chromosome.h"
//#include <vector>
//using namespace std;
//
//
//void CGenetic::rank_fix()
//{
//	//cout << "------------2����֧������---------" << endl;
//	int i, j;
//	int domRel, rankLevel, size, sizeZero, domChromoNo, domedChromoNo;
//	double objValue;
//	bool bt;
//	vector <int> v_domZero;//�������������汻֧�����Ϊ0�ĸ��壨���ǵ�ָ��һ�㣬�п����Ǻ�����һ������һ�㣩
//	//initialize
//	for (i = 0; i < v_Chromo.size(); i++)//��ʼ����Ⱥ��ÿ������ı�֧�������֧���б��ϣ���������0
//	{
//		v_Chromo[i].domination_count = 0;//��Ⱥ�е�i������� ��֧����� ��ʼ��Ϊ0
//		v_Chromo[i].v_dominationSet.resize(0);//��Ⱥ�е�i������� ֧���б��� ��ʼ������Ϊ0
//		v_Chromo[i].rank = 0;//��Ⱥ�е�i������� ���� ��ʼ��Ϊ0
//	}
//
//	//Ȼ������� ÿ������ ���� �жϸ���֧���ϵ������Ϊ������ ��֧�����domination_count ��֧���б���v_dominationSet ��ֵ��
//	size = v_Chromo.size();//��Ⱥ��ģ��С       ��NSGA2������ÿ�����嶼��һ��������һ�������������ԣ������ڵ�������CIndividual��
//	for (i = 0; i < v_Chromo.size() - 1; i++)//�˹��̻�ȡv_Chromo��Ⱥ��ÿ�� ����� ��֧����� �� ֧����������ļ���
//	{
//		for (int j = i + 1; j < v_Chromo.size(); j++)//���������໥�Ƚ����е�Ŀ��ֵ
//		{               //���ú�������Ϊ�Ƚϵ������������֧���ϵ�����ڴ�������ʱ��Ҳ�Ǵ�����
//			domRel = 3; //v_Chromo[i],v_Chromo[j]������������Ķ��󼴵�i������͵�j�����󣬽�ʵ�δ����β�A��B�����ô��ݣ��ҳ����ã�
//			domRelation(v_Chromo[i], v_Chromo[j], domRel);//���ڶ��������� �ж�A��B֧���ϵ �ĺ�����void CGenetic::domRelation(const CIndividual& A, const CIndividual& B, int& domRel)
//			if (domRel == 1)//ǰ�����ں���      ����ֵ=1����ʾ֧�䣻
//			{   //������.������ ���� ���еı�������v_dominationSet�Ƕ������������ʹ��push_back()β�巨��ֵ
//				v_Chromo[j].domination_count++;//�� �������v_Chromo[j] �� ����domination_count����֧����� ++
//				v_Chromo[i].v_dominationSet.push_back(j);//��ǰ�߶���v_Chromo[i] �� ����֧���б���v_dominationSet β�� һ�� ���ߵĶ����
//			}
//			else if (domRel == -1)///ǰ�߲��ں���    ����ֵ=-1����ʾ��֧��
//			{
//				v_Chromo[i].domination_count++;//��ǰ�����v_Chromo[i] �� ����domination_count����֧����� ++
//				v_Chromo[j].v_dominationSet.push_back(i);//�ʺ������v_Chromo[j] ������֧�伯��v_dominationSet β�� һ�� ǰ�ߵĶ����
//			}//����ֻ������������֧���뱻֧��Ĺ�ϵ������Ӱ�������֧�������֧���б��ϣ�����doRem1=0����ȣ�����domRe1=2(��֧��)������
//		}
//	}//���� ���v_Chromo��Ⱥ�� ÿ������� ��֧�������֧���б�
//
//	//rank the population  //CRankSequ���� ���������� �� ����������Ⱦɫ����chromoNo������ֵrankSequ��ӵ���Ⱦ���croDiversity��Ŀ��ֵv_robjective
//	vector <CRankSequ>().swap(v_rankSequ);  //����swap�����ڴ棬v_rankSequ��ʱ�ĳ���Ϊ0���൱�ڳ�ʼ�������ݺ������򣬲�����ϵĶ���
//	rankLevel = 1;	//��ʼ�� ��ţ����ŵ�һ��
//	while (1)//while��1��ָ��ѭ����Զִ����ȥ.��������break;������ѭ����//���whileѭ�����Ǹ��ֲ�Ĺ���
//	{                 //���ҷֲ���̣������һ��v_CRankSequ������������ֵΪ1�Ķ����2��3��ô�ţ����Ҹ��������ı���chromoNo,rankSequ,croDiversity,v_robjective
//		bt = false;   //����ָ��!! ��Ϊ�������ר�ű�֧�����Ϊ0�Ķ������ڽ�����һ���������б�֧�����-1�Ĳ�������һ��Ϊ0�Ĳ�������ѡ�� 
//		v_domZero.resize(0);//����ָ�� ���汻֧�����Ϊ0�Ķ���� ������domZero ����Ϊ0��
//		for (i = 0; i < v_Chromo.size(); i++)//�����ж�ÿ�������Ƿ�֧�����=0����:����������������v_rankSequ�͵�ǰ֧�����=0����v_domZero��
//		{    //ͬʱ����v_Chromo��v_rankSequ�����ĳ�Ա������rank��chromoNo,rankSequ,rankLevel,v_rObjValue
//			if (v_Chromo[i].domination_count == 0)//��v_Chromo����ĵ�i����� ��������֧�������Ϊ0���ͻ��ֵ���ǰ��������һ������ʱ���ǵ�һ��
//			{//��Ҫ��ΪCRankSequ�����еľ������t��Ӧ�ı�����ֵ��ͬʱ��t��������v_CRankSequ������ʱ�����Ź����Ŷ��t������ѡ��
//				//rankLevel����CIndividual�ж�Ӧ���� rank�� ����CRankSequ�ж�Ӧ����rankSequ
//				CRankSequ t;//����һ���������t���������԰��� chromoNo��rankLevel�� v_rObjValue;����ٰѶ���ŵ�rankSequ������                
//				v_Chromo[i].rank = rankLevel;//��ǰrankLevelֵ ��ֵ�� v_Chromo�Ķ���i�� ����rank��
//				t.chromoNo = i;//�� �����i ��ֵ�� �ö���t�� Ⱦɫ����chromoNo
//				t.rankSequ = rankLevel;//����ǰrankLevelֵ ��ֵ�� CRankSequ�Ķ���t  ����rankSequֵ��
//				for (j = 0; j < number_of_objectives; j++)
//				{
//					objValue = v_Chromo[i].v_objective_value[j];//��v_Chromo����i���� ��ȡ ÿ��Ŀ��ֵ
//					t.v_rObjValue.push_back(objValue);//�ٸ�ֵ ������t ��v_rObjValue���������Ŀ�����Ҫһ������vector <double> v_rObjValue;
//				}
//				v_rankSequ.push_back(t);//���������t����v_rankSequ��
//				bt = true;//ֻҪ��һ���б�֧�����=0���Ϳ��Ը��������󣬽�����һ���ɸѡ
//				v_domZero.push_back(i);//�������i����v_domZero�����У�����1��3��5�ı�֧�����=0����ô1,3,5����Ÿ�ֵ��������
//			}
//			//�������if���Ҳ������CIndividual��CRankSequ��֮��Ĺ�ϵ��CRankSequ��chromoNo��v_rObjValue���Ǵ�CIndividual��ȡ
//		}//������������ֱ���V_Chromo[i]��t
//		//�������forѭ�������ǰ����еı�֧�����=0�Ķ��ҳ���������У�����Ϊ����t,�ٽ�����t����rankSequ���飬����Ӧ�Ķ����i����v_domZero����
//	  //�Ҹ�ֵ��v_Chromo�е�rank����=rankLevel�� CRankSequ�е�t��rankSequ=rankLevel,chromoNo=i,v_robjctive=��v_Chromo[i]�ǻ�ȡ��objective
//		if (bt == false)//һ��ʼ��ʼ��Ϊfalse��ֻҪ�浽һ����֧�����Ϊ0�ģ���һ�������ݣ�����ô�Ϳ���true;����true��������䣬ɸѡ��һ��
//		{
//			break;//���û��==0�ģ������-1�ˣ���ֹ�ظ��ж����õ�-1������ôû��true,Ĭ�ϳ�ʼfalse������������whileѭ�����ֲ����
//		}
//		if (bt == true)//��trueʱ������һ�㣬�Ұ���һ�㱻֧�����=0�Ķ�ɸ�����ˣ���ô�����ϲ㿪ʼɸѡ��һ�㣺���ǰ���һ��ĸ�����ӵ�е�֧���б��еĸ���ı�֧�����-1
//		{
//			rankLevel++;//�²����++����һ����� ��֧���б� �����ĸ���ı�֧�����-1������A��B�ǵ�һ�㣬A֧��C,D,E�� B֧��C��F����ôC-2��D��E��F-1��
//			sizeZero = v_domZero.size();//��ǰ��֧�����=0������v_domZero �� ���ȣ����ж��ٸ�����ѽ
//			for (int j = 0; j < sizeZero; j++)//�ж��ٸ����ݾͱ������ٴ�
//			{
//				domChromoNo = v_domZero[j];//��ԭ�������ȥ��t�Ķ������ȡ����ֵ��domChromoNov_domZero[0]=1��v_domZero[1]=3��v_domZero[2]=5��
//				v_Chromo[domChromoNo].domination_count = -1;//��ԭ����֧�����=0�� ���� �� ��֧�������Ϊ-1����Ϊ��ǰif�������Խ��������Ǹ��ֲ��жϣ�
//				size = v_Chromo[domChromoNo].v_dominationSet.size();//��ȡ��֧�����=0�Ķ��� �� ֧���б��� �� ����           //��Щ=0���Ѿ��жϹ��ˡ�
//				for (int k = 0; k < size; k++)
//				{
//					domedChromoNo = v_Chromo[domChromoNo].v_dominationSet[k];//�ѱ�֧�����ı��ȡ���� ��ֵ�� domedChromoNo
//					v_Chromo[domedChromoNo].domination_count--;//��֧�����ı�֧�����-1
//				}
//			}
//		}//���if���󣬲�����һ����֧�����=0�Ķ��󣬽���whileѭ��������ִ�������Ǹ�if (v_Chromo[i].domination_count == 0)
//	}                                                                                          //�ж���һ������Щ����
//	//�������whileѭ�����Ƿֲ�ģ���ԭ����Ⱥ�еĶ�����֮ǰ�ı�֧�������֧�伯��ָ����зֲ㣻����v_RankSequ����������F1,F2...˳�����δ洢
//
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//v_RankSequ�����洢һ�Ŷ�����Щ�����ǰ���rankֵ����ģ���ǰ�����ǵ�һ��ģ����ż����ǵڶ��㣬ֱ����󼸸����������һ�㡣
//	//v_RankSequ�����еĶ������԰���:chromoNo����ţ�rankSequ��ֵ��ӵ���Ⱦ����Ŀ��ֵ
//	//���v_rankSequ����
//	//for (int cn = 0; cn < v_rankSequ.size(); cn++)
//	//{
//	//	cout << v_rankSequ[cn].chromoNo << " ";
//	//	cout << v_rankSequ[cn].rankSequ << endl;
//	//}
//
//
//
//	//step1:����һ�����飬ר�ű���rankֵ��С�ĸ�����Ϊ��Ѹ���
//	vector <CRankSequ>().swap(v1_individuals);
//	for (int i = 0; i < v_rankSequ.size(); i++)
//	{
//		if (v_rankSequ[i].rankSequ == 1)//ֻͳ�Ƶ�һ��ĸ�����Ŀ
//		{
//			CRankSequ bst;
//			bst.chromoNo = v_rankSequ[i].chromoNo;//��ȡ��ҵ��
//			bst.rankSequ = 1;//�غ�
//			bst.v_rObjValue = v_rankSequ[i].v_rObjValue;//��ȡĿ��ֵ
//			v1_individuals.push_back(bst);
//		}
//	}
//	int v1_size = v1_individuals.size();
//	//for (int i = 0; i < v1_size; i++)
//	//{
//	//	cout<<v1_individuals[i].chromoNo << " ";
//	//}
//	//cout << endl;
//
//	//step2:����һ��������omega��Ⱥ��(���ظ�)
//	vector <CIndividual>().swap(v_omega_individuals);//�������	
//	for (int i = 0; i < v1_size; i++)
//	{
//		CIndividual o_Indiv;
//		int o_Indiv_index = v1_individuals[i].chromoNo;
//		v_omega_individuals.push_back(v_Chromo[o_Indiv_index]);
//	}
//	//for (int i = 0; i < v_omega_individuals.size(); i++)
//	//{
//	//	for (int j = 0; j < v_omega_individuals[i].v_objective_value.size(); j++)
//	//	{
//	//		cout << v_omega_individuals[i].v_objective_value[j] << " ";
//	//	}
//	//	cout << endl;
//	//}
//	//system("pause");
//
//	//step3:ɸѡ�ظ�
//	vector <int> v_delete_indiv_index;//�洢�ظ��������� ����
//	vector <int>().swap(v_delete_indiv_index);
//	for (int i = 0; i < v_omega_individuals.size() - 1; i++)
//	{
//		CIndividual indiv1, indiv2;
//		indiv1 = v_omega_individuals[i];
//		for (int j = i + 1; j < v_omega_individuals.size(); j++)
//		{
//			indiv2 = v_omega_individuals[j];
//			int same_count = 0;
//			for (int k = 0; k < number_of_objectives; k++)
//			{
//				if (indiv1.v_objective_value[k] == indiv2.v_objective_value[k])
//				{
//					same_count = same_count + 1;
//				}
//			}
//
//			if (same_count == 2)
//			{
//				int Same_Count = 0;
//				for (int ii = 0; ii < number_of_jobs1; ii++)
//				{
//					if (indiv1.v_chromosome1[ii].factory_number = indiv2.v_chromosome1[ii].factory_number)
//					{
//						Same_Count = Same_Count + 1;
//					}
//				}
//				for (int jj = number_of_jobs1; jj < 2*number_of_jobs1; jj++)
//				{
//					if (indiv1.v_chromosome1[jj].job_number = indiv2.v_chromosome1[jj].job_number)
//					{
//						Same_Count = Same_Count + 1;
//					}
//				}
//				for (int kk = 0; kk < number_of_jobs2*number_of_operations; kk++)
//				{
//					if (indiv1.v_chromosome2[kk].operation_number = indiv2.v_chromosome2[kk].operation_number)
//					{
//						Same_Count = Same_Count + 1;
//					}
//				}
//				for (int uu = number_of_jobs2 * number_of_operations; uu < indiv1.v_chromosome2.size(); uu++)
//				{
//					if (indiv1.v_chromosome2[uu].machine_number = indiv2.v_chromosome2[uu].machine_number)
//					{
//						Same_Count = Same_Count + 1;
//					}
//				}
//
//				if (Same_Count == 2*number_of_jobs1 + 2 * number_of_jobs2*number_of_operations)
//				{
//					int del_index = j;//��¼Ҫɾ���ĸ����λ������
//					//cout << "del_index =" << j << endl;
//					v_delete_indiv_index.push_back(del_index);
//				}
//			}
//		}
//		//cout << endl;
//	}
//	//system("pause");
//
//	//step3:ֻ�������ظ��ķ�֧��� �� ����Omega
//	vector <CIndividual>().swap(v_Omega_individuals);//�������
//	bool tf = true;
//	for (int i = 0; i < v_omega_individuals.size(); i++)
//	{
//		CIndividual O_indiv = v_omega_individuals[i];
//		for (int j = 0; j < v_delete_indiv_index.size(); j++)
//		{
//			if (i == v_delete_indiv_index[j])
//			{
//				tf = false;
//				break;
//			}
//			else
//			{
//				tf = true;
//				continue;
//			}
//		}
//		if (tf == true)
//		{
//			v_Omega_individuals.push_back(O_indiv);
//		}
//
//	}
//
//	//////step4:���Omega��Ⱥ�������������IGA
//	//for (int i = 0; i < v_Omega_individuals.size(); i++)
//	//{
//	//	for (int j = 0; j < number_of_jobs1; j++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_chromosome1[j].factory_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int j = number_of_jobs1; j < 2*number_of_jobs1; j++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_chromosome1[j].job_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_chromosome2[j].operation_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_chromosome2[j].operation_index << " ";
//	//	}
//	//	cout << endl;
//	//	for (int j = number_of_jobs2*number_of_operations; j < v_Omega_individuals[i].v_chromosome2.size(); j++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_chromosome2[j].machine_number << " ";
//	//	}
//	//	cout << endl;
//
//	//	for (int k = 0; k < v_Omega_individuals[i].v_objective_value.size(); k++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_objective_value[k] << " ";
//	//	}
//	//	cout << endl;
//	//}
//	//system("pause");
//
//	vector <CIndividual>().swap(v_archive);//�������
//	for (int i = 0; i < v_Omega_individuals.size(); i++)
//	{
//		v_archive.push_back(v_Omega_individuals[i]);
//	}
//}