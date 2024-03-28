#include "Genetic.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"
#include <vector>
using namespace std;

void CGenetic::cluster()
{
	//cout << "------------2、非支配分层---------" << endl;
	int i, j;
	int domRel, rankLevel, size, sizeZero, domChromoNo, domedChromoNo;
	double objValue;
	bool bt;
	vector <int> v_domZero;//创建容器，储存被支配次数为0的个体（不是单指第一层，有可能是后面新一批的下一层）
	//initialize
	for (i = 0; i < v_Chromo.size(); i++)//初始化种群：每个对象的被支配次数，支配列表集合，和排序都是0
	{
		v_Chromo[i].domination_count = 0;//种群中第i个对象的 被支配次数 初始化为0
		v_Chromo[i].v_dominationSet.resize(0);//种群中第i个对象的 支配列表集合 初始化长度为0
		v_Chromo[i].rank = 0;//种群中第i个对象的 排序 初始化为0
	}
	//然后下面对 每个对象 调用 判断个体支配关系函数；为其属性 被支配次数domination_count 和支配列表集合v_dominationSet 赋值。
	size = v_Chromo.size();//种群规模大小       在NSGA2代码中每个个体都是一个对象，有一堆属于他的属性，他所在的类名是CIndividual；
	for (i = 0; i < v_Chromo.size() - 1; i++)//此过程获取v_Chromo种群中每个 对象的 被支配次数 和 支配其他个体的集合
	{
		for (int j = i + 1; j < v_Chromo.size(); j++)//两两对象相互比较所有的目标值
		{               //调用函数：因为比较的是两个对象的支配关系，故在传参数的时候也是传对象；
			domRel = 3; //v_Chromo[i],v_Chromo[j]代表两个具体的对象即第i个对象和第j个对象，将实参传给形参A，B；引用传递，且常引用；
			domRelation(v_Chromo[i], v_Chromo[j], domRel);//（第二步）调用 判断A和B支配关系 的函数；void CGenetic::domRelation(const CIndividual& A, const CIndividual& B, int& domRel)
			if (domRel == 1)//前者优于后者      函数值=1，表示支配；
			{   //对象名.属性名 访问 类中的变量；且v_dominationSet是定义的容器，故使用push_back()尾插法赋值
				v_Chromo[j].domination_count++;//故 后面对象v_Chromo[j] 的 属性domination_count即被支配次数 ++
				v_Chromo[i].v_dominationSet.push_back(j);//故前者对象v_Chromo[i] 的 属性支配列表集合v_dominationSet 尾插 一个 后者的对象号
			}
			else if (domRel == -1)///前者差于后者    函数值=-1，表示被支配
			{
				v_Chromo[i].domination_count++;//故前面对象v_Chromo[i] 的 属性domination_count即被支配次数 ++
				v_Chromo[j].v_dominationSet.push_back(i);//故后面对象v_Chromo[j] 的属性支配集合v_dominationSet 尾插 一个 前者的对象号
			}//以上只考虑两个函数支配与被支配的关系，进而影响变量被支配次数和支配列表集合；而当doRem1=0（相等）或者domRe1=2(非支配)不考虑
		}
	}//以上 求出v_Chromo种群中 每个对象的 被支配次数，支配列表

	//rank the population  //CRankSequ储存 经历过排序 的 对象；属性是染色体编号chromoNo，排序值rankSequ，拥挤度距离croDiversity及目标值v_robjective
	vector <CRankSequ>().swap(v_rankSequ);  //巧用swap缩短内存，v_rankSequ此时的长度为0；相当于初始化；根据后续排序，插入符合的对象；
	rankLevel = 1;	//初始化 层号；先排第一层
	while (1)//while（1）指“循环永远执行下去.除非遇到break;才跳出循环”//这个while循环就是个分层的过程
	{                 //并且分层过程，填充了一个v_CRankSequ容器（先排序值为1的对象后2再3这么排）；且更新了它的变量chromoNo,rankSequ,croDiversity,v_robjective
		bt = false;   //重新指定!! 因为这个容器专门被支配次数为0的对象；用于进行下一步的所属列表被支配次数-1的操作；新一批为0的不包含老选手 
		v_domZero.resize(0);//重新指定 储存被支配次数为0的对象号 的数组domZero 长度为0；
		for (i = 0; i < v_Chromo.size(); i++)//依次判断每个对象是否被支配次数=0，是:存入排序序列容器v_rankSequ和当前支配次数=0容器v_domZero。
		{    //同时更新v_Chromo和v_rankSequ容器的成员变量：rank；chromoNo,rankSequ,rankLevel,v_rObjValue
			if (v_Chromo[i].domination_count == 0)//若v_Chromo数组的第i对象的 变量（被支配次数）为0；就划分到当前层数；第一次运行时，是第一层
			{//主要是为CRankSequ容器中的具体对象t对应的变量赋值；同时把t填充给容器v_CRankSequ，但此时的是排过序的哦，t是优秀选手
				//rankLevel在类CIndividual中对应变量 rank； 在类CRankSequ中对应变量rankSequ
				CRankSequ t;//创建一个具体对象t，它的属性包括 chromoNo，rankLevel， v_rObjValue;最后再把对象放到rankSequ容器中                
				v_Chromo[i].rank = rankLevel;//当前rankLevel值 赋值给 v_Chromo的对象i的 属性rank；
				t.chromoNo = i;//将 对象号i 赋值给 该对象t的 染色体编号chromoNo
				t.rankSequ = rankLevel;//将当前rankLevel值 赋值给 CRankSequ的对象t  属性rankSequ值；
				for (j = 0; j < number_of_objectives; j++)
				{
					objValue = v_Chromo[i].v_objective_value[j];//从v_Chromo对象i那里 获取 每个目标值
					t.v_rObjValue.push_back(objValue);//再赋值 给对象t 的v_rObjValue变量，多个目标故需要一个容器vector <double> v_rObjValue;
				}
				v_rankSequ.push_back(t);//最后具体对象t存在v_rankSequ中
				bt = true;//只要第一层有被支配次数=0，就可以根据这层对象，进行下一层的筛选
				v_domZero.push_back(i);//将对象号i存在v_domZero容器中，比如1，3，5的被支配次数=0；那么1,3,5对象号赋值给该数组
			}
			//以上这个if语句也体现了CIndividual和CRankSequ类之间的关系，CRankSequ的chromoNo，v_rObjValue都是从CIndividual获取
		}//两个类的桥梁分别是V_Chromo[i]和t
		//以上这个for循环，就是把所有的被支配次数=0的都找出来（如果有），设为对象t,再将对象t存入rankSequ数组，将对应的对象号i存入v_domZero数组
	  //且赋值：v_Chromo中的rank变量=rankLevel， CRankSequ中的t的rankSequ=rankLevel,chromoNo=i,v_robjctive=从v_Chromo[i]那获取的objective
		if (bt == false)//一开始初始化为false；只要存到一个被支配次数为0的（第一层有数据），那么就可以true;进行true的条件语句，筛选下一层
		{
			break;//如果没有==0的，都变成-1了（防止重复判断设置的-1），那么没有true,默认初始false，则跳出整个while循环，分层结束
		}
		if (bt == true)//在true时候即有上一层，且把上一层被支配次数=0的都筛出来了，那么根据上层开始筛选下一层：就是把上一层的个体所拥有的支配列表中的个体的被支配次数-1
		{
			rankLevel++;//下层次数++；上一层个体 的支配列表 所属的个体的被支配次数-1。比如A，B是第一层，A支配C,D,E； B支配C，F；那么C-2，D，E，F-1。
			sizeZero = v_domZero.size();//当前被支配次数=0的数组v_domZero 的 长度；即有多少个数据呀
			for (int j = 0; j < sizeZero; j++)//有多少个数据就遍历多少次
			{
				domChromoNo = v_domZero[j];//将原来保存进去的t的对象号提取，赋值给domChromoNov_domZero[0]=1；v_domZero[1]=3；v_domZero[2]=5；
				v_Chromo[domChromoNo].domination_count = -1;//将原来被支配次数=0的 对象 的 被支配次数改为-1；因为当前if结束后，仍进入上面那个分层判断，
				size = v_Chromo[domChromoNo].v_dominationSet.size();//获取被支配次数=0的对象 的 支配列表集合 的 长度           //这些=0的已经判断过了。
				for (int k = 0; k < size; k++)
				{
					domedChromoNo = v_Chromo[domChromoNo].v_dominationSet[k];//把被支配个体的编号取出来 赋值给 domedChromoNo
					v_Chromo[domedChromoNo].domination_count--;//被支配个体的被支配次数-1
				}
			}
		}//这个if语句后，产生新一批被支配次数=0的对象，进入while循环，继续执行上面那个if (v_Chromo[i].domination_count == 0)
	}                                                                                          //判断下一层有哪些对象
	//以上这个while循环就是分层的；将原来种群中的对象按照之前的被支配次数和支配集合指标进行分层；存入v_RankSequ容器，按照F1,F2...顺序依次存储

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//v_RankSequ容器存储一排对象，这些对象是按照rank值排序的，即前几个是第一层的，接着几个是第二层，直至最后几个个体是最后一层。
	//v_RankSequ容器中的对象属性包括:chromoNo个体号；rankSequ序值；拥挤度距离和目标值
	////输出v_rankSequ容器
	//for (int cn = 0; cn < v_rankSequ.size(); cn++)
	//{
	//	cout << v_rankSequ[cn].chromoNo << " ";
	//	cout << v_rankSequ[cn].rankSequ << endl;
	//}
	//cout << endl;

	//首先需要获取一共有多少个簇，找出最大的rankSequ即可	
	cluster_number = v_rankSequ[number_of_individuals - 1].rankSequ;
	//cout << "cluster_number = " << cluster_number << endl;
	//然后获取每个簇包括哪些个体，即相同rankSequ属于同一簇
	int num_c = 0;
	vector <vector<CRankSequ>>().swap(v_cluster);//清空容器,初始化
	for (int cn = 1; cn <= cluster_number; cn++)
	{
		vector <CRankSequ> v;
		v_cluster.push_back(v);

		for (int i = num_c; i < v_rankSequ.size(); i++)
		{
			if (v_rankSequ[i].rankSequ == cn)
			{
				CRankSequ clu;
				clu.chromoNo = v_rankSequ[i].chromoNo;//获取作业号
				clu.rankSequ = v_rankSequ[i].rankSequ;//获取rank值
				clu.v_rObjValue = v_rankSequ[i].v_rObjValue;//获取目标值
				v_cluster[cn - 1].push_back(clu);//将该对象放入当前簇列表
				num_c++;
			}
			else
			{
				break;
			}
		}
	}
	//cout<<"每个簇包含的个体及其簇号和目标值"<<endl;
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

void CGenetic::domRelation(const CIndividual& A, const CIndividual& B, int& domRel)//类CGenetic源文件只保留函数的实现部分
{                 //常引用 const       类名 &形参；不想改变实参的值，故加入const，否则引用传递，实参的值会发生改变
	int i;        //A和B是两个对象；因为个体都有很多变量，故一开始就把个体建立一个类；方便后续访问其个体的属性
	int equalCount, lessCount, greaterCount;//函数实参是 具体对象 时，形参格式： 带类名的 引用 形参名
	equalCount = 0;//初始化
	lessCount = 0;//初始化
	greaterCount = 0;//初始化
	for (i = 0; i < number_of_objectives; i++)//多个目标比较
	{
		if (A.v_objective_value[i] == B.v_objective_value[i])//对象名.变量；通过[]方式访问vector容器中的元素
		{
			equalCount++;//若两个对象的目标值相等，则相等次数++
		}
		if (A.v_objective_value[i] < B.v_objective_value[i])
		{
			lessCount++;//若A对象的目标值<B对象的目标值，则less次数++
		}
		if (A.v_objective_value[i] > B.v_objective_value[i])
		{
			greaterCount++;//若A对象的目标值>B对象的目标值，则greater次数++
		}
	}
	if (equalCount == number_of_objectives)    //two solutions are equal in each objective.
	{
		domRel = 0;//两个个体的所有目标值都相等
	}
	else if ((equalCount + lessCount == number_of_objectives) && lessCount > 0)  // the first solution dominates the second solution.
	{        //0+2=2,2>0或者1+1=2,1>0;less代表好，故支配（情况1：A的所有目标值<B的，equalCount=0，此时lessCount=number_of_objectives;）
		domRel = 1;            //（情况2：A的所有目标值有=B的（假设1），此时equalCount=1，也有<B的，lessCount=number_of_objectives-1;）
	}
	else if ((equalCount + greaterCount == number_of_objectives) && greaterCount > 0) //the first solution is dominated by the second solution.
	{       //0+2=2,2>0或者1+1=2,1>0;great代表差，故被支配（情况1：A的所有目标值>B的，equalCount=0，此时greaterCount=number_of_objectives;）
		domRel = -1;     //（情况2：A的所有目标值有 = B的（假设1），此时equalCount = 1，也有 >B的，greaterCount = number_of_objectives - 1; ）
	}
	else         //two solutions are non-dominated each other.
	{
		domRel = 2;//1个less+1个great；//A目标值既有<B的也有>B的，此时两个对象属于非支配关系
	}
}