#include "Matrix.h"

Matrix::Matrix() : m_width(0), m_height(0)
{
	m_data = nullptr;
}
Matrix::Matrix(int height, int width) : m_width(width), m_height(height)
{
	m_data = createData(height, width);
}
Matrix::Matrix(int size) : Matrix(size,size)
{
}

Matrix::Matrix(const Matrix& matrix) : m_width(matrix.m_width), m_height(matrix.m_height)
{
	m_data = createData(m_height, m_width);
	for (int i = 0;i < m_height;i++)
		for (int j = 0;j < m_width;j++)
			m_data[i][j] = matrix.m_data[i][j];
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
	deleteData();

	m_width = matrix.m_width;
	m_height = matrix.m_height;

	m_data = createData(m_height, m_width);
	for (int i = 0;i < m_height;i++)
		for (int j = 0;j < m_width;j++)
			m_data[i][j] = matrix.m_data[i][j];

	return *this;
}

Matrix::~Matrix()
{
	deleteData();
}

void Matrix::createRandom(int height, int width)
{
	resize(height, width);
	for (int i = 0;i < m_height;i++)
		for (int j = 0;j < m_width;j++)
			m_data[i][j] = static_cast<double>(rand() % 10000)/100.0;
}

double Matrix::get(int x, int y) const
{
	if (x >= 0 && x < m_width&&y>=0 && y < m_height)
		return m_data[y][x];
	throw new std::exception("no such element");
}

int Matrix::getWidth() const
{
	return m_width;
}

int Matrix::getHeight() const
{
	return m_height;
}

void Matrix::set(int x, int y, double value)
{
	if (x >= 0 && x < m_width&&y>=0 && y < m_height)
		m_data[y][x] = value;
	else
		throw new std::exception("no such element");
}

void Matrix::addRow(const Matrix& matrix)
{
	if (m_width != matrix.m_width)
		return;

	double** newData = createData(m_height + 1, m_width);
	for (int i = 0;i<m_height;i++)
		for (int j = 0;j < m_width;j++)
			newData[i][j] = m_data[i][j];

	for(int i = 0;i<m_width;i++)
		newData[m_height][i] = matrix.m_data[0][i];

	deleteData();
	m_height++;
	m_data = newData;
}



void Matrix::resize(int height, int width)
{
	deleteData();
	m_height = height;
	m_width = width;
	m_data = createData(height, width);
}

void Matrix::getFromInputSquare()
{
	int size = -1;

	std::cout << "type size" << std::endl;
	std::cin >> size;
	if (size <= 0)
		throw std::invalid_argument("");

	std::cout << "type matrix" << std::endl;

	loadFromStream(std::cin, size, size);
}

void Matrix::getFromInputColumn(int size)
{
	std::cout << "type matrix" << std::endl;

	loadFromStream(std::cin, size, 1);
}

void Matrix::getFromInput()
{
	int height = -1;
	int width = -1;

	std::cout << "type height and width" << std::endl;
	std::cin >> height;
	std::cin >> width;

	if (height <= 0 || width<=0)
		throw std::invalid_argument("");

	std::cout << "type matrix" << std::endl;

	loadFromStream(std::cin, height, width);
	
}

void Matrix::getFromFile(std::ifstream& file)
{
	int height = -1;
	int width = -1;

	file >> height;
	file >> width;

	if (height <= 0 || width <= 0)
		throw std::invalid_argument("");

	loadFromStream(file, height, width);
}

void Matrix::getFromFileSquare(std::ifstream& file)
{
	int size = -1;

	file >> size;
	if (size <= 0)
		throw std::invalid_argument("");

	loadFromStream(file, size, size);

}

void Matrix::getFromFileColumn(std::ifstream& file, int size)
{
	loadFromStream(file, size, 1);
}

void Matrix::print() const
{
	for(int i = 0;i<m_height;i++)
	{
		for (int j = 0;j < m_width;j++)
			std::cout << m_data[i][j] << " ";
		std::cout << std::endl;
	}
}

Matrix Matrix::transponate() const
{
	Matrix resMatrix(m_width, m_height);

	for (int i = 0;i<m_height;i++)
		for (int j = 0;j < m_width;j++)
			resMatrix.m_data[j][i] = m_data[i][j];

	return resMatrix;
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
	if (m_width != matrix.m_height)
		return *(new Matrix());

	Matrix resMatrix(m_height, matrix.m_width);
	for(int i = 0;i<m_height; i++)
		for(int j = 0;j<matrix.m_width;j++)
		{
			double value = 0;
			for (int k = 0;k < m_width;k++)
				value += m_data[i][k] * matrix.m_data[k][j];
			resMatrix.m_data[i][j] = value;
		}

	return resMatrix;
}

Matrix Matrix::operator+(const Matrix& matrix) const
{
	if (m_height != matrix.m_height || m_width != matrix.m_width)
		return *(new Matrix());

	Matrix resMatrix(m_height, matrix.m_width);
	for (int i = 0;i<m_height; i++)
		for (int j = 0;j<matrix.m_width;j++)
			resMatrix.m_data[i][j] = m_data[i][j] + matrix.m_data[i][j];

	return resMatrix;
}

Matrix Matrix::operator-(const Matrix& matrix) const
{
	return *this + -matrix;
}

Matrix Matrix::operator-() const
{
	Matrix resMatrix(m_height, m_width);
	for (int i = 0;i<m_height; i++)
		for (int j = 0;j<m_width;j++)
			resMatrix.m_data[i][j] = -m_data[i][j];

	return resMatrix;
}

double** Matrix::createData(int height, int width)
{
	double** data = new double*[height];
	for (int i = 0;i<height;i++)
		data[i] = new double[width];

	return data;
}


void Matrix::deleteData()
{
	for (int i = 0;i < m_height;i++)
		delete[] m_data[i];
	delete[] m_data;
	m_data = nullptr;
}

void Matrix::loadFromStream(std::istream& stream, int height, int width)
{
	deleteData();

	m_height = height;
	m_width = width;
	m_data = createData(m_height, m_width);

	for (int i = 0;i<m_height;i++)
		for (int j = 0;j < m_width;j++)
		{
			std::string temp;
			stream >> temp;
			m_data[i][j] = std::stod(temp);
		}
}


