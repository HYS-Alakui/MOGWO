#include "Genetic.h"
#include "Individual.h"
#include "headfile.h"
#include "Chromosome.h"

void CGenetic::next_pop()
{
	//cout << "------------6、下一代种群-----------" << endl;
	for (int i = 0; i < v_new_individuals.size(); i++)
	{
		v_Chromo.push_back(v_new_individuals[i]);
	}
	//cout << "合并种群" << endl;
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


	//////对2N个个体进行分层
	int domRel, rankLevel, size, sizeZero, domChromoNo, domedChromoNo;
	double objValue;
	bool bt;
	vector <int> v_domZero;//创建容器，储存被支配次数为0的个体（不是单指第一层，有可能是后面新一批的下一层）

	//initialize
	for (int i = 0; i < 2 * number_of_individuals; i++)//初始化种群：每个对象的被支配次数，支配列表集合，和排序都是0
	{
		v_Chromo[i].domination_count = 0;//种群中第i个对象的 被支配次数 初始化为0
		v_Chromo[i].v_dominationSet.resize(0);//种群中第i个对象的 支配列表集合 初始化长度为0
		v_Chromo[i].rank = 0;//种群中第i个对象的 排序 初始化为0
	}
	//然后下面对 每个对象 调用 判断个体支配关系函数；为其属性 被支配次数domination_count 和支配列表集合v_dominationSet 赋值。
	size = v_Chromo.size();//种群规模大小       在NSGA2代码中每个个体都是一个对象，有一堆属于他的属性，他所在的类名是CIndividual；
	for (int i = 0; i < 2 * number_of_individuals - 1; i++)//此过程获取v_Chromo种群中每个 对象的 被支配次数 和 支配其他个体的集合
	{
		for (int j = i + 1; j < 2 * number_of_individuals; j++)//两两对象相互比较所有的目标值
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
		for (int i = 0; i < 2 * number_of_individuals; i++)//依次判断每个对象是否被支配次数=0，是:存入排序序列容器v_rankSequ和当前支配次数=0容器v_domZero。
		{    //同时更新v_Chromo和v_rankSequ容器的成员变量：rank；chromoNo,rankSequ,rankLevel,v_rObjValue
			if (v_Chromo[i].domination_count == 0)//若v_Chromo数组的第i对象的 变量（被支配次数）为0；就划分到当前层数；第一次运行时，是第一层
			{//主要是为CRankSequ容器中的具体对象t对应的变量赋值；同时把t填充给容器v_CRankSequ，但此时的是排过序的哦，t是优秀选手
				//rankLevel在类CIndividual中对应变量 rank； 在类CRankSequ中对应变量rankSequ
				CRankSequ t;//创建一个具体对象t，它的属性包括 chromoNo，rankLevel， v_rObjValue;最后再把对象放到rankSequ容器中                
				v_Chromo[i].rank = rankLevel;//当前rankLevel值 赋值给 v_Chromo的对象i的 属性rank；
				t.chromoNo = i;//将 对象号i 赋值给 该对象t的 染色体编号chromoNo
				t.rankSequ = rankLevel;//将当前rankLevel值 赋值给 CRankSequ的对象t  属性rankSequ值；
				for (int j = 0; j < number_of_objectives; j++)
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
	//以上这个while循环就是分层的；将原来种群中的对象按照之前的被支配次数和支配集合指标进行分层；存入v_RankSequ容器，按照F1,F2...

	/////输出v_rankSequ容器
	//for (int cn = 0; cn < v_rankSequ.size(); cn++)
	//{
	//	cout << v_rankSequ[cn].chromoNo << " ";
	//	cout << v_rankSequ[cn].rankSequ << endl;
	//}

	select();
	///////select N individuals from 2N 按照rank值和拥挤度进行筛选


	//////输出下一代种群
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

void CGenetic::select()//类外定义选择函数：从2N个个体中选择N个个体；
{   //先看后面rank和rank the population代码；只有根据支配关系排完序分层好，才能根据这些指标再选择
	int i, j;                                                             //包括染色体，目标值，排序，支配次数，支配集合等变量
	vector <CIndividual> v_sele;//定义一个容器v_select，用于放被选中的对象；自定义类型Cindividual；通过对象可访问关于个体的变量
	vector<CIndividual>().swap(v_sele);

	int sizeSeledNum;//规模
	CIndividual t;//创建一个具体对象即一个具体的个体 对象名为t
	int rankLevel = 1;//初始化为1，因为先选第一层的
	int total, num;
	int start, end;
	int chromoNo;//染色体编号
	start = 0;
	num = 0;
	while (1)//while（1）指“循环永远执行下去.除非遇到break;才跳出循环”
	{
		num = 0;
		for (i = start; i < 2 * number_of_individuals; i++)
		{
			if (v_rankSequ[i].rankSequ == rankLevel)//首先，v_rankSequ是个（容器）数组，以[]方式可以访问i对象；
			{  //v_rankSequ是自定义数据类型<CRankSequ>，故i是对象；通过.变量名的方式访问CRankSequ类中的rankSequ变量
				num++;
				end = i;                  //防止所有点都在第一层上
			}
			else
			{
				end = i - 1;
				break;//break用来从最近的封闭循环体内跳出。
			}
		}
		sizeSeledNum = v_sele.size();//容器的大小即数组的长度；一开始容器的大小应该是0的//下一层时候，长度=上一层个体数目
		total = sizeSeledNum + num;//num数值等于上述循环过程执行的次数，即有多少个体属于当前层

		//一开始就是先看看rankSequ=1（total衡量）即第一层rankLevel的够不够N
		if (total < number_of_individuals)//小于N
		{
			//[start,end]中的所有个体保存下来
			for (j = start; j <= end; j++)
			{
				chromoNo = v_rankSequ[j].chromoNo;//获取 v_rankSequ数组的第j个对象 的 变量染色体编号chromoNo
				t = v_Chromo[chromoNo];//将v_Chromo数组即种群中的编号为chromoNo的对象 赋值给 具体对象t
				v_sele.push_back(t);//将具体对象 t储存给 v_sele数组
			}
			start = end + 1;//下一层开始=上一层结束+1
			rankLevel++;//开始下一层；因为上一层数目不够N，故只能进入下一层寻找；
			continue;//此时不够，还得选下一层，那么跳过循环体中尚未执行的语句，跳到while（1）。
		}
		if (total == number_of_individuals)//等于N
		{
			//[start, end]中的所有个体保存下来
			for (j = start; j <= end; j++)
			{
				chromoNo = v_rankSequ[j].chromoNo;//获取 v_rankSequ数组的第j个对象 的 变量染色体编号chromoNo
				t = v_Chromo[chromoNo];//将v_Chromo数组即种群中的编号为chromoNo的对象 赋值给 具体对象t
				v_sele.push_back(t);//将具体对象 t储存给 v_sele数组
			}
			break;//此时够了，结束while循环即可
		}
		if (total > number_of_individuals)//大于N时，需要进行拥挤度距离判断，再选择剩余位置个体
		{
			//调用求密度函数进行选择（第四步）；拥挤度大的优先进入剩余位置。			
			crodiversity(v_rankSequ, start, end);//参数是 CRankSequ类（自定义数据类型）的对象 int型的数字 int型的数字
			end = number_of_individuals - 1;//0开始的，N个个体，故end=N-1
			for (int j = start; j <= end; j++)
			{
				chromoNo = v_rankSequ[j].chromoNo; // 获取 v_rankSequ数组的第j个对象 的 变量染色体编号chromoNo
				t = v_Chromo[chromoNo];//将v_Chromo数组即种群中的编号为chromoNo的对象 赋值给 具体对象t
				v_sele.push_back(t);//将具体对象 t储存给 v_sele数组
			}
			break;//此时够了，结束while循环即可
		}
	}
	//选择出的个体向量集合v_sele赋到原来集合v_Chromo中
	vector <CIndividual>().swap(v_Chromo);//巧用swap缩短内存，v_Chromo此时的长度为0
	v_Chromo.assign(v_sele.begin(), v_sele.begin() + number_of_individuals);//将v_slec容器中的值用assign赋值给v_Chromo，此时长度为N

}

void CGenetic::crodiversity(vector <CRankSequ>& v_rankSequ, int& start, int& end)
{                         //v_rankSequ是容器=数组，数组传递时，只需写个数组名即可，再加引用符号&
	int i, j;
	double minObjValue, maxObjValue, preObjValue, nextObjValue;//最小值，最大目值，前值，后置
	double dtemp;
	CRankSequ t;

	for (i = start; i <= end; i++)
	{
		v_rankSequ[i].croDiversity = 0.0;//初始化 某一层的个体 的 拥挤度密度=0；
	}
	//order the individuals in the same rank as non-dereasingly 
	for (int objNo = 0; objNo < number_of_objectives; objNo++)//遍历每个目标
	{
		for (i = start; i <= end - 1; i++)//升序排列；类似于冒泡排序
		{
			for (int j = i + 1; j <= end; j++)
			{
				dtemp = v_rankSequ[i].v_rObjValue[objNo];//获取i对象的目标值
				if (dtemp > v_rankSequ[j].v_rObjValue[objNo])//与j对象的目标值比较
				{
					t = v_rankSequ[i];//因为是对象换，且对象换其所有的属性即当前目标下的目标值也跟着变动；
					v_rankSequ[i] = v_rankSequ[j];//故用对象t来当第三方工具人；
					v_rankSequ[j] = t;//互换操作：目标值小的对象被换到前面，目标值大的对象被换到后面
				}
			}
		}
		////经历上面排序后，start对应当前目标下的目标值小的对象，end对象目标值大的对象 某一层的两端临界对象 的 拥挤度距离 =无穷大
		v_rankSequ[start].croDiversity = INF_DOUBLE_MAX;//在当前目标下，最小目标值对于的对象的密度为无限大值
		v_rankSequ[end].croDiversity = INF_DOUBLE_MAX;//在当前目标下，最大目标值对于的对象的密度为无限大值

		minObjValue = v_rankSequ[start].v_rObjValue[objNo];//获取当前目标的最小目标值；//不用管是同一层上的最值还是全局；反正就是个常数
		maxObjValue = v_rankSequ[end].v_rObjValue[objNo];//获取当前目标的最大目标值；//不影响结果

		for (i = start + 1; i <= end - 1; i++)//求每个个体的密度，start和end密度为无穷大，因为他们的对象是升序区间最值。
		{   //因为涉及前一个对象i-1，故i从start+1开始；同理涉及后一个对象i+1,故i从end-1结束
			preObjValue = v_rankSequ[i - 1].v_rObjValue[objNo];//前一个对象 的 当前目标下的目标值
			nextObjValue = v_rankSequ[i + 1].v_rObjValue[objNo];//后一个对象 的 当前目标下的目标值
			v_rankSequ[i].croDiversity = v_rankSequ[i].croDiversity + abs((double)(nextObjValue - preObjValue)) / ((maxObjValue - minObjValue)*1.0);
			//密度=（前一个个体的目标值-后一个个体的目标值）/（最大目标值-最小目标值）；fabs（）对float，double求绝对值
		}
		//以上求出单个目标下所有对象的密度
	}
	//以上 求出所有对象的拥挤度距离
	for (i = start; i <= end - 1; i++) //order non-increasingly as cronwding distance //按照个体密度，对v_rankSequ容器中的个体降序排列
	{
		for (j = i + 1; j <= end; j++)//比较相邻两个对象的拥挤度距离；降序排列
		{
			dtemp = v_rankSequ[i].croDiversity;
			if (dtemp < v_rankSequ[j].croDiversity)
			{
				t = v_rankSequ[i];//互换操作，比较拥挤度距离，将对应对象互换；
				v_rankSequ[i] = v_rankSequ[j];//即拥挤度距离值小的对象在前面，拥挤度距离值大的对象在后面；
				v_rankSequ[j] = t;//互换对象，故用对象t来当第三方工具人；
			}
		}
	}

}