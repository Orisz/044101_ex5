#include"Scalar.h"
#include"Matrix.h"
#include"ScriptExceptions.h"

using namespace std;

//************************************************************************************************************
//* Function name : Scalar::Scalar
//* Description   : c'ctor for Scalar val is the value type 0 means its scalar
//* Parameters    : int val
//* Return value  : None
//************************************************************************************************************

Scalar::Scalar(int val) :
	Variable(0), val_(val)
{}

//************************************************************************************************************
//* Function name : Scalar::Scalar
//* Description   : copy c'tor of scalar
//* Parameters    : const Scalar& s		
//* Return value  : none
//************************************************************************************************************

Scalar::Scalar(const Scalar& s) :
	Variable(0), val_(s.val_)
{}

//************************************************************************************************************
//* Function name : Scalar::~Scalar
//* Description   : Destructor of Scalar 
//* Parameters    : none			
//* Return value  : none
//************************************************************************************************************

Scalar::~Scalar()
{}

//************************************************************************************************************
//* Function name : Scalar::Copy() const
//* Description   : copy the scalar and return a smart pointer to it
//* Parameters    : none				
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::Copy() const
{
	return VarPtr(new Scalar(val_));
}

//************************************************************************************************************
//* Function name : Scalar::NumElems() const
//* Description   : returns 1 always as a scalar
//* Parameters    : none			
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::NumElems() const
{
	return VarPtr(new Scalar(1));
}

//************************************************************************************************************
//* Function name : Scalar::Size() const
//* Description   : return the dimensions of the scalar which is a 1 by 1 marix mening always [1 1]
//* Parameters    : none			
//* Return value  : VarPtr pointer to matrix
//************************************************************************************************************

VarPtr Scalar::Size() const
{
	Matrix* m = new Matrix(1, 2, 0);
	(*m)[1] = 1;
	(*m)[2] = 1;
	return m;
}

//************************************************************************************************************
//* Function name : Scalar::Size(int dim) const
//* Description   : return no matter what the input the dimension of scalar meaning 1 as scalar
//* Parameters    : int dim
//* Return value  : VarPtr s - pointer to scalar
//************************************************************************************************************

VarPtr Scalar::Size(int dim) const
{
	Scalar* s = new Scalar(1);
	return s;
}

//************************************************************************************************************
//* Function name : Scalar::Conv(VarPtr rhs) const
//* Description   : convolution
//* Parameters    : VarPtr		
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::Conv(VarPtr rhs) const
{
	if ((*(rhs->NumElems()))[1] == 0)
		return VarPtr(new Scalar(0));
	VarPtr pRet = VarPtr(new Scalar(*this));
	VarPtr rhsSize = rhs->Size();
	int rhsRows = (*rhsSize)[1], rhsCols = (*rhsSize)[2];
	IdxVec rhsCenter = { (rhsRows / 2) + 1,(rhsCols / 2) + 1 };
	(*pRet)[1] *= (*rhs)[rhsCenter];
	return pRet;
}

//************************************************************************************************************
//* Function name : Scalar::Transpose() const
//* Description   : returns the transpose of scalar meaning a copy of scalar
//* Parameters    : none			
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::Transpose() const
{
	return Copy();
}

//************************************************************************************************************
//* Function name : Scalar::operator[](int idx)
//* Description   : operator [] for scalar throw exeption if idx diffrent then 1
//* Parameters    : int idx	
//* Return value  : int& val - the value of the scalar
//************************************************************************************************************

int& Scalar::operator[](int idx)
{
	if (idx != 1)
		throw(INDEX_OUT_OF_RANGE);
	else
	{
		return val_;
	}
}

//************************************************************************************************************
//* Function name : Scalar::operator[](IdxVec v)
//* Description   : operator [] for scalar now gets vector as input throw exeption if not all the vec elements are 1
//* Parameters    : IdxVec v			
//* Return value  : int& val - the scalar value
//************************************************************************************************************

int& Scalar::operator[](IdxVec v)
{
	int size = v.size();
	for (int i = 0; i < size; i++)
	{
		if (v[i] != 1)
		{
			throw(INDEX_OUT_OF_RANGE);
		}
	}
	return val_;
}

//************************************************************************************************************
//* Function name : Scalar::operator[](int idx) const
//* Description   : Const operator [] for scalar throw exeption if idx diffrent then 1
//* Parameters    : int idx				
//* Return value  : const int& val
//************************************************************************************************************

const int& Scalar::operator[](int idx) const
{
	if (idx != 1)
		throw(INDEX_OUT_OF_RANGE);
	else
	{
		return val_;
	}
}

//************************************************************************************************************
//* Function name : Scalar::operator[](IdxVec v) const
//* Description   : Const operator [] for scalar now gets vector as input throw exeption if not all the vec elements are 1
//* Parameters    : IdxVec v		
//* Return value  : const int& val
//************************************************************************************************************

const int& Scalar::operator[](IdxVec v) const
{
	int size = v.size();
	for (int i = 0; i < size; i++)
	{
		if (v[i] != 1)
		{
			throw(INDEX_OUT_OF_RANGE);
		}
	}
	return val_;
}

