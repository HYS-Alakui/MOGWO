//#include "Genetic.h"
//#include "Individual.h"
//#include "rankSequ.h"
//#include "headfile.h"
//
////��cpp��Ҫ���н���ͱ��������
//
////������������S1��O1,V1��,S2��02,V2��,O1��O2���ֽ������㽻�棨������죩��V1��V2���ֽ��ж����ƾ��Ƚ��棨������죩��
////���棺ע��Ⱦɫ�峤�ȣ�ǰһ�룺ѡ����ĸʹ�ý�������������һ�룺ʹ�ö������������ж�ѡ��
//void CGenetic::cross()
//{
//	int i, j, k;
//	int croTimes, irandNum1, irandNum2, domRel;//���彻��������������1�Ķ���ţ��������2�Ķ���ţ�֧����
//	CIndividual mothIndiv, fathIndiv, chIndiv1, chIndiv2, indiv1, indiv2;//�������ĸ�ף����ף��Ӵ�1���Ӵ�2������2������2
//	int cutpoint1, cutpoint2;//�е㣻��ʵÿ���������һ���������������Լ�������,v_chromosome��v_objective_value��
//	int temp;
//	int jobNo;
//	int index;
//	bool bt;
//
//	vector <int> v_parNum;//����һ�� ���� ��ĸ �� ������Ϊɶ�Ǵ�����ĸ�����أ���Ϊ�ܶ�̬�����ڴ棻�漰����ִ��ѡ��ĸ��ʱ��
//	croTimes = number_of_individuals / 2;//���������//������������Ŀ�ǣ�1+2���������ôֻ��������2��Ԫ�صĴ�ͳ����Ͳ���ʹ��
//	for (i = 0; i < croTimes; i++)
//	{
//		//binary tourment seletciton//
//		vector <int>().swap(v_parNum);
//		vector <int>().swap(chIndiv1.v_chromosome);
//		vector <double>().swap(chIndiv1.v_objective_value);
//		vector <int>().swap(chIndiv2.v_chromosome);
//		vector <double>().swap(chIndiv2.v_objective_value);
//		//����swap,�����������ڴ棻�൱��һ����ʼ��
//
//		for (j = 0; j < 2; j++)//��Ϊѡ�����õĸ��嵱��ĸ���ʽ�������ѭ�����ų� һ���Ӿ�ѡ�����������Ƿ�֧���ϵ �����Ŷ��
//		{   //���������ֱ��break���Ϳ���������Ϊһ�ξ�ѡ�������õĸ�������������һ����֧��/��֧��/��ͬ����ʱ��������1�����壬
//			//���ڶ����Ƿ�֧�䣬���������2����ô����������Ŀ��1+2�����Ҳ��Ҫ��������Ϊ������ֻ��ѡ������ǰ����Ԫ�ص���ĸŶ��
//			irandNum1 = rand() % number_of_individuals;//����������󣨸��壩1�Ķ����
//			irandNum2 = rand() % number_of_individuals;//����������󣨸��壩2�Ķ����
//			while (irandNum1 == irandNum2)//��ѡ�еĶ����ͬ����ѡ�ж��󣨸��壩ͬ
//			{
//				irandNum2 = rand() % number_of_individuals;//���²������󣨸��壩2�Ķ����
//			}
//			indiv1 = v_Chromo[irandNum1];//���ݶ���ţ���ȡ��1�����󣻷���������� ���ú��� �ж����������ϵ
//			indiv2 = v_Chromo[irandNum2];//���ݶ���ţ���ȡ��2�����󣻽���ѡ����õĸ��壬��ֻ�ж���ţ��޷���ȡ���߹�ϵѽ
//
//			domRelation(indiv1, indiv2, domRel);//�ж��������󣨸���Ĺ�ϵ����ѡ������ 1�� �õ� ���� ���븸ĸ������
//			if (domRel == 1 || domRel == 0)//������1 ֧������ ����2��������1�ã�
//			{
//				v_parNum.push_back(irandNum1);//��ô�Ѹ���1�� ����� β�� �� ��ĸ������
//			}
//			else if (domRel == -1)//������1 �� ����2 ֧�䣬������2�ã�
//			{
//				v_parNum.push_back(irandNum2);//��ô�Ѹ���2�� ����� β�� �� ��ĸ������
//			}
//			else if (domRel == 2)//�����ڷ�֧���ϵ����ôֻ������һ��ѭ�����ɣ�ֱ�ӽ�����������
//			{
//				v_parNum.push_back(irandNum1);//�Ķ���� β�� �� ��ĸ�����У���ʱ�Ѿ��и�ĸ��
//				v_parNum.push_back(irandNum2);//����ǰ��������� ��ĸ����������
//				break;                        //��ĸѡ����̽�������ֱ������forѭ��
//			}
//		}
//		//���� ��ѡ�� ��ĸ �Ĺ��� 
//
//		irandNum1 = v_parNum[0];//��ȡ ��ĸ�����е�һ��Ԫ�ص� �����;��[ ]��ʽ�����������е�Ԫ��
//		irandNum2 = v_parNum[1];//��ȡ ��ĸ�����е�һ��Ԫ�ص� �����
//		fathIndiv = v_Chromo[irandNum1];//���� ����� ��ȡ ���׸���
//		mothIndiv = v_Chromo[irandNum2];//���� ����� ��ȡ ĸ�׸���
//
//		for (j = 0; j < 2 * number_of_jobs; j++)
//		{
//			chIndiv1.v_chromosome.push_back(0);//��ʼ�� �Ӵ�1 �� Ⱦɫ�壬Ⱦɫ���ϵ�2* number_of_jobs�����򣬶�β��0
//			chIndiv2.v_chromosome.push_back(0);//��ʼ�� �Ӵ�2 �� Ⱦɫ�壬Ⱦɫ���ϵ�2* number_of_jobs�����򣬶�β��0
//		}
//
//		//(1)���ø�ĸ���� ���� ��� �Ӵ�1��2 ��[0, number_of_jobs)�������ֵ��
//		cutpoint1 = rand() % number_of_jobs;//�������һ���е�1���е�1�ķ�Χ[0 , number_of_jobs-1]
//		cutpoint2 = rand() % number_of_jobs;//�������һ���е�2���е�2�ķ�Χ[0 , number_of_jobs-1]
//		while (cutpoint1 == cutpoint2)//�������е���ͬ
//		{
//			cutpoint2 = rand() % number_of_jobs;//�����²���һ���е�2
//		}                         //���� ��Ϊ ���е�1���е�2��ǰ�棬ֱ���ҷ����������
//		if (cutpoint1 > cutpoint2)//���е�1���е�2����
//		{
//			temp = cutpoint1;
//			cutpoint1 = cutpoint2;//����л�������
//			cutpoint2 = temp;
//		}
//
//		for (j = 0; j < cutpoint1; j++)//ע��cutpoint1�ǿ����䣬�����ҵ���ϵ���ҵ��ȡ�����ģ�
//		{
//			jobNo = fathIndiv.v_chromosome[j];//��ȡ����Ⱦɫ����[0,cutpoint1)�������ҵ
//			chIndiv1.v_chromosome[j] = jobNo;//������[0,cutpoint1)�ϵ���ҵ ���� ���Ӵ�1��ͬλ��
//			jobNo = mothIndiv.v_chromosome[j];//��ȡĸ��Ⱦɫ����[0,cutpoint1)�������ҵ
//			chIndiv2.v_chromosome[j] = jobNo;//��ĸ��[0,cutpoint1)�ϵ���ҵ ���� ���Ӵ�2��ͬλ��
//		}
//		for (j = cutpoint2; j < number_of_jobs; j++)
//		{
//			jobNo = fathIndiv.v_chromosome[j];//��ȡ����Ⱦɫ����[cutpoint2��number_of_jobs)�������ҵ
//			chIndiv1.v_chromosome[j] = jobNo;//������[cutpoint2��number_of_jobs)�ϵ���ҵ ���� ���Ӵ�1��ͬλ��
//			jobNo = mothIndiv.v_chromosome[j];//��ȡĸ��Ⱦɫ����[cutpoint2��number_of_jobs)�������ҵ
//			chIndiv2.v_chromosome[j] = jobNo;//��ĸ��[cutpoint2��number_of_jobs)�ϵ���ҵ ���� ���Ӵ�2��ͬλ��
//		}
//		//���� �ǽ���ĸ �����е� �������ҵ ֱ�ӿ��� ���Ӵ�1���Ӵ�2����ͬλ��
//
//		//���濪ʼ����Ӵ�1���Ӵ�2[cutpoint1,cutpoint2)֮�����ҵ���Ӵ�1��ʣ�ಿ�ִ�ĸ�������ã��Ӵ�2������
//		index = cutpoint1;//��cutpoint1λ�ÿ�ʼ��䣬����ѭ�����λ�ñ���䣬��index++�����������һ��
//		for (j = 0; j < number_of_jobs; j++)
//		{
//			jobNo = mothIndiv.v_chromosome[j];//��ĸ����ÿ����ҵ���Ӵ�1���е���ҵ�Ƚ�;
//			bt = false;
//			for (k = 0; k < cutpoint1; k++)//����ǰĸ����ҵ���Ӵ�1����[0,cutpoint1)��ҵ�Ƚ�
//			{                              //��һֱ��ͬ����������ִ�У��ж����Ӵ�1����[cutpoint2,number_of_jobs)��ҵ�Ƚ�
//				if (jobNo == chIndiv1.v_chromosome[k])//������һ����ͬ�ģ���ô��ĸ����ҵ�϶����ܼ��������Ӵ�1
//				{
//					bt = true;//��true��ֱ��break����������ǰ���forѭ�������ý������Ӵ�1[0,cutpoint1)����ʣ����ҵ�Ƚ���
//					break;//���ǿ��Խ���������[cutpoint2,number_of_jobs)��ҵ�Ƚϣ�ֻ����һֱ��true,Ҳ���ᱻ����
//				}         //�Ӵ�1��cutpoint1λ���ϣ�indexҲ���ֲ��䣬��������ֱ�������жϵ�ǰĸ����ҵ���¸���ҵ
//			}
//			for (k = cutpoint2; k < number_of_jobs; k++)//����ǰĸ����ҵ���Ӵ�1����[cutpoint2,number_of_jobs)��ҵ�Ƚ�
//			{                            //����ĸ����ҵ������������������ҵ��ͬ���ʿ��Լ����Ӵ�1���е�cutpoint1��һֱfalse
//				if (jobNo == chIndiv1.v_chromosome[k])//������һ����ͬ�ģ���ô��ĸ����ҵ�϶����ܼ��������Ӵ�1
//				{  //��true��ֱ��break����������ǰ���forѭ�������ý������Ӵ�1[cutpoint2,number_of_jobs)����ʣ����ҵ�Ƚ���
//					bt = true;//��ʱindex���ֲ��䣬����ִ����һ��forѭ���жϵ�ǰĸ����ҵ���¸���ҵ
//					break;
//				}
//			}
//			if (bt == false)//��һֱfalse��δ����true��˵����ǰĸ����ҵһֱ�������������ҵ��ͬ����
//			{
//				chIndiv1.v_chromosome[index] = jobNo;//����ĸ����ҵ����ҵ�ţ������Ӵ�1��ǰ��cutpoint1λ����
//				index++;//��ʱԭcutpoint1�Ѿ�������ˣ���++�����������һ��λ��
//			}
//		}//��������Ӵ�1[cutpoint1,cutpoint2)λ����ҵ����䣬��ĸ�׻�á�
//
//		//���½����Ӵ�2[cutpoint1,cutpoint2)λ����ҵ����䣬ֻ�����ǴӸ����ǻ�û���
//		index = cutpoint1;//��cutpoint1λ�ÿ�ʼ��䣬����ѭ�����λ�ñ���䣬��index++�����������һ��
//		for (j = 0; j < number_of_jobs; j++)
//		{
//			jobNo = fathIndiv.v_chromosome[j];//��������ÿ����ҵ���Ӵ�2�����е���ҵ�Ƚ�;
//			bt = false;
//			for (k = 0; k < cutpoint1; k++)
//			{
//				if (jobNo == chIndiv2.v_chromosome[k])//����ǰ������ҵ���Ӵ�2����[0,cutpoint1)��ҵ�Ƚ�
//				{                            //��һֱ��ͬ����������ִ�У��ж����Ӵ�2����[cutpoint2,number_of_jobs)��ҵ�Ƚ�
//					bt = true;//������һ����ͬ�ģ���ô�ø�����ҵ�϶����ܼ��������Ӵ�2
//					break;//��true��ֱ��break����������ǰ���forѭ�������ý������Ӵ�2[0,cutpoint1)����ʣ����ҵ�Ƚ���
//				}//���ǿ��Խ���������[cutpoint2,number_of_jobs)��ҵ�Ƚϣ�ֻ����һֱ��true,Ҳ���ᱻ�����Ӵ�1��cutpoint1λ��
//			}    //�ϣ�indexҲ���ֲ��䣬һֱ����ֱ�������жϵ�ǰĸ����ҵ���¸���ҵ
//			for (k = cutpoint2; k < number_of_jobs; k++)//����ǰ������ҵ���Ӵ�2����[cutpoint2,number_of_jobs)��ҵ�Ƚ�
//			{                       //���ø�����ҵ������������������ҵ����ͬ���ʿ��Լ����Ӵ�2���е�cutpoint1��һֱfalse
//				if (jobNo == chIndiv2.v_chromosome[k])//������һ����ͬ�ģ���ô�ø�����ҵ�϶����ܼ��������Ӵ�2
//				{//��true��ֱ��break����������ǰ���forѭ�������ý������Ӵ�2[cutpoint2,number_of_jobs)����ʣ����ҵ�Ƚ���
//					bt = true;//��ʱindex���ֲ��䣬����ִ����һ��forѭ���жϵ�ǰĸ����ҵ���¸���ҵ
//					break;
//				}
//			}
//			if (bt == false)//��һֱfalse��δ����true,˵����ǰ������ҵһֱ�������������ҵ��ͬ����
//			{
//				chIndiv2.v_chromosome[index] = jobNo;//���ø�����ҵ����ҵ�ţ������Ӵ�2��ǰ��cutpoint1λ����
//				index++;//��ʱԭcutpoint1�Ѿ�������ˣ���++�����������һ��λ��
//			}//��������Ӵ�2[cutpoint1,cutpoint2)λ����ҵ����䣬�Ӹ��׻�á�
//		}
//		//������� ����ѡ���� ��ĸ ���н��� �����Ӵ�1��2�� �����������[0,number_of_jobs)�Ļ���ֵ��
//	
//
//		evaluate(chIndiv1);//���ú��������Ӵ�1��Ŀ��ֵ
//		current_number_of_fitness_evaluations++;
//		evaluate(chIndiv2);//���ú��������Ӵ�2��Ŀ��ֵ
//		current_number_of_fitness_evaluations++;
//		v_Chromo.push_back(chIndiv1);//���Ӵ�1 β�� �� ��Ⱥ��
//		v_Chromo.push_back(chIndiv2);//���Ӵ�2 β�� �� ��Ⱥ��
//	}
//	//cout << "�����" << endl;
//	//for (int i = 0; i < v_Chromo.size(); i++)
//	//{
//	//	for (int j = 0; j < number_of_jobs; j++)
//	//	{
//	//		cout << v_Chromo[i].v_chromosome[j] << " ";
//	//	}
//	//	cout << endl;
//	//}
//}//����croTimes��ѭ����������number_of_individuals�����壬��ʱ��Ⱥ��ģ��2*number_of_individuals��
////��Ϊ����ԭ����ʼ��Ⱥ�Ļ�����β�������Ⱥ:��init.cpp�в����ĳ�ʼ��Ⱥ��cross����������β���Ӵ���Ⱥ
//
////mutate
//void CGenetic::mutate()
//{
//	int  mutaNo;//������󣨸��壩��
//	int pos1, pos2, index, pos;
//	int jobNo;//������������
//	int i;
//
//	for (i = number_of_individuals; i < 2 * number_of_individuals; i++)//����Ӵ���Ⱥ���б���
//	{
//		mutaNo = i;//��ȡ ������󣨸��壩 �� �����
//		if (rand() / (RAND_MAX * 1.0) <= mutProb) //�������һ��[0,1)�ĸ������������������mutProb�Ƚ�
//		{                                         //�������<=�����ʣ�����б��졣����������󣬵��ú�������ø���Ŀ��ֵ
//			if (rand() / (RAND_MAX * 1.0) <1)  //���������һ��[0,1)�ĸ���������0.5�Ƚϣ�����0.5��������������
//			{                                                                     //��������[0,number_of_jobs�ϱ䶯
//				pos1 = rand() % number_of_jobs;//�������һ��λ��1��ȡֵ[0,number_of_jobs)
//				pos2 = rand() % number_of_jobs;//�������һ��λ��2��ȡֵ[0,number_of_jobs)
//				while (pos1 == pos2)//����ͬ���������������һ��λ��2
//				{
//					pos2 = rand() % number_of_jobs;
//				}
//				jobNo = v_Chromo[mutaNo].v_chromosome[pos1];//Ȼ������λ�õĻ��򻥻�����Ⱥ��mutaNo���󣨸��壩��Ⱦɫ����
//				v_Chromo[mutaNo].v_chromosome[pos1] = v_Chromo[mutaNo].v_chromosome[pos2];//�ĵ�pos1λ�õĻ��� ��ֵ�������� 
//				v_Chromo[mutaNo].v_chromosome[pos2] = jobNo;//������jobNo����Ⱥ��mutaNo���󣨸��壩��Ⱦɫ����pos2λ�õĻ��� 
//			}                                               //��ֵ��pos1����󣬽������������˵�ֵ��ֵ��pos1                                                                                      
//		}
//		evaluate(v_Chromo[mutaNo]);//���ú�����������죨�п��ܲ�������죩�����Ŀ��ֵ��
//		current_number_of_fitness_evaluations++;
//	}
//
//	//for (int i = number_of_individuals; i < 2*number_of_individuals; i++)
//	//{
//	//	for (int j = 0; j < number_of_jobs; j++)
//	//	{
//	//		cout << v_Chromo[i].v_chromosome[j] << " ";//���������Ⱥ
//	//	}
//	//	cout << endl;
//	//}
//}//��������Ӵ���Ⱥ�ı��������Ⱦɫ�峤���������й�
