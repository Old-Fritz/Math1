#pragma once
#include <fstream>
#include<iostream>
#include<string>

class Matrix
{
public:
	Matrix();
	Matrix(int height, int width);
	Matrix(int size);
	Matrix(const Matrix& matrix);
	Matrix& operator=(const Matrix& matrix);
	~Matrix();
	void createRandom(int height, int width);

	double get(int x, int y) const;
	int getWidth() const;
	int getHeight() const;
	void set(int x, int y, double value);
	void addRow(const Matrix& matrix);
	void resize(int height, int width);

	void getFromInput();
	void getFromInputSquare();
	void getFromInputColumn(int size);
	void getFromFile(std::ifstream& file);
	void getFromFileSquare(std::ifstream& file);
	void getFromFileColumn(std::ifstream& file, int size);
	void print() const;

	Matrix transponate() const;
	Matrix operator*(const Matrix& matrix) const;
	Matrix operator+(const Matrix& matrix) const;
	Matrix operator-(const Matrix& matrix) const;
	Matrix operator-() const;
private:
	double** createData(int height, int width);
	void deleteData();
	void loadFromStream(std::istream& stream, int height, int width);

private:
	double** m_data;
	int m_height;
	int m_width;
};