//************************************************************************************************************
//* Function name : Scalar::operator+(const Variable& var) const
//* Description   : operator + for scalar with variable
//* Parameters    : const Variable& var			
//* Return value  : VarPtr - return the sum of 2 scalars by value
//************************************************************************************************************

VarPtr Scalar::operator+(const Variable& var) const
{
	return var + ((Scalar)*this);
}

//************************************************************************************************************
//* Function name : Scalar::operator+(const Scalar& scalar) const
//* Description   : operator + for scalar with scalar
//* Parameters    : const Scalar& scalar				
//* Return value  : VarPtr - sum of scalars
//************************************************************************************************************

VarPtr Scalar::operator+(const Scalar& scalar) const
{
	Scalar* s1 = new Scalar(val_ + scalar.val_);
	return s1;
}

//************************************************************************************************************
//* Function name : Scalar::operator+(const Matrix& matrix) const
//* Description   : operator + for scalar with matrix
//* Parameters    : const Matrix& matrix			
//* Return value  : VarPtr - pointing to matrix
//************************************************************************************************************

VarPtr Scalar::operator+(const Matrix& matrix) const
{
	VarPtr m1 = matrix.Copy();
	VarPtr size = m1->NumElems();
	int size_val = (*size)[1];
	for (int i = 1; i <= size_val; i++)
	{
		(*m1)[i] = (*m1)[i] + val_;
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Scalar::operator*(const Variable& var) const
//* Description   : operator * for scalar with variable
//* Parameters    : const Variable& var			
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::operator*(const Variable& var) const
{
	return var * ((Scalar)*this);//operator * of 'var' is called
}

//************************************************************************************************************
//* Function name : Scalar::operator*(const Scalar& scalar) const
//* Description   : operator * for scalar with scalar
//* Parameters    : const Scalar& scalar		
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::operator*(const Scalar& scalar) const
{
	Scalar* s = new Scalar(val_*scalar.val_);
	return s;
}

//************************************************************************************************************
//* Function name : Scalar::operator*(const Matrix& matrix) const
//* Description   : perator * for scalar with matrix
//* Parameters    : const Matrix& matrix		
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::operator*(const Matrix& matrix) const
{
	VarPtr m1 = matrix.Copy();
	VarPtr size = m1->NumElems();
	int size_val = (*size)[1];
	for (int i = 1; i <= size_val; i++)
	{
		(*m1)[i] = (*m1)[i] * val_;
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Scalar::operator<(const Variable& var) const
//* Description   : operator < of scalar with variable - calls var operator >
//* Parameters    : const Variable& var			
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::operator<(const Variable& var) const
{
	return (var > ((Scalar)*this));
}

//************************************************************************************************************
//* Function name : Scalar::operator<(const Scalar& scalar) const
//* Description   : operator < of scalar with scalar returns 1 if true 0 else
//* Parameters    : const Scalar& scalar			
//* Return value  : VarPtr to scalar of 1 or 0
//************************************************************************************************************

VarPtr Scalar::operator<(const Scalar& scalar) const
{
	if (val_ < scalar.val_)
	{
		Scalar* s = new Scalar(1);
		return s;
	}
	else
	{
		Scalar* s = new Scalar(0);
		return s;
	}
}

//************************************************************************************************************
//* Function name : Scalar::operator<(const Matrix& matrix) const
//* Description   : operator < of scalar with matrix returns matrix of 1's and 0's according to the > operator for each elem of the matrix
//* Parameters    : const Matrix& matrix				
//* Return value  : VarPtr - to a matrix of 1's and 0's
//************************************************************************************************************

VarPtr Scalar::operator<(const Matrix& matrix) const
{
	VarPtr m1 = matrix.Copy();
	VarPtr size = m1->NumElems();
	int size_val = (*size)[1];
	for (int i = 1; i <= size_val; i++)
	{
		if (val_ < (*m1)[i])
		{
			(*m1)[i] = 1;
		}
		else
			(*m1)[i] = 0;
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Scalar::operator>(const Variable& var) const
//* Description   : operator > of scalar with variable - calls var operator <
//* Parameters    : const Variable& var			
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::operator>(const Variable& var) const
{
	return (var < ((Scalar)*this));
}

//************************************************************************************************************
//* Function name : Scalar::operator>(const Scalar& scalar) const
//* Description   : operator > of scalar with scalar
//* Parameters    : const Scalar& scalar				
//* Return value  : VarPtr to scalar => 1 if true else 0
//************************************************************************************************************

VarPtr Scalar::operator>(const Scalar& scalar) const
{
	if (val_ > scalar.val_)
	{
		Scalar* s = new Scalar(1);
		return s;
	}
	else
	{
		Scalar* s = new Scalar(0);
		return s;
	}
}

//************************************************************************************************************
//* Function name : Scalar::operator>(const Matrix& matrix) const
//* Description   : operator > of scalar with matrix returns matrix of 1's and 0's according to the > operator for each elem of the matrix
//* Parameters    : const Matrix& matrix				
//* Return value  : VarPtr  - pointer to a matrix of 1's and 0's
//************************************************************************************************************

VarPtr Scalar::operator>(const Matrix& matrix) const
{
	VarPtr m1 = matrix.Copy();
	VarPtr size = m1->NumElems();
	int size_val = (*size)[1];
	for (int i = 1; i <= size_val; i++)
	{
		if (val_ > (*m1)[i])
		{
			(*m1)[i] = 1;
		}
		else
			(*m1)[i] = 0;
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Scalar::operator==(const Variable& var) const
//* Description   : operator == of scalar with variable return ptr to scalar 1 if true else scalar 0
//* Parameters    : const Variable& var					
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::operator==(const Variable& var) const
{
	return (var == ((Scalar)*this));
}

//************************************************************************************************************
//* Function name : Scalar::operator==(const Scalar& scalar) const
//* Description   : operator == of scalar with scalar return ptr to scalar 1 if true else scalar 0
//* Parameters    : const Scalar& scalar			
//* Return value  : VarPtr to scalar of 1 or 0
//************************************************************************************************************

VarPtr Scalar::operator==(const Scalar& scalar) const
{
	if (val_ == scalar.val_)
	{
		Scalar* s = new Scalar(1);
		return s;
	}
	else
	{
		Scalar* s = new Scalar(0);
		return s;
	}
}

//************************************************************************************************************
//* Function name : Scalar::operator==(const Matrix& matrix) const
//* Description   : operator == of scalar with matrix return ptr to matrix of 1's and 0's according to the == output
//* Parameters    : const Matrix& matrix		
//* Return value  : VarPtr to a matrix of 1's and 0's
//************************************************************************************************************

VarPtr Scalar::operator==(const Matrix& matrix) const
{
	VarPtr m1 = matrix.Copy();//copy the matrix
	VarPtr size = m1->NumElems();
	int size_val = (*size)[1];
	for (int i = 1; i <= size_val; i++)
	{
		if (val_ == (*m1)[i])//if equal put 1 in the matrix
		{
			(*m1)[i] = 1;
		}
		else//if not equal put 0 in the matrix
			(*m1)[i] = 0;
	}
	return m1;//return the 1's and 0's matrix
}

//************************************************************************************************************
//* Function name : Scalar::operator&&(const Variable& var) const
//* Description   : operator && of scalar with var calls operator && of var
//* Parameters    : onst Variable& var			
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::operator&&(const Variable& var) const
{
	return (var && ((Scalar)*this));
}

//************************************************************************************************************
//* Function name : Scalar::operator&&(const Scalar& scalar) const
//* Description   : operator && of scalar with scalar return 1 i true else 0
//* Parameters    : const Scalar& scalar			
//* Return value  : VarPtr - ptr to scalar of 1 or 0
//************************************************************************************************************

VarPtr Scalar::operator&&(const Scalar& scalar) const
{
	if (val_ != 0 && scalar.val_ != 0)
	{
		Scalar* s = new Scalar(1);
		return s;
	}
	else
	{
		Scalar* s = new Scalar(0);
		return s;
	}
}

//************************************************************************************************************
//* Function name : Scalar::operator&&(const Matrix& matrix) const
//* Description   : operator && of scalar with matrix
//* Parameters    : const Matrix& matrix			
//* Return value  : VarPtr - ptr to exeption "BAD_INPUT"
//************************************************************************************************************

VarPtr Scalar::operator&&(const Matrix& matrix) const
{
	throw(BAD_INPUT);
}

//************************************************************************************************************
//* Function name : calar::operator||(const Variable& var) const
//* Description   : operator || of scalar with variable calls var operator ||
//* Parameters    : const Variable& var			
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Scalar::operator||(const Variable& var) const
{
	return (var || ((Scalar)*this));
}

//************************************************************************************************************
//* Function name : Scalar::operator||(const Scalar& scalar) const
//* Description   : operator || of scalar with scalar
//* Parameters    : const Scalar& scalar				
//* Return value  : VarPtr  - ptr to sclar of 1 or 0, return 0 only if the two scalars are 0
//************************************************************************************************************

VarPtr Scalar::operator||(const Scalar& scalar) const
{
	if (val_ == 0 && scalar.val_ == 0)
	{
		Scalar* s = new Scalar(0);
		return s;
	}
	else
	{
		Scalar* s = new Scalar(1);
		return s;
	}
}

//************************************************************************************************************
//* Function name : Scalar::operator||(const Matrix& matrix) const
//* Description   : operator || of scalar with matrix
//* Parameters    : const Matrix& matrix				
//* Return value  : VarPtr - ptr to exeptio "BAD_INPUT"
//************************************************************************************************************

VarPtr Scalar::operator||(const Matrix& matrix) const
{
	throw(BAD_INPUT);
}

//************************************************************************************************************
//* Function name : Scalar::print(ostream& ro) const
//* Description   : put the val of scalar into ro with the << operator of ostream.this is helper func for operator <<
//* Parameters    : ostream& ro				
//* Return value  : void
//************************************************************************************************************

void Scalar::print(ostream& ro) const
{
	ro << val_;
	return;
}