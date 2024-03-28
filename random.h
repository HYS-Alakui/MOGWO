


#include "Genetic.h"
#include "headfile.h"
#include "Individual.h"



#ifndef _RANDOM_H_
#define _RANDOM_H_

double random01();
void random_permuation(vector <int>& v_perm, int min, int max);
void random_series(vector <double>& v_perm, double min, double max, int size);
int random_integer(int low,int high);
void random_unit_vector(vector <double>& v_unit_vector, int length);
double gaussian();

#endif