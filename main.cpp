#pragma once

#include "IterMethtod.h"
#include <ctime>

bool randomInput(Matrix& A, Matrix& B, double accuracy, IterMethod& method)
{
	std::cout << "type size" << std::endl;
	int size = -1;
	std::cin >> size;
	if(size<0)
	{
		std::cout << "incorrect input" << std::endl;
		return false;
	}

	std::cout << "wait..." << std::endl;

	int tryNumber = 0;
	const int maxTry = 1000000;
	srand(time(0));
	do
	{
		tryNumber++;
		if (tryNumber >= maxTry)
		{
			std::cout << "can't generate correct matrix" << std::endl;
			return false;
		}
		A.createRandom(size, size);
		B.createRandom(size, 1);
	} while (!method.calculate(A, B, accuracy));

	return true;
}

bool consoleInput(Matrix& A, Matrix& B, double accuracy, IterMethod& method)
{
	try
	{
		std::cout << "type A matrix" << std::endl;
		A.getFromInputSquare();
		std::cout << "type B matrix" << std::endl;
		B.getFromInputColumn(A.getHeight());
	}
	catch (std::exception& e)
	{
		std::cout << "incorrect input" << std::endl;
		return false;
	}

	if (!method.calculate(A, B, accuracy))
	{
		std::cout << "incorrect input or matrix isn't convergence" << std::endl;
		return false;
	}

	return true;
}

bool fileInput(Matrix& A, Matrix& B, double accuracy, IterMethod& method)
{
	std::cout << "type filename" << std::endl;
	std::string filename;
	std::cin >> filename;
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "incorrect input" << std::endl;
		return false;
	}

	try
	{
		A.getFromFileSquare(file);
		B.getFromFileColumn(file, A.getHeight());
	}
	catch (std::exception& e)
	{
		std::cout << "incorrect input" << std::endl;
		return false;
	}

	if (!method.calculate(A, B, accuracy))
	{
		std::cout << "incorrect input or matrix isn't convergence" << std::endl;
		return false;
	}

	return true;
}

void printResult(const Matrix& A,const Matrix& B, const IterMethod& method, const std::string& type)
{
	if (type == "random")
	{
		std::cout << "A matrix" << std::endl;
		A.print();
		std::cout << "B matrix" << std::endl;
		B.print();
		std::cout << std::endl;
	}
	std::cout << "result" << std::endl;
	method.getResult().print();
	std::cout << std::endl;
	std::cout << "Unknowns" << std::endl;
	method.getUnknown().print();
	std::cout << std::endl;
	std::cout << "Errors" << std::endl;
	method.getErrors().print();
	std::cout << std::endl;
	std::cout << "iterations number" << std::endl;
	std::cout << method.getItersTime();
	std::cout << std::endl;
}

double getAccuracy()
{
	double accuracy = -1;
	std::cout << "type accuracy" << std::endl;
	try
	{
		std::cin >> accuracy;
	}
	catch (std::exception& e)
	{
		return -1;
	}
	return accuracy;
}


int main()
{
	IterMethod method;
	Matrix A;
	Matrix B;
	double accuracy;
	bool result;
	

	accuracy = getAccuracy();
	if(accuracy<=0)
	{
		std::cout << "incorrect input" << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "choose input type (file, console, random)" << std::endl;
	std::string type;
	std::cin >> type;

	if (type == "random")
		result = randomInput(A,B,accuracy, method);
	else if(type == "console")
		result = consoleInput(A, B, accuracy, method);
	else if (type == "file")
		result = fileInput(A, B, accuracy, method);
	else
	{
		std::cout << "incorrect input" << std::endl;
		result = false;
	}

	if (result)
		printResult(A, B, method, type);

	system("pause");
}
