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

	chromoSize = v_Chromo.size();//种群的大小：种群规模
	for (i = 0; i < chromoSize; i++)
	{
		archive_size = v_archive.size();//非支配种群的大小
		if (archive_size == 0)//若非支配集合=空
		{
			v_archive.push_back(v_Chromo[i]);//把当前种群中第i个个对象 尾插 到非支配集合
			continue;
		}
		bt = false;
		for (j = archive_size - 1; j >= 0; j--)
		{
			domRelation(v_Chromo[i], v_archive[j], domRel);//调用函数判断 v_Chromo[i] 与 其他个体v_archive[j] 之间支配关系 
			if (domRel == 1)//若v_Chromo[i] 支配  v_archive[j]，存在支配关系，则
			{
				v_archive.erase(v_archive.begin() + j);//删掉v_archive数组第j个位置的 元素
			}
			else if (domRel == -1 || domRel == 0)//若v_Chromo[i] 与  v_archive[j]存在 被支配，相等关系
			{
				bt = true;//v_Chromo[i] 被 v_archive[j]支配/相等,那么v_Chromo[i]肯定不是非支配解了
				break;    //跳出离他最近的for循环，判断种群中下一个个体
			}
		}
		//上面这个for循环，排除了存在支配关系的个体，也跳过了存在 被支配和相同 关系的个体
		if (bt == false)//存在非支配关系，
		{
			v_archive.push_back(v_Chromo[i]);//把v_Chromo的第i个对象 储存 到v_archive中 
		}
	}

}
