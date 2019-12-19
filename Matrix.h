#ifndef _MATRIX_H_
#define _MATRIX_H_

#include"Variable.h"
#include"Scalar.h"


class Matrix : public Variable
{
public:
	Matrix(int rows, int cols, int val);
	Matrix(int startVal, int endVal);
	Matrix(const Matrix& m);
	~Matrix();
	
	VarPtr Copy() const;
	VarPtr NumElems() const;
	VarPtr Size() const;
	VarPtr Size(int dim) const;	
	virtual VarPtr Conv(VarPtr rhs) const;
	VarPtr Transpose() const;

	int& operator[](int idx);
	int& operator[](IdxVec v);

	const int& operator[](int idx) const;
	const int& operator[](IdxVec v) const;

	VarPtr operator+(const Variable&) const;
	VarPtr operator+(const Scalar&) const;
	VarPtr operator+(const Matrix&) const;

	VarPtr operator*(const Variable&) const;
	VarPtr operator*(const Scalar&) const;
	VarPtr operator*(const Matrix&) const;

	VarPtr operator<(const Variable&) const;
	VarPtr operator<(const Scalar&) const;
	VarPtr operator<(const Matrix&) const;

	VarPtr operator>(const Variable&) const;
	VarPtr operator>(const Scalar&) const;
	VarPtr operator>(const Matrix&) const;

	VarPtr operator==(const Variable&) const;
	VarPtr operator==(const Scalar&) const;
	VarPtr operator==(const Matrix&) const;

	VarPtr operator&&(const Variable&) const;
	VarPtr operator&&(const Scalar&) const;
	VarPtr operator&&(const Matrix&) const;

	VarPtr operator||(const Variable&) const;
	VarPtr operator||(const Scalar&) const;
	VarPtr operator||(const Matrix&) const;

	void print(ostream& ro) const;


private:
	int rows_;
	int cols_;
	int** mat_;	
};




#endif // _MATRIX_H_
