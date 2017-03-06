#include <iostream>
#include <fstream>
#include <cstring>
#include "TPerceptron.h"

#define DEF_DIMENSIONS 2

using namespace std;

void learningFromFile(char * filename);

int main(int argc, const char * argv[])
{
	//input Learn/Test
	ifstream inLT("data12.csv");
	ifstream inNet("network.txt");
	ofstream outTest("test_out.txt");
	ofstream outNet("network.txt");

	int nDim = DEF_DIMENSIONS;
	//inLearn >> nDim;

	int countLearn = 0;

	double ** x = new double*[countLearn];
	int * ansPreset = new int[countLearn];
	while(!inLT.eof())
	{
		x[i] = new double[nDim];
		for (int j = 0; j < nDim; j++)
			inLearn >> x[i][j];
		inLearn >> ansPreset[i];
		if (!ansPreset[i])
			ansPreset[i] -= 1;
	}

	TPerceptron p(nDim);
	cout << p.print() << endl;
	srand(static_cast<int>(time(0)));
	p.studWithTeacher(x, ansPreset, countLearn, );
	


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

void learningFromFile(char * filename)
{

}
