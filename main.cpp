#include "Genetic.h"
#include "headfile.h"
#include "RankSequ.h"
#include "Individual.h"
#include  <ctime>

char findex0[50]; // 定义字符数组，数组长度50
char findex1[50];
char findex2[50];
char findex3[50];
char findex4[50];
char filename[100];//定义字符数组，数组长度100                  //实际上是把字符串中的第一个字符的地址赋给extendname
char* extendname = ".txt";//定义字符指针变量extendname，用字符串常量双引号 ".txt"对他初始化。对字符串指针变量的初始化


void main()
{
	srand((unsigned)time(NULL));
	//************************************************************
	int number_of_factories, number_of_machines,number_of_jobs1,number_of_jobs2;

	int *p_number_of_factories = new int[3];
	int *p_number_of_machines = new int[2];
	int *p_number_of_jobs = new int[5];

	p_number_of_factories[0] = 2;
	p_number_of_factories[1] = 3;
	p_number_of_factories[2] = 4;
	p_number_of_machines[0] = 5;
	p_number_of_machines[1] = 10;
	p_number_of_jobs[0] = 20;
	p_number_of_jobs[1] = 50;
	p_number_of_jobs[2] = 100;
	p_number_of_jobs[3] = 150;
	p_number_of_jobs[4] = 200;
	int SOLVE_TIMES = 1;//运行20次

	for (int i = 0; i < 1;i++)
	{
		number_of_factories = p_number_of_factories[i];
		for (int j =0; j < 1; j++)
		{
			number_of_machines = p_number_of_machines[j];
			for (int k = 2; k < 3; k++)
			{
				number_of_jobs1 = p_number_of_jobs[k];
				for (int solve_times = 1; solve_times <= SOLVE_TIMES; solve_times++)
				{
					clock_t start, finish;
					start = clock();//开始计时
					srand(time(NULL)); /*产生随机种子  把NULL换成0也行*/


					//读入数据
					_itoa_s(number_of_factories, findex0, 10);
					_itoa_s(number_of_machines, findex1, 10);
					_itoa_s(number_of_jobs1, findex2, 10);
					strcpy_s(filename, ".\\data_MO");//拷贝后面字符串给前面字符串
					strcat_s(filename, "\\");//连接两个字符串，连接后放在第一个数组中
					strcat_s(filename, findex0);
					strcat_s(filename, "-");
					strcat_s(filename, findex1);
					strcat_s(filename, "-");
					strcat_s(filename, findex2);
					strcat_s(filename, extendname);


					CGenetic Instance;
					Instance.finData(filename);
					//system("pause");
					Instance.run();
					//system("pause");
					finish = clock();//结束计时
					double time1 = (double)(finish - start) / CLOCKS_PER_SEC;

					//输出结果
					_itoa_s(number_of_factories, findex0, 10);
					_itoa_s(number_of_machines, findex1, 10);
					_itoa_s(number_of_jobs1, findex2, 10);
					_itoa_s(solve_times, findex3, 10);
					strcpy_s(filename, ".\\result-MOGWO");//拷贝函数，将.\\result_NSGAII字符串转换给filename
					strcat_s(filename, "\\result-");//字符串连接函数：连接两个字符串
					strcat_s(filename, findex0);//number_factories
					strcat_s(filename, "-");
					strcat_s(filename, findex1);//number_machines
					strcat_s(filename, "-");
					strcat_s(filename, findex2);//number_jobs
					strcat_s(filename, "\\");
					strcat_s(filename, "\\result-");//连接函数，且结果放在前面字符串
					strcat_s(filename, findex0);
					strcat_s(filename, "-");
					strcat_s(filename, findex1);
					strcat_s(filename, "-");
					strcat_s(filename, findex2);
					strcat_s(filename, "-");
					strcat_s(filename, findex3);
					strcat_s(filename, extendname);
					//以上输出结果是：.\\result_NSGAII\\result-findex0-findex1-findex2\\result-findex0-findex1-findex2-findex3.txt
					cout << filename << endl;

					Instance.foutData(filename, time1);

					//system("pause");
				}

			}
		}
	}
	delete[] p_number_of_factories;
	delete[] p_number_of_jobs;
	delete[] p_number_of_machines;
}
