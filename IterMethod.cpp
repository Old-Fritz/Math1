#include "IterMethtod.h"
#include <cmath>

IterMethod::IterMethod()
{
	m_iterNums = 0;
}

bool IterMethod::calculate(Matrix matrixA, Matrix matrixB, float precision)
{
	// check correct size
	if (matrixA.getWidth() != matrixA.getHeight() || matrixB.getWidth() != 1 || matrixB.getHeight() != matrixA.getHeight())
		return false;

	// prepare start values
	m_iterNums = 0;
	m_precision = precision;
	m_errors.resize(0, matrixA.getWidth());
	m_unknown.resize(0, matrixA.getWidth());

	// transform matrix for expressing X
	if (!convertInitMatrix(matrixA, matrixB))
		return false;

	// check convergence first
	////if (!checkConvergence(matrixA))
	//	return false;

	m_result = matrixB;
	Matrix oldResult;

	// iterations
	do
	{
		oldResult = m_result;
		m_result = matrixB + matrixA * oldResult;
		m_unknown.addRow(m_result.transponate());
		m_errors.addRow((m_result - oldResult).transponate());
		m_iterNums++;
	}
	while(!checkPrecision(m_result - oldResult));

	return true;
}

bool IterMethod::convertInitMatrix(Matrix& matrixA, Matrix& matrixB)
{
	for (int i = 0; i < matrixA.getHeight();i++)
	{
		if (matrixA.get(i, i) == 0)
			return false;
		matrixB.set(0, i, matrixB.get(0, i) / matrixA.get(i, i));
		for (int j = 0;j<matrixA.getWidth();j++)
		{
			if (i != j)
				matrixA.set(j, i, -matrixA.get(j, i) / matrixA.get(i, i));
		}
		matrixA.set(i, i, 0);
	}

	return true;
}

bool IterMethod::checkPrecision(const Matrix& matrix)
{
	for (int i = 0;i < matrix.getHeight();i++)
		if (abs(matrix.get(0, i)) > m_precision)
			return false;

	return true;
}

bool IterMethod::checkConvergence(Matrix& matrix)
{
	// check first condition
	bool b = true;
	for(int i =0;i<matrix.getWidth();i++)
	{
		double sum = 0;
		for (int j = 0;j < matrix.getWidth();j++)
			sum += abs(matrix.get(j,i));
		if (sum >= 1)
		{
			b = false;
			break;
		}
	}
	if (b)
		return true;

	// chek second condition
	for (int i = 0;i<matrix.getWidth();i++)
	{
		double sum = 0;
		for (int j = 0;j < matrix.getWidth();j++)
			sum += abs(matrix.get(i, j));
		if (sum >= 1)
			return false;
	}

	return true;
}


// getters
const Matrix& IterMethod::getResult() const
{
	return m_result;
}

const Matrix& IterMethod::getUnknown()  const
{
	return m_unknown;
}

const Matrix& IterMethod::getErrors()  const
{
	return m_errors;
}

int IterMethod::getItersTime()  const
{
	return m_iterNums;
}

