


#include "headfile.h"
#include "random.h"
#include "Individual.h"


void CGenetic::MOOCBA()
{
	int i, j, k;

	int number_of_designs;
	int number_of_objectives;

	vector <CIndividual> v_archive;
	vector <CIndividual> v_new_individuals;
	int new_individuals_size = v_new_individuals.size(); 

	vector <vector <CIndividual>> v_sample;

	vector <int> v_S_A;
	vector <int> v_S_B;

	vector <vector <double>> v_sample_mean_value;
	vector <vector <double>> v_sample_variance_value;
	vector <vector <vector <double>>> v_sample_difference_value;

	int sample_size_row, sample_size_column;
	double sum_value, average_value, variance_value, difference_value;
	/**************************************************************************/
	//calculate mean and variance values...
	for (i=0; i<number_of_designs; i++)
	{
		vector <double> v_vec;
		v_sample_mean_value.push_back(v_vec);
		v_sample_variance_value.push_back(v_vec);
	}
	sample_size_row = v_sample.size();
	for (i=0; i<sample_size_row; i++)
	{
		for (j=0; j<number_of_objectives; j++)
		{
			sum_value = 0.0;
			sample_size_column = v_sample[i].size();
			for (k=0; k<sample_size_column; k++)
			{
				sum_value = sum_value + v_sample[i][k].v_objValue[j];
			}
			average_value = sum_value * 1.0 / sample_size_column;
			sum_value = 0.0;
			for (k=0; k<sample_size_column; k++)
			{
				sum_value = sum_value + (v_sample[i][k].v_objValue[j] - average_value) * (v_sample[i][k].v_objValue[j] - average_value) ;
			}
			variance_value = sqrt(sum_value * 1.0 / sample_size_column);
			v_sample_mean_value[i].push_back(average_value);
			v_sample_variance_value.push_back(variance_value);
		}
	}
	//calculate difference value...
	for (i=0; i<number_of_designs; i++)
	{
		vector <double> v_vec1;
		vector <vector <double>> v_vec2;
		for (j=0; j<number_of_designs; j++)
		{
			v_vec2.push_back(v_vec1);
		}
		v_sample_difference_value.push_back(v_vec2);
	}
	for (i=0; i<number_of_designs; i++)
	{
		for (j=0; j<number_of_designs; j++)
		{
			for (k=0; k<number_of_objectives; k++)
			{
				difference_value = v_sample_mean_value[i][k] - v_sample_mean_value[j][k];
				v_sample_difference_value[i][j].push_back(difference_value);
			}
		}
	}
	//construct the observed Pareto set...
	for (i=0; i<new_individuals_size; i++)
	{
		vector <double>().swap(v_new_individuals[i].v_objValue);
		for (j=0; j<number_of_objectives; j++)
		{
			v_new_individuals[i].v_objValue.push_back(0.0);
		}
		for (j=0; j<number_of_objectives; j++)
		{
			v_new_individuals[i].v_objValue[j] = v_sample_mean_value[i][j];
		}
	}

	//
	vector <vector <int>> v_theta_h;
	vector <vector <int>> v_theta_d_star;


	/**************************************************************************/
}
