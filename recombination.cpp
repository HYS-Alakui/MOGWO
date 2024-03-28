//#include "Genetic.h"
//#include "Individual.h"
//#include "rankSequ.h"
//#include "headfile.h"
//
////该cpp主要进行交叉和变异操作！
//
////对于两个父代S1（O1,V1）,S2（02,V2）,O1和O2部分进行两点交叉（两点变异），V1和V2部分进行二进制均匀交叉（单点变异）；
////交叉：注意染色体长度！前一半：选出父母使用交叉产生后代；后一半：使用二进制容器，判断选择
//void CGenetic::cross()
//{
//	int i, j, k;
//	int croTimes, irandNum1, irandNum2, domRel;//定义交叉次数，随机个体1的对象号，随机个体2的对象号，支配结果
//	CIndividual mothIndiv, fathIndiv, chIndiv1, chIndiv2, indiv1, indiv2;//具体对象，母亲，父亲，子代1，子代2，个体2，个体2
//	int cutpoint1, cutpoint2;//切点；其实每个个体就是一个对象，有着属于自己的属性,v_chromosome和v_objective_value等
//	int temp;
//	int jobNo;
//	int index;
//	bool bt;
//
//	vector <int> v_parNum;//定义一个 储存 父母 的 容器；为啥是创建父母容器呢，因为能动态开辟内存；涉及下面执行选择父母的时候
//	croTimes = number_of_individuals / 2;//交叉次数；//有容器个体数目是：1+2的情况，那么只建立包含2个元素的传统数组就不好使了
//	for (i = 0; i < croTimes; i++)
//	{
//		//binary tourment seletciton//
//		vector <int>().swap(v_parNum);
//		vector <int>().swap(chIndiv1.v_chromosome);
//		vector <double>().swap(chIndiv1.v_objective_value);
//		vector <int>().swap(chIndiv2.v_chromosome);
//		vector <double>().swap(chIndiv2.v_objective_value);
//		//巧用swap,完成清空容器内存；相当于一个初始化
//
//		for (j = 0; j < 2; j++)//因为选两个好的个体当父母，故进行两次循环，排除 一下子就选出两个个体是非支配关系 的情况哦！
//		{   //此种情况，直接break掉就可以啦，因为一次就选中两个好的个体啦！；若第一次是支配/被支配/相同，此时，容器加1个个体，
//			//若第二次是非支配，容器个体加2；那么，容器中数目：1+2，这个也不要紧啦，因为，下面只会选容器的前两个元素当父母哦！
//			irandNum1 = rand() % number_of_individuals;//随机产生对象（个体）1的对象号
//			irandNum2 = rand() % number_of_individuals;//随机产生对象（个体）2的对象号
//			while (irandNum1 == irandNum2)//若选中的对象号同，即选中对象（个体）同
//			{
//				irandNum2 = rand() % number_of_individuals;//重新产生对象（个体）2的对象号
//			}
//			indiv1 = v_Chromo[irandNum1];//根据对象号，获取第1个对象；方面下面进行 调用函数 判断两个对象关系
//			indiv2 = v_Chromo[irandNum2];//根据对象号，获取第2个对象；进而选择出好的个体，若只有对象号，无法获取二者关系呀
//
//			domRelation(indiv1, indiv2, domRel);//判断两个对象（个体的关系）；选择其中 1个 好的 个体 存入父母容器！
//			if (domRel == 1 || domRel == 0)//若个体1 支配或等于 个体2，（个体1好）
//			{
//				v_parNum.push_back(irandNum1);//那么把个体1的 对象号 尾插 到 父母容器中
//			}
//			else if (domRel == -1)//若个体1 被 个体2 支配，（个体2好）
//			{
//				v_parNum.push_back(irandNum2);//那么把个体2的 对象号 尾插 到 父母容器中
//			}
//			else if (domRel == 2)//若存在非支配关系，那么只进行这一次循环即可，直接将这两个个体
//			{
//				v_parNum.push_back(irandNum1);//的对象号 尾插 到 父母容器中，此时已经有父母了
//				v_parNum.push_back(irandNum2);//即当前交叉次数下 父母容器已满，
//				break;                        //父母选择过程结束，故直接跳出for循环
//			}
//		}
//		//以上 是选择 父母 的过程 
//
//		irandNum1 = v_parNum[0];//获取 父母容器中第一个元素的 对象号;以[ ]方式，访问容器中的元素
//		irandNum2 = v_parNum[1];//获取 父母容器中第一个元素的 对象号
//		fathIndiv = v_Chromo[irandNum1];//根据 对象号 获取 父亲个体
//		mothIndiv = v_Chromo[irandNum2];//根据 对象号 获取 母亲个体
//
//		for (j = 0; j < 2 * number_of_jobs; j++)
//		{
//			chIndiv1.v_chromosome.push_back(0);//初始化 子代1 的 染色体，染色体上的2* number_of_jobs个基因，都尾插0
//			chIndiv2.v_chromosome.push_back(0);//初始化 子代2 的 染色体，染色体上的2* number_of_jobs个基因，都尾插0
//		}
//
//		//(1)利用父母个体 交叉 完成 子代1和2 的[0, number_of_jobs)区间基因赋值。
//		cutpoint1 = rand() % number_of_jobs;//随机产生一个切点1，切点1的范围[0 , number_of_jobs-1]
//		cutpoint2 = rand() % number_of_jobs;//随机产生一个切点2，切点2的范围[0 , number_of_jobs-1]
//		while (cutpoint1 == cutpoint2)//若两个切点相同
//		{
//			cutpoint2 = rand() % number_of_jobs;//则重新产生一个切点2
//		}                         //我们 人为 让切点1在切点2的前面，直观且方便后续操作
//		if (cutpoint1 > cutpoint2)//若切点1在切点2后面
//		{
//			temp = cutpoint1;
//			cutpoint1 = cutpoint2;//则进行互换操作
//			cutpoint2 = temp;
//		}
//
//		for (j = 0; j < cutpoint1; j++)//注意cutpoint1是开区间，这个作业号上的作业是取不到的；
//		{
//			jobNo = fathIndiv.v_chromosome[j];//获取父亲染色体上[0,cutpoint1)区间的作业
//			chIndiv1.v_chromosome[j] = jobNo;//将父亲[0,cutpoint1)上的作业 拷贝 给子代1相同位置
//			jobNo = mothIndiv.v_chromosome[j];//获取母亲染色体上[0,cutpoint1)区间的作业
//			chIndiv2.v_chromosome[j] = jobNo;//将母亲[0,cutpoint1)上的作业 拷贝 给子代2相同位置
//		}
//		for (j = cutpoint2; j < number_of_jobs; j++)
//		{
//			jobNo = fathIndiv.v_chromosome[j];//获取父亲染色体上[cutpoint2，number_of_jobs)区间的作业
//			chIndiv1.v_chromosome[j] = jobNo;//将父亲[cutpoint2，number_of_jobs)上的作业 拷贝 给子代1相同位置
//			jobNo = mothIndiv.v_chromosome[j];//获取母亲染色体上[cutpoint2，number_of_jobs)区间的作业
//			chIndiv2.v_chromosome[j] = jobNo;//将母亲[cutpoint2，number_of_jobs)上的作业 拷贝 给子代2相同位置
//		}
//		//以上 是将父母 两个切点 两侧的作业 直接拷贝 给子代1，子代2的相同位置
//
//		//下面开始填充子代1和子代2[cutpoint1,cutpoint2)之间的作业，子代1该剩余部分从母亲那里获得；子代2：父亲
//		index = cutpoint1;//从cutpoint1位置开始填充，若经循环后该位置被填充，则index++，继续填充下一个
//		for (j = 0; j < number_of_jobs; j++)
//		{
//			jobNo = mothIndiv.v_chromosome[j];//将母亲中每个作业与子代1现有的作业比较;
//			bt = false;
//			for (k = 0; k < cutpoint1; k++)//将当前母亲作业与子代1现有[0,cutpoint1)作业比较
//			{                              //若一直不同，继续往下执行，判断与子代1现有[cutpoint2,number_of_jobs)作业比较
//				if (jobNo == chIndiv1.v_chromosome[k])//若存在一个相同的，那么该母亲作业肯定不能加入现有子代1
//				{
//					bt = true;//故true，直接break掉，跳出当前这个for循环，不用进行与子代1[0,cutpoint1)区间剩余作业比较了
//					break;//但是可以接着往下与[cutpoint2,number_of_jobs)作业比较，只不过一直是true,也不会被加入
//				}         //子代1的cutpoint1位置上；index也保持不变，接着运行直至进行判断当前母亲作业的下个作业
//			}
//			for (k = cutpoint2; k < number_of_jobs; k++)//将当前母亲作业与子代1现有[cutpoint2,number_of_jobs)作业比较
//			{                            //若该母亲作业与两个区间内所有作业不同，故可以加入子代1现有的cutpoint1！一直false
//				if (jobNo == chIndiv1.v_chromosome[k])//若存在一个相同的，那么该母亲作业肯定不能加入现有子代1
//				{  //故true，直接break掉，跳出当前这个for循环，不用进行与子代1[cutpoint2,number_of_jobs)区间剩余作业比较了
//					bt = true;//此时index保持不变，接着执行下一个for循环判断当前母亲作业的下个作业
//					break;
//				}
//			}
//			if (bt == false)//若一直false，未出现true，说明当前母亲作业一直与两个区间的作业不同，故
//			{
//				chIndiv1.v_chromosome[index] = jobNo;//将该母亲作业的作业号，放入子代1当前的cutpoint1位置上
//				index++;//此时原cutpoint1已经被填充了，故++，继续填充下一个位置
//			}
//		}//以上完成子代1[cutpoint1,cutpoint2)位置作业的填充，从母亲获得。
//
//		//以下进行子代2[cutpoint1,cutpoint2)位置作业的填充，只不过是从父亲那获得基因。
//		index = cutpoint1;//从cutpoint1位置开始填充，若经循环后该位置被填充，则index++，继续填充下一个
//		for (j = 0; j < number_of_jobs; j++)
//		{
//			jobNo = fathIndiv.v_chromosome[j];//将父亲中每个作业与子代2中现有的作业比较;
//			bt = false;
//			for (k = 0; k < cutpoint1; k++)
//			{
//				if (jobNo == chIndiv2.v_chromosome[k])//将当前父亲作业与子代2现有[0,cutpoint1)作业比较
//				{                            //若一直不同，继续往下执行，判断与子代2现有[cutpoint2,number_of_jobs)作业比较
//					bt = true;//若存在一个相同的，那么该父亲作业肯定不能加入现有子代2
//					break;//故true，直接break掉，跳出当前这个for循环，不用进行与子代2[0,cutpoint1)区间剩余作业比较了
//				}//但是可以接着往下与[cutpoint2,number_of_jobs)作业比较，只不过一直是true,也不会被加入子代1的cutpoint1位置
//			}    //上；index也保持不变，一直运行直至进行判断当前母亲作业的下个作业
//			for (k = cutpoint2; k < number_of_jobs; k++)//将当前父亲作业与子代2现有[cutpoint2,number_of_jobs)作业比较
//			{                       //若该父亲作业与两个区间内所有作业都不同，故可以加入子代2现有的cutpoint1！一直false
//				if (jobNo == chIndiv2.v_chromosome[k])//若存在一个相同的，那么该父亲作业肯定不能加入现有子代2
//				{//故true，直接break掉，跳出当前这个for循环，不用进行与子代2[cutpoint2,number_of_jobs)区间剩余作业比较了
//					bt = true;//此时index保持不变，接着执行下一个for循环判断当前母亲作业的下个作业
//					break;
//				}
//			}
//			if (bt == false)//若一直false，未出现true,说明当前父亲作业一直与两个区间的作业不同，故
//			{
//				chIndiv2.v_chromosome[index] = jobNo;//将该父亲作业的作业号，放入子代2当前的cutpoint1位置上
//				index++;//此时原cutpoint1已经被填充了，故++，继续填充下一个位置
//			}//以上完成子代2[cutpoint1,cutpoint2)位置作业的填充，从父亲获得。
//		}
//		//以上完成 利用选出的 父母 进行交叉 产生子代1和2的 操作；完成了[0,number_of_jobs)的基因赋值。
//	
//
//		evaluate(chIndiv1);//调用函数，求子代1的目标值
//		current_number_of_fitness_evaluations++;
//		evaluate(chIndiv2);//调用函数，求子代2的目标值
//		current_number_of_fitness_evaluations++;
//		v_Chromo.push_back(chIndiv1);//将子代1 尾插 到 种群中
//		v_Chromo.push_back(chIndiv2);//将子代2 尾插 到 种群中
//	}
//	//cout << "交叉后：" << endl;
//	//for (int i = 0; i < v_Chromo.size(); i++)
//	//{
//	//	for (int j = 0; j < number_of_jobs; j++)
//	//	{
//	//		cout << v_Chromo[i].v_chromosome[j] << " ";
//	//	}
//	//	cout << endl;
//	//}
//}//经过croTimes次循环，共产生number_of_individuals个个体，此时种群规模是2*number_of_individuals，
////因为是在原来初始种群的基础上尾插的新种群:在init.cpp中产生的初始种群＋cross（）产生的尾插子代种群
//
////mutate
//void CGenetic::mutate()
//{
//	int  mutaNo;//变异对象（个体）号
//	int pos1, pos2, index, pos;
//	int jobNo;//第三方工具人
//	int i;
//
//	for (i = number_of_individuals; i < 2 * number_of_individuals; i++)//针对子代种群进行变异
//	{
//		mutaNo = i;//获取 变异对象（个体） 的 对象号
//		if (rand() / (RAND_MAX * 1.0) <= mutProb) //随机产生一个[0,1)的浮点数，与参数变异率mutProb比较
//		{                                         //若随机数<=变异率，则进行变异。否则，跳到最后，调用函数计算该个体目标值
//			if (rand() / (RAND_MAX * 1.0) <1)  //再随机产生一个[0,1)的浮点数，与0.5比较；若＜0.5，则进行两点变异
//			{                                                                     //且在区间[0,number_of_jobs上变动
//				pos1 = rand() % number_of_jobs;//随机产生一个位置1，取值[0,number_of_jobs)
//				pos2 = rand() % number_of_jobs;//随机产生一个位置2，取值[0,number_of_jobs)
//				while (pos1 == pos2)//若相同，则重新随机产生一个位置2
//				{
//					pos2 = rand() % number_of_jobs;
//				}
//				jobNo = v_Chromo[mutaNo].v_chromosome[pos1];//然后将两个位置的基因互换，种群中mutaNo对象（个体）的染色体上
//				v_Chromo[mutaNo].v_chromosome[pos1] = v_Chromo[mutaNo].v_chromosome[pos2];//的第pos1位置的基因 赋值给第三方 
//				v_Chromo[mutaNo].v_chromosome[pos2] = jobNo;//工具人jobNo；种群中mutaNo对象（个体）的染色体上pos2位置的基因 
//			}                                               //赋值给pos1；最后，将第三方工具人的值赋值给pos1                                                                                      
//		}
//		evaluate(v_Chromo[mutaNo]);//调用函数，计算变异（有可能不参与变异）个体的目标值；
//		current_number_of_fitness_evaluations++;
//	}
//
//	//for (int i = number_of_individuals; i < 2*number_of_individuals; i++)
//	//{
//	//	for (int j = 0; j < number_of_jobs; j++)
//	//	{
//	//		cout << v_Chromo[i].v_chromosome[j] << " ";//输出变异种群
//	//	}
//	//	cout << endl;
//	//}
//}//以上完成子代种群的变异操作，染色体长度与问题有关
