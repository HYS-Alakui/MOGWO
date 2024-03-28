#pragma once




#include "headfile.h"


class CJob
{
private:
public:
	/*	vector <double> ProcessTime;
	vector <double> EnergyConsumption;
	double DueDate;
	vector <int> RestWorkstations;
	*/

	vector < double> ProcessTime;
	vector <int> RestWorkstationsAtStage1;
	vector <int> RestWorkstationsAtStage2;
	double DueDate;
	vector <double> EnergyConsumption;

	int StageIndex;
};