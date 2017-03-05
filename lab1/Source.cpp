#include <iostream>
#include <fstream>
#include "TPerceptron.h"

using namespace std;

int main(int argc, const char * argv[])
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	int nDim;
	in >> nDim;

	int countLearn;
	in >> countLearn;

	double ** x = new double*[countLearn];
	for (int i = 0; i < countLearn; i++)
	{
		x[i] = new double[nDim];
		for (int j = 0; j < nDim; j++)
			in >> x[i][j];
	}

	int * ansPreset = new int[countLearn];
	for (int i = 0; i < countLearn; i++)
	{
		in >> ansPreset[i];
		if (!ansPreset[i])
			ansPreset[i] -= 1;
	}
		

	TPerceptron p(nDim);
	cout << p.print() << endl;
	srand(static_cast<int>(time(0)));
	p.studWithTeacher(x, countLearn, ansPreset, out);
	


	int testCount;
	in >> testCount;

	double ** testX = new double*[testCount];
	for (int i = 0; i < testCount; i++)
	{
		testX[i] = new double[nDim];
		for (int j = 0; j < nDim; j++)
			in >> testX[i][j];
	}

	int * testAnswers = new int[testCount];
	for (int i = 0; i < testCount; i++)
	{
		in >> testAnswers[i];
		if (!testAnswers[i])
			testAnswers[i] -= 1;
	}
		

	int * curAnswers = p.signFunc(testX,testCount);

	for (int i = 0; i < testCount; i++)
	{
		out << curAnswers[i] << "\t" << testAnswers[i] << endl;
	}



	for (int i = 0; i < countLearn; i++)
		delete[] x[i];
	delete[] x;

	delete[] ansPreset;

	in.close();
	out.close();

	return 0;
}