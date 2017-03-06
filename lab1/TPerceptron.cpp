#include "TPerceptron.h"



TPerceptron::TPerceptron()
{
	order = DEF_DIMENTION;
	w = new double[order];
	for (int i = 0; i < order; i++)
		w[i] = 0;
	b = 0;
}

TPerceptron::TPerceptron(double * w, double b, int order)
{
	w = new double[order];
	for (int i = 0; i < order; i++)
		this->w[i] = w[i];
	this->order = order;
	this->b = b;
}

TPerceptron::TPerceptron(TPerceptron & p)
{
	order = p.order;
	w = new double[order];
	for (int i = 0; i < order; i++)
		this->w[i] = p.w[i];
	b = p.b;
}

TPerceptron & TPerceptron::setW(double * w)
{
	for (int i = 0; i < order; i++)
		this->w[i] = w[i];
	return *this;
}

TPerceptron & TPerceptron::setB(double b)
{
	this->b = b;
	return *this;
}

int TPerceptron::signFunc(double * x)
{
	double sum = 0;
	for (int i = 0; i < order; i++)
		sum += w[i] * x[i];
	sum -= b;
	return (sum > 0 ? 1 : -1);
}

int * TPerceptron::signFunc(double ** x, int count)
{
	int * result = new int[count];
	for (int i = 0; i < count; i++)
		result[i] = signFunc(x[i]);
	return result;
}

char * TPerceptron::print()
{
	char * result = new char[5000];
	strcpy(result, "");
	char * buff = new char[256];
	for (int i = 0; i < order; i++)
	{
		
		strcpy(buff,"");
		sprintf(buff, "%1.7f", w[i]);
		strcat(result,buff);
		strcat(result, "\t");
		
	}
	strcpy(buff, "");
	sprintf(buff, "%1.7f", b);
	strcat(result, buff);
	delete[] buff;

	return result;
}

double * TPerceptron::studWithTeacher(double ** data, int count, double k)
{
	srand(time(0));
	for (int i = 0; i < order; i++)
	{
		double f = (double)rand() / RAND_MAX;
		w[i] = RAND_BOT_B + f * (RAND_UP_B - RAND_BOT_B);
	}
	
	double f = (double)rand() / RAND_MAX;
	b = RAND_BOT_B + f * (RAND_UP_B - RAND_BOT_B);

	double * result = new double[order+1];
	bool isContinue = true;	

	while (isContinue)
	{
		//random pair from preset
		int numOfAns = rand() % count;

		//result with current weight vector
		double curRes = signFunc(data[numOfAns]);

		//modifying w vector if result incorrect
		double delta = data[numOfAns][order] - curRes;
		if (delta != 0)
		{
			for (int i = 0; i < order; i++)
				this->w[i] += k*delta*(data[numOfAns][i]);
			this->b -= k*delta;
		}	
		
		int * newRes = signFunc(data, count);
		isContinue = !(arrCompare(newRes,data,order,count));
		delete[] newRes;
	}

	for (int i = 0; i < order; i++)
		result[i] = w[i];

	result[order] = b;

	return result;
}

bool TPerceptron::arrCompare(int * a, double ** b, int order, int count)
{
	bool result = true;
	for (int i = 0; i < count; i++)
		if (a[i] != (int)b[i][order]) result = false;
	return result;
}


TPerceptron::~TPerceptron()
{
	delete[] w;
	w = NULL;
	b = 0;
	order = 0;
}
