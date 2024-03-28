#include "Genetic.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"

void CGenetic::next_pop()
{
	//cout << "------------6����һ����Ⱥ-----------" << endl;
	for (int i = 0; i < v_new_individuals.size(); i++)
	{
		v_Chromo.push_back(v_new_individuals[i]);
	}
	//cout << "�ϲ���Ⱥ" << endl;
	//for (int i = 0; i < v_Chromo.size(); i++)
	//{
	//	cout << "MergeIndividual = " << i + 1 << endl;
	//	int next_total_lenth1 = v_Chromo[i].v_chromosome1.size();
	//	for (int j = 0; j < number_of_jobs1; j++)
	//	{
	//		cout << v_Chromo[i].v_chromosome1[j].factory_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs1; j < next_total_lenth1; j++)
	//	{
	//		cout<<v_Chromo[i].v_chromosome1[j].job_number << " ";
	//	}
	//	cout << endl;
	//	int next_total_lenth2 = v_Chromo[i].v_chromosome2.size();
	//	//cout << "---machine assignment vector---" << endl;
	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//	{
	//		cout << v_Chromo[i].v_chromosome2[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs2 * number_of_operations; j < next_total_lenth2; j++)
	//	{
	//		cout << v_Chromo[i].v_chromosome2[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	//cout << "---objective value---" << endl;
	//	for (int ob = 0; ob < number_of_objectives; ob++)
	//	{
	//		cout <<v_Chromo[i].v_objective_value[ob] << " ";
	//	}
	//	cout << endl<<endl;
	//}
	//system("pause");


	//////��2N��������зֲ�
	int domRel, rankLevel, size, sizeZero, domChromoNo, domedChromoNo;
	double objValue;
	bool bt;
	vector <int> v_domZero;//�������������汻֧�����Ϊ0�ĸ��壨���ǵ�ָ��һ�㣬�п����Ǻ�����һ������һ�㣩

	//initialize
	for (int i = 0; i < 2 * number_of_individuals; i++)//��ʼ����Ⱥ��ÿ������ı�֧�������֧���б��ϣ���������0
	{
		v_Chromo[i].domination_count = 0;//��Ⱥ�е�i������� ��֧����� ��ʼ��Ϊ0
		v_Chromo[i].v_dominationSet.resize(0);//��Ⱥ�е�i������� ֧���б��� ��ʼ������Ϊ0
		v_Chromo[i].rank = 0;//��Ⱥ�е�i������� ���� ��ʼ��Ϊ0
	}
	//Ȼ������� ÿ������ ���� �жϸ���֧���ϵ������Ϊ������ ��֧�����domination_count ��֧���б���v_dominationSet ��ֵ��
	size = v_Chromo.size();//��Ⱥ��ģ��С       ��NSGA2������ÿ�����嶼��һ��������һ�������������ԣ������ڵ�������CIndividual��
	for (int i = 0; i < 2 * number_of_individuals - 1; i++)//�˹��̻�ȡv_Chromo��Ⱥ��ÿ�� ����� ��֧����� �� ֧����������ļ���
	{
		for (int j = i + 1; j < 2 * number_of_individuals; j++)//���������໥�Ƚ����е�Ŀ��ֵ
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
		for (int i = 0; i < 2 * number_of_individuals; i++)//�����ж�ÿ�������Ƿ�֧�����=0����:����������������v_rankSequ�͵�ǰ֧�����=0����v_domZero��
		{    //ͬʱ����v_Chromo��v_rankSequ�����ĳ�Ա������rank��chromoNo,rankSequ,rankLevel,v_rObjValue
			if (v_Chromo[i].domination_count == 0)//��v_Chromo����ĵ�i����� ��������֧�������Ϊ0���ͻ��ֵ���ǰ��������һ������ʱ���ǵ�һ��
			{//��Ҫ��ΪCRankSequ�����еľ������t��Ӧ�ı�����ֵ��ͬʱ��t��������v_CRankSequ������ʱ�����Ź����Ŷ��t������ѡ��
				//rankLevel����CIndividual�ж�Ӧ���� rank�� ����CRankSequ�ж�Ӧ����rankSequ
				CRankSequ t;//����һ���������t���������԰��� chromoNo��rankLevel�� v_rObjValue;����ٰѶ���ŵ�rankSequ������                
				v_Chromo[i].rank = rankLevel;//��ǰrankLevelֵ ��ֵ�� v_Chromo�Ķ���i�� ����rank��
				t.chromoNo = i;//�� �����i ��ֵ�� �ö���t�� Ⱦɫ����chromoNo
				t.rankSequ = rankLevel;//����ǰrankLevelֵ ��ֵ�� CRankSequ�Ķ���t  ����rankSequֵ��
				for (int j = 0; j < number_of_objectives; j++)
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
	//�������whileѭ�����Ƿֲ�ģ���ԭ����Ⱥ�еĶ�����֮ǰ�ı�֧�������֧�伯��ָ����зֲ㣻����v_RankSequ����������F1,F2...

	/////���v_rankSequ����
	//for (int cn = 0; cn < v_rankSequ.size(); cn++)
	//{
	//	cout << v_rankSequ[cn].chromoNo << " ";
	//	cout << v_rankSequ[cn].rankSequ << endl;
	//}

	select();
	///////select N individuals from 2N ����rankֵ��ӵ���Ƚ���ɸѡ


	//////�����һ����Ⱥ
	//for (int i = 0; i < v_Chromo.size(); i++)
	//{
	//	cout << "NextIndividual =" << i + 1 << endl;
	//	int next_total_lenth1 = v_Chromo[i].v_chromosome1.size();
	//	for (int j = 0; j < number_of_jobs1; j++)
	//	{
	//		cout << v_Chromo[i].v_chromosome1[j].factory_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs; j < next_total_lenth1; j++)
	//	{
	//		cout << v_Chromo[i].v_chromosome1[j].job_number << " ";
	//	}
	//	cout << endl;
	//	int next_total_lenth2 = v_Chromo[i].v_chromosome2.size();
	//	//cout << "---machine assignment vector---" << endl;
	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
	//	{
	//		cout << v_Chromo[i].v_chromosome2[j].operation_number << " ";
	//	}
	//	cout << endl;
	//	for (int j = number_of_jobs2 * number_of_operations; j < next_total_lenth2; j++)
	//	{
	//		cout << v_Chromo[i].v_chromosome2[j].machine_number << " ";
	//	}
	//	cout << endl;
	//	cout << "---objective value---" << endl;
	//	for (int ob = 0; ob < number_of_objectives; ob++)
	//	{
	//		cout << v_Chromo[i].v_objective_value[ob] << " ";
	//	}
	//	cout << endl << endl;
	//}
	//cout << endl;
}

void CGenetic::select()//���ⶨ��ѡ��������2N��������ѡ��N�����壻
{   //�ȿ�����rank��rank the population���룻ֻ�и���֧���ϵ������ֲ�ã����ܸ�����Щָ����ѡ��
	int i, j;                                                             //����Ⱦɫ�壬Ŀ��ֵ������֧�������֧�伯�ϵȱ���
	vector <CIndividual> v_sele;//����һ������v_select�����ڷű�ѡ�еĶ����Զ�������Cindividual��ͨ������ɷ��ʹ��ڸ���ı���
	vector<CIndividual>().swap(v_sele);

	int sizeSeledNum;//��ģ
	CIndividual t;//����һ���������һ������ĸ��� ������Ϊt
	int rankLevel = 1;//��ʼ��Ϊ1����Ϊ��ѡ��һ���
	int total, num;
	int start, end;
	int chromoNo;//Ⱦɫ����
	start = 0;
	num = 0;
	while (1)//while��1��ָ��ѭ����Զִ����ȥ.��������break;������ѭ����
	{
		num = 0;
		for (i = start; i < 2 * number_of_individuals; i++)
		{
			if (v_rankSequ[i].rankSequ == rankLevel)//���ȣ�v_rankSequ�Ǹ������������飬��[]��ʽ���Է���i����
			{  //v_rankSequ���Զ�����������<CRankSequ>����i�Ƕ���ͨ��.�������ķ�ʽ����CRankSequ���е�rankSequ����
				num++;
				end = i;                  //��ֹ���е㶼�ڵ�һ����
			}
			else
			{
				end = i - 1;
				break;//break����������ķ��ѭ������������
			}
		}
		sizeSeledNum = v_sele.size();//�����Ĵ�С������ĳ��ȣ�һ��ʼ�����Ĵ�СӦ����0��//��һ��ʱ�򣬳���=��һ�������Ŀ
		total = sizeSeledNum + num;//num��ֵ��������ѭ������ִ�еĴ��������ж��ٸ������ڵ�ǰ��

		//һ��ʼ�����ȿ���rankSequ=1��total����������һ��rankLevel�Ĺ�����N
		if (total < number_of_individuals)//С��N
		{
			//[start,end]�е����и��屣������
			for (j = start; j <= end; j++)
			{
				chromoNo = v_rankSequ[j].chromoNo;//��ȡ v_rankSequ����ĵ�j������ �� ����Ⱦɫ����chromoNo
				t = v_Chromo[chromoNo];//��v_Chromo���鼴��Ⱥ�еı��ΪchromoNo�Ķ��� ��ֵ�� �������t
				v_sele.push_back(t);//��������� t����� v_sele����
			}
			start = end + 1;//��һ�㿪ʼ=��һ�����+1
			rankLevel++;//��ʼ��һ�㣻��Ϊ��һ����Ŀ����N����ֻ�ܽ�����һ��Ѱ�ң�
			continue;//��ʱ����������ѡ��һ�㣬��ô����ѭ��������δִ�е���䣬����while��1����
		}
		if (total == number_of_individuals)//����N
		{
			//[start, end]�е����и��屣������
			for (j = start; j <= end; j++)
			{
				chromoNo = v_rankSequ[j].chromoNo;//��ȡ v_rankSequ����ĵ�j������ �� ����Ⱦɫ����chromoNo
				t = v_Chromo[chromoNo];//��v_Chromo���鼴��Ⱥ�еı��ΪchromoNo�Ķ��� ��ֵ�� �������t
				v_sele.push_back(t);//��������� t����� v_sele����
			}
			break;//��ʱ���ˣ�����whileѭ������
		}
		if (total > number_of_individuals)//����Nʱ����Ҫ����ӵ���Ⱦ����жϣ���ѡ��ʣ��λ�ø���
		{
			//�������ܶȺ�������ѡ�񣨵��Ĳ�����ӵ���ȴ�����Ƚ���ʣ��λ�á�			
			crodiversity(v_rankSequ, start, end);//������ CRankSequ�ࣨ�Զ����������ͣ��Ķ��� int�͵����� int�͵�����
			end = number_of_individuals - 1;//0��ʼ�ģ�N�����壬��end=N-1
			for (int j = start; j <= end; j++)
			{
				chromoNo = v_rankSequ[j].chromoNo; // ��ȡ v_rankSequ����ĵ�j������ �� ����Ⱦɫ����chromoNo
				t = v_Chromo[chromoNo];//��v_Chromo���鼴��Ⱥ�еı��ΪchromoNo�Ķ��� ��ֵ�� �������t
				v_sele.push_back(t);//��������� t����� v_sele����
			}
			break;//��ʱ���ˣ�����whileѭ������
		}
	}
	//ѡ����ĸ�����������v_sele����ԭ������v_Chromo��
	vector <CIndividual>().swap(v_Chromo);//����swap�����ڴ棬v_Chromo��ʱ�ĳ���Ϊ0
	v_Chromo.assign(v_sele.begin(), v_sele.begin() + number_of_individuals);//��v_slec�����е�ֵ��assign��ֵ��v_Chromo����ʱ����ΪN

}

void CGenetic::crodiversity(vector <CRankSequ>& v_rankSequ, int& start, int& end)
{                         //v_rankSequ������=���飬���鴫��ʱ��ֻ��д�����������ɣ��ټ����÷���&
	int i, j;
	double minObjValue, maxObjValue, preObjValue, nextObjValue;//��Сֵ�����Ŀֵ��ǰֵ������
	double dtemp;
	CRankSequ t;

	for (i = start; i <= end; i++)
	{
		v_rankSequ[i].croDiversity = 0.0;//��ʼ�� ĳһ��ĸ��� �� ӵ�����ܶ�=0��
	}
	//order the individuals in the same rank as non-dereasingly 
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//����ÿ��Ŀ��
	{
		for (i = start; i <= end - 1; i++)//�������У�������ð������
		{
			for (int j = i + 1; j <= end; j++)
			{
				dtemp = v_rankSequ[i].v_rObjValue[objNo];//��ȡi�����Ŀ��ֵ
				if (dtemp > v_rankSequ[j].v_rObjValue[objNo])//��j�����Ŀ��ֵ�Ƚ�
				{
					t = v_rankSequ[i];//��Ϊ�Ƕ��󻻣��Ҷ��������е����Լ���ǰĿ���µ�Ŀ��ֵҲ���ű䶯��
					v_rankSequ[i] = v_rankSequ[j];//���ö���t���������������ˣ�
					v_rankSequ[j] = t;//����������Ŀ��ֵС�Ķ��󱻻���ǰ�棬Ŀ��ֵ��Ķ��󱻻�������
				}
			}
		}
		////�������������start��Ӧ��ǰĿ���µ�Ŀ��ֵС�Ķ���end����Ŀ��ֵ��Ķ��� ĳһ��������ٽ���� �� ӵ���Ⱦ��� =�����
		v_rankSequ[start].croDiversity = INF_DOUBLE_MAX;//�ڵ�ǰĿ���£���СĿ��ֵ���ڵĶ�����ܶ�Ϊ���޴�ֵ
		v_rankSequ[end].croDiversity = INF_DOUBLE_MAX;//�ڵ�ǰĿ���£����Ŀ��ֵ���ڵĶ�����ܶ�Ϊ���޴�ֵ

		minObjValue = v_rankSequ[start].v_rObjValue[objNo];//��ȡ��ǰĿ�����СĿ��ֵ��//���ù���ͬһ���ϵ���ֵ����ȫ�֣��������Ǹ�����
		maxObjValue = v_rankSequ[end].v_rObjValue[objNo];//��ȡ��ǰĿ������Ŀ��ֵ��//��Ӱ����

		for (i = start + 1; i <= end - 1; i++)//��ÿ��������ܶȣ�start��end�ܶ�Ϊ�������Ϊ���ǵĶ���������������ֵ��
		{   //��Ϊ�漰ǰһ������i-1����i��start+1��ʼ��ͬ���漰��һ������i+1,��i��end-1����
			preObjValue = v_rankSequ[i - 1].v_rObjValue[objNo];//ǰһ������ �� ��ǰĿ���µ�Ŀ��ֵ
			nextObjValue = v_rankSequ[i + 1].v_rObjValue[objNo];//��һ������ �� ��ǰĿ���µ�Ŀ��ֵ
			v_rankSequ[i].croDiversity = v_rankSequ[i].croDiversity + abs((double)(nextObjValue - preObjValue)) / ((maxObjValue - minObjValue)*1.0);
			//�ܶ�=��ǰһ�������Ŀ��ֵ-��һ�������Ŀ��ֵ��/�����Ŀ��ֵ-��СĿ��ֵ����fabs������float��double�����ֵ
		}
		//�����������Ŀ�������ж�����ܶ�
	}
	//���� ������ж����ӵ���Ⱦ���
	for (i = start; i <= end - 1; i++) //order non-increasingly as cronwding distance //���ո����ܶȣ���v_rankSequ�����еĸ��彵������
	{
		for (j = i + 1; j <= end; j++)//�Ƚ��������������ӵ���Ⱦ��룻��������
		{
			dtemp = v_rankSequ[i].croDiversity;
			if (dtemp < v_rankSequ[j].croDiversity)
			{
				t = v_rankSequ[i];//�����������Ƚ�ӵ���Ⱦ��룬����Ӧ���󻥻���
				v_rankSequ[i] = v_rankSequ[j];//��ӵ���Ⱦ���ֵС�Ķ�����ǰ�棬ӵ���Ⱦ���ֵ��Ķ����ں��棻
				v_rankSequ[j] = t;//�������󣬹��ö���t���������������ˣ�
			}
		}
	}

}