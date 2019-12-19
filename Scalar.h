#ifndef _SCALAR_H_
#define _SCALAR_H_

#include"Variable.h"

class Scalar : public Variable
{
public:
	Scalar(int val = 0);
	Scalar(const Scalar& s);
	~Scalar();

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
	int val_;
	
};

#endif // _SCALAR_H_
