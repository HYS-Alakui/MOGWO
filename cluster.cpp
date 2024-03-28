#include "Genetic.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"
#include <vector>
using namespace std;

void CGenetic::cluster()
{
	//cout << "------------2����֧��ֲ�---------" << endl;
	int i, j;
	int domRel, rankLevel, size, sizeZero, domChromoNo, domedChromoNo;
	double objValue;
	bool bt;
	vector <int> v_domZero;//�������������汻֧�����Ϊ0�ĸ��壨���ǵ�ָ��һ�㣬�п����Ǻ�����һ������һ�㣩
	//initialize
	for (i = 0; i < v_Chromo.size(); i++)//��ʼ����Ⱥ��ÿ������ı�֧�������֧���б��ϣ���������0
	{
		v_Chromo[i].domination_count = 0;//��Ⱥ�е�i������� ��֧����� ��ʼ��Ϊ0
		v_Chromo[i].v_dominationSet.resize(0);//��Ⱥ�е�i������� ֧���б��� ��ʼ������Ϊ0
		v_Chromo[i].rank = 0;//��Ⱥ�е�i������� ���� ��ʼ��Ϊ0
	}
	//Ȼ������� ÿ������ ���� �жϸ���֧���ϵ������Ϊ������ ��֧�����domination_count ��֧���б���v_dominationSet ��ֵ��
	size = v_Chromo.size();//��Ⱥ��ģ��С       ��NSGA2������ÿ�����嶼��һ��������һ�������������ԣ������ڵ�������CIndividual��
	for (i = 0; i < v_Chromo.size() - 1; i++)//�˹��̻�ȡv_Chromo��Ⱥ��ÿ�� ����� ��֧����� �� ֧����������ļ���
	{
		for (int j = i + 1; j < v_Chromo.size(); j++)//���������໥�Ƚ����е�Ŀ��ֵ
		{               //���ú�������Ϊ�Ƚϵ������������֧���ϵ�����ڴ�������ʱ��Ҳ�Ǵ�����
			domRel = 3; //v_Chromo[i],v_Chromo[j]������������Ķ��󼴵�i������͵�j�����󣬽�ʵ�δ����β�A��B�����ô��ݣ��ҳ����ã�
			domRelation(v_Chromo[i], v_Chromo[j], domRel);//���ڶ��������� �ж�A��B֧���ϵ �ĺ�����void CGenetic::domRelation(const CIndividual& A, const CIndividual& B, int& domRel)
			if (domRel == 1)//ǰ�����ں���      ����ֵ=1����ʾ֧�䣻
			{   //������.������ ���� ���еı�������v_dominationSet�Ƕ������������ʹ��push_back()β�巨��ֵ
				v_Chromo[j].domination_count++;//�� �������v_Chromo[j] �� ����domination_count����֧����� ++
				v_Chromo[i].v_dominationSet.push_back(j);//��ǰ�߶���v_Chromo[i] �� ����֧���б���v_dominationSet β�� һ�� ���ߵĶ����
			}
			else if (domRel == -1)///ǰ�߲��ں���    ����ֵ=-1����ʾ��֧��
			{
				v_Chromo[i].domination_count++;//��ǰ�����v_Chromo[i] �� ����domination_count����֧����� ++
				v_Chromo[j].v_dominationSet.push_back(i);//�ʺ������v_Chromo[j] ������֧�伯��v_dominationSet β�� һ�� ǰ�ߵĶ����
			}//����ֻ������������֧���뱻֧��Ĺ�ϵ������Ӱ�������֧�������֧���б��ϣ�����doRem1=0����ȣ�����domRe1=2(��֧��)������
		}
	}//���� ���v_Chromo��Ⱥ�� ÿ������� ��֧�������֧���б�

	//rank the population  //CRankSequ���� ���������� �� ����������Ⱦɫ����chromoNo������ֵrankSequ��ӵ���Ⱦ���croDiversity��Ŀ��ֵv_robjective
	vector <CRankSequ>().swap(v_rankSequ);  //����swap�����ڴ棬v_rankSequ��ʱ�ĳ���Ϊ0���൱�ڳ�ʼ�������ݺ������򣬲�����ϵĶ���
	rankLevel = 1;	//��ʼ�� ��ţ����ŵ�һ��
	while (1)//while��1��ָ��ѭ����Զִ����ȥ.��������break;������ѭ����//���whileѭ�����Ǹ��ֲ�Ĺ���
	{                 //���ҷֲ���̣������һ��v_CRankSequ������������ֵΪ1�Ķ����2��3��ô�ţ����Ҹ��������ı���chromoNo,rankSequ,croDiversity,v_robjective
		bt = false;   //����ָ��!! ��Ϊ�������ר�ű�֧�����Ϊ0�Ķ������ڽ�����һ���������б�֧�����-1�Ĳ�������һ��Ϊ0�Ĳ�������ѡ�� 
		v_domZero.resize(0);//����ָ�� ���汻֧�����Ϊ0�Ķ���� ������domZero ����Ϊ0��
		for (i = 0; i < v_Chromo.size(); i++)//�����ж�ÿ�������Ƿ�֧�����=0����:����������������v_rankSequ�͵�ǰ֧�����=0����v_domZero��
		{    //ͬʱ����v_Chromo��v_rankSequ�����ĳ�Ա������rank��chromoNo,rankSequ,rankLevel,v_rObjValue
			if (v_Chromo[i].domination_count == 0)//��v_Chromo����ĵ�i����� ��������֧�������Ϊ0���ͻ��ֵ���ǰ��������һ������ʱ���ǵ�һ��
			{//��Ҫ��ΪCRankSequ�����еľ������t��Ӧ�ı�����ֵ��ͬʱ��t��������v_CRankSequ������ʱ�����Ź����Ŷ��t������ѡ��
				//rankLevel����CIndividual�ж�Ӧ���� rank�� ����CRankSequ�ж�Ӧ����rankSequ
				CRankSequ t;//����һ���������t���������԰��� chromoNo��rankLevel�� v_rObjValue;����ٰѶ���ŵ�rankSequ������                
				v_Chromo[i].rank = rankLevel;//��ǰrankLevelֵ ��ֵ�� v_Chromo�Ķ���i�� ����rank��
				t.chromoNo = i;//�� �����i ��ֵ�� �ö���t�� Ⱦɫ����chromoNo
				t.rankSequ = rankLevel;//����ǰrankLevelֵ ��ֵ�� CRankSequ�Ķ���t  ����rankSequֵ��
				for (j = 0; j < number_of_objectives; j++)
				{
					objValue = v_Chromo[i].v_objective_value[j];//��v_Chromo����i���� ��ȡ ÿ��Ŀ��ֵ
					t.v_rObjValue.push_back(objValue);//�ٸ�ֵ ������t ��v_rObjValue���������Ŀ�����Ҫһ������vector <double> v_rObjValue;
				}
				v_rankSequ.push_back(t);//���������t����v_rankSequ��
				bt = true;//ֻҪ��һ���б�֧�����=0���Ϳ��Ը��������󣬽�����һ���ɸѡ
				v_domZero.push_back(i);//�������i����v_domZero�����У�����1��3��5�ı�֧�����=0����ô1,3,5����Ÿ�ֵ��������
			}
			//�������if���Ҳ������CIndividual��CRankSequ��֮��Ĺ�ϵ��CRankSequ��chromoNo��v_rObjValue���Ǵ�CIndividual��ȡ
		}//������������ֱ���V_Chromo[i]��t
		//�������forѭ�������ǰ����еı�֧�����=0�Ķ��ҳ���������У�����Ϊ����t,�ٽ�����t����rankSequ���飬����Ӧ�Ķ����i����v_domZero����
	  //�Ҹ�ֵ��v_Chromo�е�rank����=rankLevel�� CRankSequ�е�t��rankSequ=rankLevel,chromoNo=i,v_robjctive=��v_Chromo[i]�ǻ�ȡ��objective
		if (bt == false)//һ��ʼ��ʼ��Ϊfalse��ֻҪ�浽һ����֧�����Ϊ0�ģ���һ�������ݣ�����ô�Ϳ���true;����true��������䣬ɸѡ��һ��
		{
			break;//���û��==0�ģ������-1�ˣ���ֹ�ظ��ж����õ�-1������ôû��true,Ĭ�ϳ�ʼfalse������������whileѭ�����ֲ����
		}
		if (bt == true)//��trueʱ������һ�㣬�Ұ���һ�㱻֧�����=0�Ķ�ɸ�����ˣ���ô�����ϲ㿪ʼɸѡ��һ�㣺���ǰ���һ��ĸ�����ӵ�е�֧���б��еĸ���ı�֧�����-1
		{
			rankLevel++;//�²����++����һ����� ��֧���б� �����ĸ���ı�֧�����-1������A��B�ǵ�һ�㣬A֧��C,D,E�� B֧��C��F����ôC-2��D��E��F-1��
			sizeZero = v_domZero.size();//��ǰ��֧�����=0������v_domZero �� ���ȣ����ж��ٸ�����ѽ
			for (int j = 0; j < sizeZero; j++)//�ж��ٸ����ݾͱ������ٴ�
			{
				domChromoNo = v_domZero[j];//��ԭ�������ȥ��t�Ķ������ȡ����ֵ��domChromoNov_domZero[0]=1��v_domZero[1]=3��v_domZero[2]=5��
				v_Chromo[domChromoNo].domination_count = -1;//��ԭ����֧�����=0�� ���� �� ��֧�������Ϊ-1����Ϊ��ǰif�������Խ��������Ǹ��ֲ��жϣ�
				size = v_Chromo[domChromoNo].v_dominationSet.size();//��ȡ��֧�����=0�Ķ��� �� ֧���б��� �� ����           //��Щ=0���Ѿ��жϹ��ˡ�
				for (int k = 0; k < size; k++)
				{
					domedChromoNo = v_Chromo[domChromoNo].v_dominationSet[k];//�ѱ�֧�����ı��ȡ���� ��ֵ�� domedChromoNo
					v_Chromo[domedChromoNo].domination_count--;//��֧�����ı�֧�����-1
				}
			}
		}//���if���󣬲�����һ����֧�����=0�Ķ��󣬽���whileѭ��������ִ�������Ǹ�if (v_Chromo[i].domination_count == 0)
	}                                                                                          //�ж���һ������Щ����
	//�������whileѭ�����Ƿֲ�ģ���ԭ����Ⱥ�еĶ�����֮ǰ�ı�֧�������֧�伯��ָ����зֲ㣻����v_RankSequ����������F1,F2...˳�����δ洢

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//v_RankSequ�����洢һ�Ŷ�����Щ�����ǰ���rankֵ����ģ���ǰ�����ǵ�һ��ģ����ż����ǵڶ��㣬ֱ����󼸸����������һ�㡣
	//v_RankSequ�����еĶ������԰���:chromoNo����ţ�rankSequ��ֵ��ӵ���Ⱦ����Ŀ��ֵ
	////���v_rankSequ����
	//for (int cn = 0; cn < v_rankSequ.size(); cn++)
	//{
	//	cout << v_rankSequ[cn].chromoNo << " ";
	//	cout << v_rankSequ[cn].rankSequ << endl;
	//}
	//cout << endl;

	//������Ҫ��ȡһ���ж��ٸ��أ��ҳ�����rankSequ����	
	cluster_number = v_rankSequ[number_of_individuals - 1].rankSequ;
	//cout << "cluster_number = " << cluster_number << endl;
	//Ȼ���ȡÿ���ذ�����Щ���壬����ͬrankSequ����ͬһ��
	int num_c = 0;
	vector <vector<CRankSequ>>().swap(v_cluster);//�������,��ʼ��
	for (int cn = 1; cn <= cluster_number; cn++)
	{
		vector <CRankSequ> v;
		v_cluster.push_back(v);

		for (int i = num_c; i < v_rankSequ.size(); i++)
		{
			if (v_rankSequ[i].rankSequ == cn)
			{
				CRankSequ clu;
				clu.chromoNo = v_rankSequ[i].chromoNo;//��ȡ��ҵ��
				clu.rankSequ = v_rankSequ[i].rankSequ;//��ȡrankֵ
				clu.v_rObjValue = v_rankSequ[i].v_rObjValue;//��ȡĿ��ֵ
				v_cluster[cn - 1].push_back(clu);//���ö�����뵱ǰ���б�
				num_c++;
			}
			else
			{
				break;
			}
		}
	}
	//cout<<"ÿ���ذ����ĸ��弰��غź�Ŀ��ֵ"<<endl;
	//for (int i = 0; i < v_cluster.size(); i++)
	//{
	//	for (int j = 0; j < v_cluster[i].size(); j++)
	//	{
	//		cout << v_cluster[i][j].chromoNo << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < v_cluster[i].size(); j++)
	//	{
	//		cout << v_cluster[i][j].rankSequ << " ";
	//	}
	//	cout << endl;
	//	for (int j = 0; j < v_cluster[i].size(); j++)
	//	{
	//		for (int k = 0; k < v_cluster[i][j].v_rObjValue.size(); k++)
	//		{
	//			cout << v_cluster[i][j].v_rObjValue[k] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
	//system("pause");

	best_size = cluster_number;
}

