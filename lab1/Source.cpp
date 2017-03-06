#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include "TPerceptron.h"

#define DEF_D 2
#define MAX_IN_DATA 100

using namespace std;

double ** rDataFile(char * filename, int order, int& count);
double ** rTestFile(char * filename, int order, int& count);
void wTestFile(char * filename, int * result, int count);
void saveNetwork(double * w, int order, char * filename);

int main(int argc, const char * argv[])
{
	
	char * dataFile = "data12.csv";
	char * testFile = "test_in.csv";
	char * netFile = "network_in.txt";
	char * outTestFile = "test_out.csv";
	char * outNetFile = "network_out.csv";

	int dataCount = 0;
	double ** data = rDataFile(dataFile, DEF_D, dataCount);
	int testCount = 0;
	double ** test = rTestFile(testFile, DEF_D, testCount);

	TPerceptron p;
	double * network = p.studWithTeacher(data, dataCount, 0.1);
	saveNetwork(network, DEF_D, outNetFile);

	int * testResult = p.signFunc(test,testCount);
	wTestFile(outTestFile, testResult, testCount);

	for (int i = 0; i < dataCount; i++)
		delete[] data[i];
	delete[] data;

	for (int i = 0; i < testCount; i++)
		delete[] test[i];
	delete[] test;

	delete[] network;
	delete[] testResult;

	return 0;
}

double ** rDataFile(char * filename, int order, int& count)
{
	ifstream in(filename);	
	count = 0;

	double ** res = new double*[MAX_IN_DATA];
	//cout << "DataFile" << endl;
	while (!in.eof())
	{
		res[count] = new double[order+1];
		for (int j = 0; j < order; j++)
		{
			string input;
			getline(in, input, ';');
			res[count][j] = atof(input.data());
			//cout << setw(5) << res[count][j] << "\t";
		}
			
		string input;
		getline(in,input,'\n');
		double dInp = atof(input.data());

		if (dInp == 0) res[count][order] = -1;
		else res[count][order] = dInp;
		//cout << setw(5) << res[count][order] << endl;

		count++;
	}

	in.close();
	return res;
}

double ** rTestFile(char * filename, int order, int& count)
{
	ifstream in(filename);
	count = 0;

	double ** res = new double*[MAX_IN_DATA];
	//cout << "TestFile" << endl;
	while (!in.eof())
	{
		res[count] = new double[order];
		for (int j = 0; j < order; j++)
		{
			string input;
			getline(in, input, ';');
			res[count][j] = atof(input.data());
			//cout << setw(5) << res[count][j] << "\t";
		}
		//cout << endl;
		count++;
	}

	count--;
	in.close();
	return res;
}

void saveNetwork(double * w, int order, char * filename)
{
	ofstream out(filename);
	for (int i = 0; i <= order; i++)
		out << setw(10) << setprecision(6) << w[i];
	out.close();
}

void wTestFile(char * filename, int * result, int count)
{
	ofstream out(filename);
	for (int i = 0; i < count; i++)
		out << setprecision(1) << result[i] << endl;
	out.close();
}