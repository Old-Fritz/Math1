#pragma once

#include"Matrix.h"

class IterMethod
{
public:
	IterMethod();

	bool calculate(Matrix matrixA, Matrix matrixB, float precision);
	
	//getters
	const Matrix& getResult() const;
	const Matrix& getUnknown() const;
	const Matrix& getErrors() const;
	int getItersTime() const;

private:
	bool convertInitMatrix(Matrix& matrixA, Matrix& matrixB);
	bool checkPrecision(const Matrix& matrix);
	bool checkConvergence(Matrix& matrix);

private:
	int m_iterNums;
	double m_precision;

	Matrix m_unknown;
	Matrix m_errors;
	Matrix m_result;
};
