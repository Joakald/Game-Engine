#pragma once

#include <vector>
#include <assert.h>

template<class T>
class Matrix
{
public:
	Matrix(int in_rows, int in_columns)
		:
		rows(in_rows),
		columns(in_columns)
	{
		elements = std::vector<T>(rows * columns, T{});
	}
	Matrix(int in_rows, int in_columns, T in_t)
		:
		rows(in_rows),
		columns(in_columns)
	{
		elements = std::vector<T>(rows * columns, in_t);
	}
	Matrix operator=(const Matrix& src)
	{
		assert(rows == src.rows);
		assert(columns == src.columns);
		for (int i = 0; i < rows * columns; i++)
		{
			elements[i] = src.elements[i];
		}
		return *this;
	}
	Matrix operator+(const Matrix& src)
	{
		assert(rows == src.rows);
		assert(columns == src.columns);
		for (int i = 0; i < rows * columns; i++)
		{
			elements[i] += src.elements[i];
		}
		return *this;
	}
	Matrix operator-(const Matrix& src)
	{
		assert(rows == src.rows);
		assert(columns == src.columns);
		for (int i = 0; i < rows * columns; i++)
		{
			elements[i] -= src.elements[i];
		}
		return *this;
	}
	Matrix operator*(const Matrix& src)
	{
		assert(columns == src.rows);
		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				T dot_product{};
				for (int k = 0; k < rows; k++)
				{
					dot_product += Get(j, k) * src.Get(k, i);
				}
				Set(j, i, dot_product);
			}
		}
		return *this;
	}
public:
	T Get(int row, int column)
	{
		assert(row >= 0);
		assert(row < rows);
		assert(column >= 0);
		assert(column < columns);

		return elements[row * columns + column];
	}
	void Set(int row, int column, T value)
	{
		assert(row >= 0);
		assert(row < rows);
		assert(column >= 0);
		assert(column < columns);

		elements[row * columns + column] = value;
	}
public:
	int rows;
	int columns;
	std::vector<T> elements;
};
typedef Matrix<int> MatI;
typedef Matrix<double> MatD;