void CGenetic::domRelation(const CIndividual& A, const CIndividual& B, int& domRel)//��CGeneticԴ�ļ�ֻ����������ʵ�ֲ���
{                 //������ const       ���� &�βΣ�����ı�ʵ�ε�ֵ���ʼ���const���������ô��ݣ�ʵ�ε�ֵ�ᷢ���ı�
	int i;        //A��B������������Ϊ���嶼�кܶ��������һ��ʼ�ͰѸ��彨��һ���ࣻ���������������������
	int equalCount, lessCount, greaterCount;//����ʵ���� ������� ʱ���βθ�ʽ�� �������� ���� �β���
	equalCount = 0;//��ʼ��
	lessCount = 0;//��ʼ��
	greaterCount = 0;//��ʼ��
	for (i = 0; i < number_of_objectives; i++)//���Ŀ��Ƚ�
	{
		if (A.v_objective_value[i] == B.v_objective_value[i])//������.������ͨ��[]��ʽ����vector�����е�Ԫ��
		{
			equalCount++;//�����������Ŀ��ֵ��ȣ�����ȴ���++
		}
		if (A.v_objective_value[i] < B.v_objective_value[i])
		{
			lessCount++;//��A�����Ŀ��ֵ<B�����Ŀ��ֵ����less����++
		}
		if (A.v_objective_value[i] > B.v_objective_value[i])
		{
			greaterCount++;//��A�����Ŀ��ֵ>B�����Ŀ��ֵ����greater����++
		}
	}
	if (equalCount == number_of_objectives)    //two solutions are equal in each objective.
	{
		domRel = 0;//�������������Ŀ��ֵ�����
	}
	else if ((equalCount + lessCount == number_of_objectives) && lessCount > 0)  // the first solution dominates the second solution.
	{        //0+2=2,2>0����1+1=2,1>0;less����ã���֧�䣨���1��A������Ŀ��ֵ<B�ģ�equalCount=0����ʱlessCount=number_of_objectives;��
		domRel = 1;            //�����2��A������Ŀ��ֵ��=B�ģ�����1������ʱequalCount=1��Ҳ��<B�ģ�lessCount=number_of_objectives-1;��
	}
	else if ((equalCount + greaterCount == number_of_objectives) && greaterCount > 0) //the first solution is dominated by the second solution.
	{       //0+2=2,2>0����1+1=2,1>0;great�����ʱ�֧�䣨���1��A������Ŀ��ֵ>B�ģ�equalCount=0����ʱgreaterCount=number_of_objectives;��
		domRel = -1;     //�����2��A������Ŀ��ֵ�� = B�ģ�����1������ʱequalCount = 1��Ҳ�� >B�ģ�greaterCount = number_of_objectives - 1; ��
	}
	else         //two solutions are non-dominated each other.
	{
		domRel = 2;//1��less+1��great��//AĿ��ֵ����<B��Ҳ��>B�ģ���ʱ�����������ڷ�֧���ϵ
	}
}