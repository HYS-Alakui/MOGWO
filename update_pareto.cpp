#include "headfile.h"
#include "Individual.h"
#include "Genetic.h"
#include "RankSequ.h"

void CGenetic::update_pareto()//store the nondominated solution in the population...
{
	int i, j;
	int chromoSize;
	int domRel;
	int archive_size;
	bool bt;
	int index;

	chromoSize = v_Chromo.size();//��Ⱥ�Ĵ�С����Ⱥ��ģ
	for (i = 0; i < chromoSize; i++)
	{
		archive_size = v_archive.size();//��֧����Ⱥ�Ĵ�С
		if (archive_size == 0)//����֧�伯��=��
		{
			v_archive.push_back(v_Chromo[i]);//�ѵ�ǰ��Ⱥ�е�i�������� β�� ����֧�伯��
			continue;
		}
		bt = false;
		for (j = archive_size - 1; j >= 0; j--)
		{
			domRelation(v_Chromo[i], v_archive[j], domRel);//���ú����ж� v_Chromo[i] �� ��������v_archive[j] ֮��֧���ϵ 
			if (domRel == 1)//��v_Chromo[i] ֧��  v_archive[j]������֧���ϵ����
			{
				v_archive.erase(v_archive.begin() + j);//ɾ��v_archive�����j��λ�õ� Ԫ��
			}
			else if (domRel == -1 || domRel == 0)//��v_Chromo[i] ��  v_archive[j]���� ��֧�䣬��ȹ�ϵ
			{
				bt = true;//v_Chromo[i] �� v_archive[j]֧��/���,��ôv_Chromo[i]�϶����Ƿ�֧�����
				break;    //�������������forѭ�����ж���Ⱥ����һ������
			}
		}
		//�������forѭ�����ų��˴���֧���ϵ�ĸ��壬Ҳ�����˴��� ��֧�����ͬ ��ϵ�ĸ���
		if (bt == false)//���ڷ�֧���ϵ��
		{
			v_archive.push_back(v_Chromo[i]);//��v_Chromo�ĵ�i������ ���� ��v_archive�� 
		}
	}

}
