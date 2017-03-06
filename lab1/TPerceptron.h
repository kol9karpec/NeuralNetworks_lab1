#pragma once

#include <ctime>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

#define DEF_DIMENTION 2
#define RAND_UP_B 0.3
#define RAND_BOT_B -0.3

class TPerceptron
{

private:
	double * w;
	double b;
	int order;

public:
	TPerceptron();
	TPerceptron(double * w, double b,int order);
	TPerceptron(TPerceptron&);

	TPerceptron& setW(double * w);
	TPerceptron& setB(double b);

	int getOrder() { return order; }

	int signFunc(double * x);
	int * signFunc(double ** x, int count);

	char * print();
	double * studWithTeacher(double ** data, int count, double k);
	/*
		template of double ** data
		x[i] = {x1, ... , xn, answer}, i = 0 ... count-1;
	*/

	
	static bool arrCompare(int * a, double ** b, int order, int count);
	
	~TPerceptron();
};

