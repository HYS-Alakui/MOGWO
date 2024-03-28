//#include "Genetic.h"
//#include "Individual.h"
//#include "headfile.h"
//#include "Vehicle.h"
//#include "Chromosome.h"
//
//void CGenetic::IGA()
//{
//	//cout << "------------7、执行IGA方法---------" << endl;
//	//输出当前的OMEGA种群
//	//cout << "OMEGA" << endl;
//	//for (int i = 0; i < v_Omega_individuals.size(); i++)
//	//{
//	//	for (int j = 0; j < number_of_jobs1; j++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_chromosome1[j].factory_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_chromosome1[j].job_number << " ";
//	//	}
//	//	cout << endl;
//
//	//	for (int j = 0; j < number_of_jobs2*number_of_operations; j++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_chromosome2[j].operation_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int j = number_of_jobs2 * number_of_operations; j < v_Omega_individuals[i].v_chromosome2.size(); j++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_chromosome2[j].machine_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int k = 0; k < v_Omega_individuals[i].v_objective_value.size(); k++)
//	//	{
//	//		cout << v_Omega_individuals[i].v_objective_value[k] << " ";
//	//	}
//	//	cout << endl;
//	//}
//
//
//
//	//对OMEGA种群中每个个体执行搜索
//	vector <CIndividual>().swap(v_Omega_individuals_temp);//清空容器
//	vector <CIndividual> v_Omega_individuals_temp(v_Omega_individuals);//拷贝构造，方便后续使用
//	vector <CIndividual>().swap(v_iga_individuals);
//
//	for (int i = 0; i < v_Omega_individuals_temp.size(); i++)
//	{
//		//cout << "I = " << i + 1 << endl;
//		CIndividual best_ig_indiv;
//		best_ig_indiv = v_Omega_individuals_temp[i];
//		//cout << "best_ig_indiv.key_cell = " << best_ig_indiv.key_cell << endl;
//		//执行IGA搜索
//		int ig_count = 0;
//		if (best_ig_indiv.key_cell == 0)
//		{
//			//对DFSP执行IGA
//			while (ig_count < ig_count_number)
//			{
//				ig_count = ig_count + 1;
//				//cout << "ig_count = " << ig_count << endl;
//				//执行破坏和重组操作
//				CIndividual ig_indiv_temp;
//				ig_indiv_temp = v_Omega_individuals_temp[i];
//				assign(ig_indiv_temp);
//				evaluate_DFSP(ig_indiv_temp);
//				evaluate_FJSP(ig_indiv_temp);
//				evaluate(ig_indiv_temp);
//
//				//for (int j = 0; j < number_of_jobs1; j++)
//				//{
//				//	cout << ig_indiv_temp.v_chromosome1[j].factory_number << " ";
//				//}
//				//cout << endl;
//				//for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)
//				//{
//				//	cout << ig_indiv_temp.v_chromosome1[j].job_number << " ";
//				//}
//				//cout << endl;
//				//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
//				//{
//				//	cout << ig_indiv_temp.v_chromosome2[j].operation_number << " ";
//				//}
//				//cout << endl;
//				//for (int j = number_of_jobs2 * number_of_operations; j < ig_indiv_temp.v_chromosome2.size(); j++)
//				//{
//				//	cout << ig_indiv_temp.v_chromosome2[j].machine_number << " ";
//				//}
//				//cout << endl;
//				//for (int ob = 0; ob < ig_indiv_temp.v_objective_value.size(); ob++)
//				//{
//				//	cout << ig_indiv_temp.v_objective_value[ob] << " ";
//				//}
//				//cout << endl;
//
//				//step1:随机选取几个job并存入基因段
//				vector <int> v_des_job0;
//				vector <int>().swap(v_des_job0);
//				int rand_job_number11 = rand() % number_of_jobs1 + 1;
//				int rand_job_number21 = rand() % number_of_jobs1 + 1;
//				int rand_job_number31 = rand() % number_of_jobs1 + 1;
//				while (rand_job_number11 == rand_job_number21 || rand_job_number11 == rand_job_number31 || rand_job_number21 == rand_job_number31)
//				{
//					rand_job_number11 = rand() % number_of_jobs1 + 1;
//					rand_job_number21 = rand() % number_of_jobs1 + 1;
//					rand_job_number31 = rand() % number_of_jobs1 + 1;
//				}
//				v_des_job0.push_back(rand_job_number11);
//				v_des_job0.push_back(rand_job_number21);
//				v_des_job0.push_back(rand_job_number31);
//				//cout << "rand_job_number11 = " << rand_job_number11 << endl;
//				//cout << "rand_job_number21 = " << rand_job_number21 << endl;
//				//cout << "rand_job_number31 = " << rand_job_number31 << endl;
//				//system("pause");
//
//				//step2:创建一个作业列，储存去除3个随机job的剩余作业
//				vector <int> v_job_list;
//				for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)
//				{
//					if (ig_indiv_temp.v_chromosome1[j].job_number != rand_job_number11 && ig_indiv_temp.v_chromosome1[j].job_number != rand_job_number21 && ig_indiv_temp.v_chromosome1[j].job_number != rand_job_number31)
//					{
//						v_job_list.push_back(ig_indiv_temp.v_chromosome1[j].job_number);
//					}
//				}
//				//cout << "临时序列" << endl;
//				//for (int j = 0; j < v_job_list.size(); j++)
//				//{
//				//	cout << v_job_list[j] << " ";
//				//}
//				//cout << endl;
//
//				//step3.1:将段job插入临时工序序列的每一个位置，得到一个新的序列ls_op_list
//				//step3.2:创建一个ls_indiv，并使用新的序列ls_op_list
//				//step3.3:求目标值，存入一个容器中
//				//step3.4:还原，插入下一个位置
//				double** p_iga_indiv_objective;
//				p_iga_indiv_objective = new double*[number_of_jobs1];
//				for (int j = 0; j < number_of_jobs1; j++)
//				{
//					p_iga_indiv_objective[j] = new double[number_of_objectives];
//				}
//
//				for (int j = 0; j < number_of_jobs1 - 2; j++)
//				{
//					//cout << "j =" << j << endl;
//					v_job_list.insert(v_job_list.begin() + j, v_des_job0.begin(), v_des_job0.end());
//
//					CIndividual ig_indiv; // step5.2:创建一个ls_indiv，并使用新的序列ls_op_list
//					ig_indiv = ig_indiv_temp;
//					for (int k = 0; k < number_of_jobs1; k++)
//					{
//						ig_indiv.v_chromosome1[k].job_number = v_job_list[k];
//						//cout << ig_indiv.v_chromosome1[k].job_number << " ";
//					}
//					//cout << endl;
//
//					assign(ig_indiv);//step5.3:求目标值，存入一个容器中
//					evaluate_DFSP(ig_indiv);//step5.3:求目标值，存入一个容器中
//					evaluate_FJSP(ig_indiv);//step5.3:求目标值，存入一个容器中
//					evaluate(ig_indiv);//step5.3:求目标值，存入一个容器中
//					for (int ob = 0; ob < ig_indiv.v_objective_value.size(); ob++)
//					{
//						//cout << ig_indiv.v_objective_value[ob] << " ";
//						p_iga_indiv_objective[j][ob] = ig_indiv.v_objective_value[ob];
//					}
//					//cout << endl;
//
//					v_job_list.erase(v_job_list.begin() + j, v_job_list.begin() + j + 3);//step5.4:还原，插入下一个位置
//					//system("pause");
//				}
//
//				//step4:找到最佳位置
//				int b_iga_indiv_index = 0;
//				double b_iga_indiv_ob1 = p_iga_indiv_objective[0][0];
//				double b_iga_indiv_ob2 = p_iga_indiv_objective[0][1];
//				for (int j = 0; j < number_of_jobs1 - 2; j++)
//				{
//					if (p_iga_indiv_objective[j][0] <= b_iga_indiv_ob1 && p_iga_indiv_objective[j][1] <= b_iga_indiv_ob2)
//					{
//						b_iga_indiv_index = j;
//						b_iga_indiv_ob1 = p_iga_indiv_objective[j][0];
//						b_iga_indiv_ob2 = p_iga_indiv_objective[j][1];
//					}
//				}
//				//cout << "b_iga_indiv_index = " << b_iga_indiv_index << endl;
//
//				//step5:获得最佳位置的解
//				v_job_list.insert(v_job_list.begin() + b_iga_indiv_index, v_des_job0.begin(), v_des_job0.end());
//				CIndividual b_ig_indiv;
//				b_ig_indiv = ig_indiv_temp;
//				for (int k = 0; k < number_of_jobs1; k++)
//				{
//					b_ig_indiv.v_chromosome1[k].job_number = v_job_list[k];
//					//cout << b_ig_indiv.v_chromosome1[k].job_number << " ";
//				}
//				//cout << endl;
//
//				assign(b_ig_indiv);//step5.3:求目标值，存入一个容器中
//				evaluate_DFSP(b_ig_indiv);//step5.3:求目标值，存入一个容器中
//				evaluate_FJSP(b_ig_indiv);//step5.3:求目标值，存入一个容器中
//				evaluate(b_ig_indiv);
//				//for (int ob = 0; ob < b_ig_indiv.v_objective_value.size(); ob++)
//				//{
//				//	cout << b_ig_indiv.v_objective_value[ob] << " ";
//				//}
//				//cout << endl;
//
//				//step6:从best_ig_indiv与b_ig_indiv中选取一个个体用于更新best_ig_indiv
//				int domRel = 3;//判断两个个体的支配关系
//				domRelation(b_ig_indiv, best_ig_indiv, domRel);
//				//cout << "domRel = " << domRel << endl;
//				if (domRel == 1)
//				{
//					best_ig_indiv = b_ig_indiv;//更新最佳解;
//				}
//
//				//step7:释放
//				for (int i = 0; i < number_of_jobs1; i++)
//				{
//					delete[] p_iga_indiv_objective[i];
//				}
//				delete[] p_iga_indiv_objective;
//				//继续count++
//
//			}
//			//system("pause");
//			v_iga_individuals.push_back(best_ig_indiv);
//		}
//		else
//		{
//			//对FJSP执行IGA
//			while (ig_count < ig_count_number)
//			{
//				ig_count = ig_count + 1;
//
//				//执行破坏和重组操作
//				CIndividual ig_indiv_temp;
//				ig_indiv_temp = v_Omega_individuals_temp[i];
//				assign(ig_indiv_temp);
//				evaluate_DFSP(ig_indiv_temp);
//				evaluate_FJSP(ig_indiv_temp);
//				evaluate(ig_indiv_temp);
//
//				//for (int j = 0; j < number_of_jobs1; j++)
//				//{
//				//	cout << ig_indiv_temp.v_chromosome1[j].factory_number << " ";
//				//}
//				//cout << endl;
//				//for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)
//				//{
//				//	cout << ig_indiv_temp.v_chromosome1[j].job_number << " ";
//				//}
//				//cout << endl;
//				//for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
//				//{
//				//	cout << ig_indiv_temp.v_chromosome2[j].operation_number << " ";
//				//}
//				//cout << endl;
//				//for (int j = number_of_jobs2 * number_of_operations; j < ig_indiv_temp.v_chromosome2.size(); j++)
//				//{
//				//	cout << ig_indiv_temp.v_chromosome2[j].machine_number << " ";
//				//}
//				//cout << endl;
//				//for (int ob = 0; ob < ig_indiv_temp.v_objective_value.size(); ob++)
//				//{
//				//	cout << ig_indiv_temp.v_objective_value[ob] << " ";
//				//}
//				//cout << endl;
//
//				//step1:随机选取几个job并存入基因段
//				vector <int> v_des_job;
//				vector <int>().swap(v_des_job);
//				int rand_job_number1 = rand() % number_of_jobs2 + 1;
//				int rand_job_number2 = rand() % number_of_jobs2 + 1;
//				int rand_job_number3 = rand() % number_of_jobs2 + 1;
//				while (rand_job_number1 == rand_job_number2 || rand_job_number1 == rand_job_number3 || rand_job_number2 == rand_job_number3)
//				{
//					rand_job_number1 = rand() % number_of_jobs2 + 1;
//					rand_job_number2 = rand() % number_of_jobs2 + 1;
//					rand_job_number3 = rand() % number_of_jobs2 + 1;
//				}
//				v_des_job.push_back(rand_job_number1);
//				v_des_job.push_back(rand_job_number2);
//				v_des_job.push_back(rand_job_number3);
//				//cout << "rand_job_number1 = " << rand_job_number1 << endl;
//				//cout << "rand_job_number2 = " << rand_job_number2 << endl;
//				//cout << "rand_job_number3 = " << rand_job_number3 << endl;
//				//system("pause");
//
//				//step2:创建一个工序序列，储存去除3个随机job的最后一道工序的剩余工序
//				vector <int> v_oper_list;
//				int rand_job_num_count1 = 0;
//				int rand_job_num_count2 = 0;
//				int rand_job_num_count3 = 0;
//				for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
//				{
//					if (ig_indiv_temp.v_chromosome2[j].operation_number == rand_job_number1 || ig_indiv_temp.v_chromosome2[j].operation_number == rand_job_number2 || ig_indiv_temp.v_chromosome2[j].operation_number == rand_job_number3)
//					{
//
//						if (ig_indiv_temp.v_chromosome2[j].operation_number == rand_job_number1)
//						{
//							rand_job_num_count1++;
//							//cout << "rand_job_num_count1 = " << rand_job_num_count1 << endl;
//							if (rand_job_num_count1 != 3)
//							{
//								//cout << ig_indiv_temp.v_chromosome2[j].operation_number << endl;
//								v_oper_list.push_back(ig_indiv_temp.v_chromosome2[j].operation_number);
//							}
//						}
//
//						if (ig_indiv_temp.v_chromosome2[j].operation_number == rand_job_number2)
//						{
//							rand_job_num_count2++;
//							//cout << "rand_job_num_count2 = " << rand_job_num_count2 << endl;
//							if (rand_job_num_count2 != 3)
//							{
//								//cout << ig_indiv_temp.v_chromosome2[j].operation_number << endl;
//								v_oper_list.push_back(ig_indiv_temp.v_chromosome2[j].operation_number);
//							}
//						}
//
//						if (ig_indiv_temp.v_chromosome2[j].operation_number == rand_job_number3)
//						{
//							rand_job_num_count3++;
//							//cout << "rand_job_num_count3 = " << rand_job_num_count3 << endl;
//							if (rand_job_num_count3 != 3)
//							{
//								//cout << ig_indiv_temp.v_chromosome2[j].operation_number << endl;
//								v_oper_list.push_back(ig_indiv_temp.v_chromosome2[j].operation_number);
//							}
//						}
//
//					}
//					else
//					{
//						v_oper_list.push_back(ig_indiv_temp.v_chromosome2[j].operation_number);
//					}
//				}
//				//cout << "临时序列" << endl;
//				//for (int j = 0; j < v_oper_list.size(); j++)
//				//{
//				//	cout << v_oper_list[j] << " ";
//				//}
//				//cout << endl;
//
//				//step3.1:将段job插入临时工序序列的每一个位置，得到一个新的序列ls_op_list
//				//step3.2:创建一个ls_indiv，并使用新的序列ls_op_list
//				//step3.3:求目标值，存入一个容器中
//				//step3.4:还原，插入下一个位置
//				double** p_ig_indiv_objective;
//				p_ig_indiv_objective = new double*[number_of_jobs2 * number_of_operations];
//				for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
//				{
//					p_ig_indiv_objective[j] = new double[number_of_objectives];
//				}
//
//				for (int j = 0; j < number_of_jobs2 * number_of_operations - 2; j++)
//				{
//					//cout << "j =" << j << endl;
//					v_oper_list.insert(v_oper_list.begin() + j, v_des_job.begin(), v_des_job.end());
//
//					CIndividual ig_indiv; // step5.2:创建一个ls_indiv，并使用新的序列ls_op_list
//					ig_indiv = ig_indiv_temp;
//					for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
//					{
//						ig_indiv.v_chromosome2[k].operation_number = v_oper_list[k];
//						//cout << ig_indiv.v_chromosome2[k].operation_number << " ";
//					}
//					//cout << endl;
//					//补充工序序列向量的job号信息和工序顺序信息
//					for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
//					{
//						ig_indiv.v_chromosome2[k].job_number = ig_indiv.v_chromosome2[k].operation_number;
//					}
//					for (int k = 0; k < number_of_jobs2; k++)//判断是每个job的第几道工序
//					{
//						int current_job_number = k + 1;
//						int count = 0;
//						for (int c = 0; c < number_of_jobs2 * number_of_operations; c++)
//						{
//							if (current_job_number == ig_indiv.v_chromosome2[c].job_number)
//							{
//								count = count + 1;
//								ig_indiv.v_chromosome2[c].operation_index = count;
//							}
//							continue;
//						}
//					}
//
//					assign(ig_indiv);//step5.3:求目标值，存入一个容器中
//					evaluate_DFSP(ig_indiv);//step5.3:求目标值，存入一个容器中
//					evaluate_FJSP(ig_indiv);//step5.3:求目标值，存入一个容器中
//					evaluate(ig_indiv);//step5.3:求目标值，存入一个容器中
//					for (int ob = 0; ob < ig_indiv.v_objective_value.size(); ob++)
//					{
//						//cout << ig_indiv.v_objective_value[ob] << " ";
//						p_ig_indiv_objective[j][ob] = ig_indiv.v_objective_value[ob];
//					}
//					//cout << endl;
//
//					v_oper_list.erase(v_oper_list.begin() + j, v_oper_list.begin() + j + 3);//step5.4:还原，插入下一个位置
//					//system("pause");
//				}
//
//				//step4:找到最佳位置
//				int b_ig_indiv_index = 0;
//				double b_ig_indiv_ob1 = p_ig_indiv_objective[0][0];
//				double b_ig_indiv_ob2 = p_ig_indiv_objective[0][1];
//				for (int j = 0; j < number_of_jobs2 * number_of_operations - 2; j++)
//				{
//					if (p_ig_indiv_objective[j][0] <= b_ig_indiv_ob1 && p_ig_indiv_objective[j][1] <= b_ig_indiv_ob2)
//					{
//						b_ig_indiv_index = j;
//						b_ig_indiv_ob1 = p_ig_indiv_objective[j][0];
//						b_ig_indiv_ob2 = p_ig_indiv_objective[j][1];
//					}
//				}
//				//cout << "b_ig_indiv_index = " << b_ig_indiv_index << endl;
//
//				//step5:获得最佳位置的解
//				v_oper_list.insert(v_oper_list.begin() + b_ig_indiv_index, v_des_job.begin(), v_des_job.end());
//				CIndividual b_ig_indiv;
//				b_ig_indiv = ig_indiv_temp;
//				for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
//				{
//					b_ig_indiv.v_chromosome2[k].operation_number = v_oper_list[k];
//					//cout << b_ig_indiv.v_chromosome2[k].operation_number << " ";
//				}
//				//cout << endl;
//				//补充工序序列向量的job号信息和工序顺序信息
//				for (int k = 0; k < number_of_jobs2 * number_of_operations; k++)
//				{
//					b_ig_indiv.v_chromosome2[k].job_number = b_ig_indiv.v_chromosome2[k].operation_number;
//				}
//				for (int k = 0; k < number_of_jobs2; k++)//判断是每个job的第几道工序
//				{
//					int current_job_number = k + 1;
//					int count = 0;
//					for (int c = 0; c < number_of_jobs2 * number_of_operations; c++)
//					{
//						if (current_job_number == b_ig_indiv.v_chromosome2[c].job_number)
//						{
//							count = count + 1;
//							b_ig_indiv.v_chromosome2[c].operation_index = count;
//						}
//						continue;
//					}
//				}
//				assign(b_ig_indiv);//step5.3:求目标值，存入一个容器中
//				evaluate_DFSP(b_ig_indiv);//step5.3:求目标值，存入一个容器中
//				evaluate_FJSP(b_ig_indiv);//step5.3:求目标值，存入一个容器中
//				evaluate(b_ig_indiv);
//				//for (int ob = 0; ob < b_ig_indiv.v_objective_value.size(); ob++)
//				//{
//				//	cout << b_ig_indiv.v_objective_value[ob] << " ";
//				//}
//				//cout << endl;
//
//				//step6:从best_ig_indiv与b_ig_indiv中选取一个个体用于更新best_ig_indiv
//				int domRel = 3;//判断两个个体的支配关系
//				domRelation(b_ig_indiv, best_ig_indiv, domRel);
//				//cout << "domRel = " << domRel << endl;
//				if (domRel == 1)
//				{
//					best_ig_indiv = b_ig_indiv;//更新最佳解;
//				}
//
//				//step7:释放
//				for (int i = 0; i < number_of_jobs2 * number_of_operations; i++)
//				{
//					delete[] p_ig_indiv_objective[i];
//				}
//				delete[] p_ig_indiv_objective;
//				//继续count++
//
//			}
//			//system("pause");
//			v_iga_individuals.push_back(best_ig_indiv);
//		}
//	
//		//system("pause");
//	}
//
//
//
//	//cout << "IGA-pop" << endl;
//	//for (int i = 0; i < v_iga_individuals.size(); i++)
//	//{
//	//	for (int j = 0; j < number_of_jobs1; j++)
//	//	{
//	//		cout << v_iga_individuals[i].v_chromosome1[j].factory_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int j = number_of_jobs1; j < 2 * number_of_jobs1; j++)
//	//	{
//	//		cout << v_iga_individuals[i].v_chromosome1[j].job_number << " ";
//	//	}
//	//	cout << endl;
//
//	//	for (int j = 0; j < number_of_jobs2 * number_of_operations; j++)
//	//	{
//	//		cout << v_iga_individuals[i].v_chromosome2[j].operation_number << " ";
//	//	}
//	//	cout << endl;
//	//	for (int j = number_of_jobs2 * number_of_operations; j < v_iga_individuals[i].v_chromosome2.size(); j++)
//	//	{
//	//		cout << v_iga_individuals[i].v_chromosome2[j].machine_number << " ";
//	//	}
//	//	cout << endl;
//
//	//	for (int ob = 0; ob < v_iga_individuals[i].v_objective_value.size(); ob++)
//	//	{
//	//		cout << v_iga_individuals[i].v_objective_value[ob] << " ";
//	//	}
//	//	cout << endl;
//	//}
//	//system("pause");
//}