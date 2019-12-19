#include"Scalar.h"
#include"Matrix.h"
#include"ScriptExceptions.h"

//************************************************************************************************************
//* Function name : Matrix::Matrix(int rows, int cols, int val)
//* Description   : c'tor of matrix 
//* Parameters    : int rows
//*					int cols
//*					int val
//* Return value  : none
//************************************************************************************************************

Matrix::Matrix(int rows, int cols, int val) :
	Variable(1), rows_(rows), cols_(cols)
{
	//if (rows_ == 0 && cols_ != 0)
	//{
	//	rows_ = cols;
	//	cols_ = rows;
	//}
	if ((rows_ != 0 && cols_ != 0) || (rows_ != 0 && cols_ == 0))
	{
		mat_ = new int*[rows];
		if (cols_ != 0) 
		{
			for (int i = 0; i < rows; i++) {
				mat_[i] = new int[cols];
			}
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					mat_[i][j] = val;
				}
			}
		}
	}
}

//************************************************************************************************************
//* Function name : Matrix::Matrix(int startVal, int endVal)
//* Description   : c'tor of matrix incrementing matrix of 1 by endval-startval + 1
//* Parameters    : int startVal
//*					int endVal					
//* Return value  : none
//************************************************************************************************************

Matrix::Matrix(int startVal, int endVal) :
	Variable(1), rows_(1), cols_(endVal-startVal+1)
{
	if (cols_ < 0)
		cols_ = 0;
	int val = startVal;
	mat_ = new int*[rows_];
	if (cols_ != 0)
	{
		mat_[0] = new int[cols_];
		for (int i = 0; i < cols_; i++, val++)
		{
			mat_[0][i] = val;
		}
	}
}

//************************************************************************************************************
//* Function name : Matrix::Matrix(const Matrix& m)
//* Description   : copy c'tor of matrix
//* Parameters    : const Matrix& m		
//* Return value  : none
//************************************************************************************************************

Matrix::Matrix(const Matrix& m) :
	Variable(1), rows_(m.rows_), cols_(m.cols_)
{
	mat_ = new int*[rows_];
	for (int i = 0; i < rows_; i++) {
		mat_[i] = new int[cols_];
	}
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			mat_[i][j] = m.mat_[i][j];
		}
	}
}

//************************************************************************************************************
//* Function name : Matrix::~Matrix()
//* Description   : destructor of matrix
//* Parameters    : none				
//* Return value  : none
//************************************************************************************************************

Matrix::~Matrix()
{
	if (rows_ == 1 && cols_ == 0)
	{
		delete[] mat_;
	}
	else if (rows_ != 0 && cols_ != 0)
	{
		for (int i = 0; i < rows_; i++) {
			delete[] mat_[i];
		}
		delete[] mat_;
	}
}

//************************************************************************************************************
//* Function name : Matrix::Copy() const
//* Description   : copy the matrix
//* Parameters    : none				
//* Return value  : VarPtr to the copy of the matrix
//************************************************************************************************************

VarPtr Matrix::Copy() const
{
	Matrix* mat_copy = new Matrix(rows_, cols_, 0);
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			mat_copy->mat_[i][j] = mat_[i][j];
		}
	}
	return mat_copy;
}

//************************************************************************************************************
//* Function name : Matrix::NumElems() const
//* Description   : retirn the number of elemnts in the matrix as a scalar
//* Parameters    : none				
//* Return value  : VarPtr to sclar
//************************************************************************************************************

VarPtr Matrix::NumElems() const
{
	Scalar* s = new Scalar(rows_*cols_);
	return s;
}

//************************************************************************************************************
//* Function name : Matrix::Size() const
//* Description   : return a matrix of 1 by two where the first elem is #rows and the secons is #cols
//* Parameters    : none				
//* Return value  : VarPtr to matrix of 1 by 2
//************************************************************************************************************

VarPtr Matrix::Size() const
{
	Matrix* m = new Matrix(1, 2, 0);
	(*m)[1] = rows_;
	(*m)[2] = cols_;
	return m;
}

//************************************************************************************************************
//* Function name : Matrix::Size(int dim) const
//* Description   : if input is 1 return nu, of rows , if input is 2 return num of cols else throw exeption
//* Parameters    : int dim				
//* Return value  : VarPtr - ptr to scalar
//************************************************************************************************************

VarPtr Matrix::Size(int dim) const
{
	if (dim > 2 || dim < 1)//invalid input
		throw(BAD_INPUT);
	else if (dim == 1)
	{
		Scalar* s = new Scalar(rows_);
		return s;
	}
	else if (dim == 2)
	{
		Scalar* s = new Scalar(cols_);
		return s;
	}
	throw(BAD_INPUT);
}

//************************************************************************************************************
//* Function name : Matrix::Conv(VarPtr rhs) const
//* Description   : Convolution this is a given function
//* Parameters    : VarPtr rhs			
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Matrix::Conv(VarPtr rhs) const
{
	if ((*NumElems())[1] == 0)
		return VarPtr(new Matrix(*this));
	if ((*(rhs->NumElems()))[1] == 0)
		return VarPtr(new Matrix(rows_, cols_, 0));

	VarPtr pRet = VarPtr(new Matrix(rows_, cols_, 0));
	VarPtr rhsSize = rhs->Size();
	int rhsRows = (*rhsSize)[1], rhsCols = (*rhsSize)[2];
	IdxVec rhsCenter = { (rhsRows / 2) + 1,(rhsCols / 2) + 1 };
	int maxRowShift = rhsRows - rhsCenter[0];
	int minRowShift = 1 - rhsCenter[0];
	int maxColShift = rhsCols - rhsCenter[1];
	int minColShift = 1 - rhsCenter[1];
	for (int resRow = 1; resRow <= rows_; ++resRow)
		for (int resCol = 1; resCol <= cols_; ++resCol)
		{
			IdxVec resIdx = { resRow,resCol };
			for (int rowShift = minRowShift; rowShift <= maxRowShift; ++rowShift)
				for (int colShift = minColShift; colShift <= maxColShift; ++colShift)
				{
					try
					{
						(*pRet)[resIdx] += ((*this)[resIdx + IdxVec{ -rowShift,-colShift }] * (*rhs)[rhsCenter + IdxVec{rowShift,colShift}]);
					}
					catch (...)
					{
						// convolution is zero padded (no action required)
					}
				}
		}
	return pRet;
}

//************************************************************************************************************
//* Function name : Matrix::Transpose() const
//* Description   : do a transpose to the matrix by defenition
//* Parameters    : none				
//* Return value  : VarPtr - ptr to a copy of a matrix transpose
//************************************************************************************************************

VarPtr Matrix::Transpose() const
{
	Matrix* m = new Matrix(cols_, rows_, 0);
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			m->mat_[j][i] = mat_[i][j];
		}
	}
	return m;
}

//************************************************************************************************************
//* Function name : Matrix::operator[](int idx)
//* Description   : operator [] for matrix so we can adress it and put values inside
//* Parameters    : int idx		
//* Return value  : int& refrence to the place in the matrix
//************************************************************************************************************

int& Matrix::operator[](int idx)
{
	int counter = 0;
	if (idx < 1 || idx >(cols_*rows_))//check if index is valid input
	{
		throw(INDEX_OUT_OF_RANGE);//if not throw "out of range input"
	}
	else
	{
		for (int i = 0; i < cols_; i++)
		{
			for (int j = 0; j < rows_; j++)
			{
				counter++;
				if (counter == idx)
				{
					return mat_[j][i];
				}
			}
		}
	}
	throw(INDEX_OUT_OF_RANGE);
}

//************************************************************************************************************
//* Function name : Matrix::operator[](IdxVec v)
//* Description   : operator [] for matrix so we can adress it and put values inside
//* Parameters    : IdxVec v				
//* Return value  : int& refrence to the place in the matrix
//************************************************************************************************************

int& Matrix::operator[](IdxVec v)
{
	if (v.size() != 2 || v[0] > rows_ || v[0] < 1 || v[1] > cols_ || v[1] < 1)
	{
		throw(INDEX_OUT_OF_RANGE);
	}
	else
	{
		return mat_[v[0]-1][v[1]-1];
	}
}

//************************************************************************************************************
//* Function name : int& Matrix::operator[](int idx) const
//* Description   : operator [] for matrix so we READ values from the matrix
//* Parameters    : int idx			
//* Return value  : const int& - value in this index
//************************************************************************************************************

const int& Matrix::operator[](int idx) const
{
	int counter = 0;
	if (idx < 1 || idx >(cols_*rows_))//check if idx is valid
	{
		throw(INDEX_OUT_OF_RANGE);//if not throw "out of range input"
	}
	else
	{
		for (int i = 0; i < cols_; i++)
		{
			for (int j = 0; j < rows_; j++)
			{
				counter++;
				if (counter == idx)
				{
					return mat_[j][i];
				}
			}
		}
	}
	throw(INDEX_OUT_OF_RANGE);
}

//************************************************************************************************************
//* Function name : Matrix::operator[](IdxVec v) const
//* Description   : operator [] for matrix so we READ values from the matrix
//* Parameters    : IdxVec v			
//* Return value  : const int&
//************************************************************************************************************

const int& Matrix::operator[](IdxVec v) const
{
	if (v.size() != 2 || v[0] > rows_ || v[0] < 1 || v[1] > cols_ || v[1] < 1)
	{
		throw(INDEX_OUT_OF_RANGE);
	}
	else
	{
		return mat_[v[0]-1][v[1]-1];
	}
}

//************************************************************************************************************
//* Function name : Matrix::operator+(const Variable& var) const
//* Description   : operator + for matrix and variable
//* Parameters    : const Variable& var				
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Matrix::operator+(const Variable& var) const
{
	return var + ((Matrix)*this);
}

//************************************************************************************************************
//* Function name : Matrix::operator+(const Scalar& s) const
//* Description   : operator + for matrix and scalar
//* Parameters    : const Scalar& s				
//* Return value  : VarPtr - ptr to matrix
//************************************************************************************************************

VarPtr Matrix::operator+(const Scalar& s) const
{
	Matrix* m1 = new Matrix(rows_, cols_,0);
	int val = s[1];
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			m1->mat_[i][j] = mat_[i][j] + val;
		}
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Matrix::operator+(const Matrix& matrix) const
//* Description   : operator + for matrix and matrix
//* Parameters    : const Matrix& matrix			
//* Return value  : VarPtr - ptr to matrix
//************************************************************************************************************

VarPtr Matrix::operator+(const Matrix& matrix) const
{
	if (rows_ != matrix.rows_ || cols_ != matrix.cols_)//check if matrix from same dimension
	{
		throw(BAD_MAT_DIMS("+"));//if not throw us out
	}
	Matrix* m1 = new Matrix(rows_, cols_, 0);
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			m1->mat_[i][j] = mat_[i][j] + matrix.mat_[i][j];
		}
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Matrix::operator*(const Variable& var) const
//* Description   : operator * for matrix and variable
//* Parameters    : const Variable& var				
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Matrix::operator*(const Variable& var) const
{
	if (var.get_type() == 0)//var is scalar
		return var * ((Matrix)*this);//calls var operator *
	else
		return ((Matrix)*this) * (dynamic_cast<Matrix&>(const_cast<Variable&>(var)));//cast var into matrix

}

//************************************************************************************************************
//* Function name : Matrix::operator*(const Scalar& s) const
//* Description   : operator * for matrix and scalar
//* Parameters    : const Scalar& s				
//* Return value  : VarPtr - ptr to matrix
//************************************************************************************************************

VarPtr Matrix::operator*(const Scalar& s) const
{
	Matrix* m1 = new Matrix(rows_, cols_, 0);
	int val = s[1];
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			m1->mat_[i][j] = mat_[i][j] * val;//multiple elem by elem of the matrix with scalar
		}
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Matrix::operator*(const Matrix& matrix) const
//* Description   : operator * for matrix and matrix
//* Parameters    : const Matrix& matrix			
//* Return value  : VarPtr - ptr to matrix
//************************************************************************************************************

VarPtr Matrix::operator*(const Matrix& matrix) const
{
	if (cols_ != matrix.rows_)//check if martix multiple is defined with those matricies
		throw(BAD_MAT_PROD);
	Matrix* m = new Matrix(rows_, matrix.cols_, 0);
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < matrix.cols_; j++)
		{
			for (int k = 0; k < cols_; k++)
			{
				(*m).mat_[i][j] = (*m).mat_[i][j] + (mat_[i][k] * matrix.mat_[k][j]);//sum of "aik*bkj" matrix multipication by defenition
			}
		}
	}
	return m;
}

//************************************************************************************************************
//* Function name : Matrix::operator<(const Variable& var) const
//* Description   : operator < for matrix and variable - calls operator > of var
//* Parameters    : const Variable& var				
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Matrix::operator<(const Variable& var) const
{
	return var > ((Matrix)*this);
}

//************************************************************************************************************
//* Function name : Matrix::operator<(const Scalar& s) const
//* Description   : operator < for matrix and scalar
//* Parameters    : const Scalar& s				
//* Return value  : VarPtr - ptr to matrix of 1's and 0's
//************************************************************************************************************

VarPtr Matrix::operator<(const Scalar& s) const
{
	Matrix* m1 = new Matrix(rows_, cols_, 0);
	int val = s[1];
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			if (mat_[i][j] < val)//if true put 1
			{
				(*m1).mat_[i][j] = 1;
			}
			else//if not true put 0
				(*m1).mat_[i][j] = 0;
		}
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Matrix::operator<(const Matrix& matrix) const
//* Description   : operator < for matrix and matrix
//* Parameters    : const Matrix& matrix			
//* Return value  : VarPtr - ptr to matrix
//************************************************************************************************************

VarPtr Matrix::operator<(const Matrix& matrix) const
{
	if (rows_ != matrix.rows_ || cols_ != matrix.cols_)//check if matricies dimensions agree
	{
		throw(BAD_MAT_DIMS("> / <"));//if not throw us out
	}
	Matrix* m1 = new Matrix(rows_, cols_, 0);
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			if (mat_[i][j] < matrix.mat_[i][j])
				(*m1).mat_[i][j] = 1;
			else
				(*m1).mat_[i][j] = 0;
		}
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Matrix::operator>(const Variable& var) const
//* Description   : operator > for matrix and variable - calls operator < of var
//* Parameters    : const Variable& var				
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Matrix::operator>(const Variable& var) const
{
	return var < ((Matrix)*this);
}

//************************************************************************************************************
//* Function name : Matrix::operator>(const Scalar& s) const
//* Description   : operator > for matrix and scalar
//* Parameters    : const Scalar& s				
//* Return value  : VarPtr - ptr to matrix of 1's and 0's
//************************************************************************************************************

VarPtr Matrix::operator>(const Scalar& s) const
{
	Matrix* m1 = new Matrix(rows_, cols_, 0);
	int val = s[1];
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			if (mat_[i][j] > val)//if true put 1
			{
				(*m1).mat_[i][j] = 1;
			}
			else//if not put 0
				(*m1).mat_[i][j] = 0;
		}
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Matrix::operator>(const Matrix& matrix) const
//* Description   : operator > for matrix and matrix
//* Parameters    : const Matrix& matrix			
//* Return value  : VarPtr - ptr to matrix
//************************************************************************************************************

VarPtr Matrix::operator>(const Matrix& matrix) const
{
	if (rows_ != matrix.rows_ || cols_ != matrix.cols_)//check if matrix dims agree
	{
		throw(BAD_MAT_DIMS("> / <"));//if not throw us out
	}
	Matrix* m1 = new Matrix(rows_, cols_, 0);
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			if (mat_[i][j] > matrix.mat_[i][j])
				(*m1).mat_[i][j] = 1;
			else
				(*m1).mat_[i][j] = 0;
		}
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Matrix::operator==(const Variable& var) const
//* Description   : operator == for matrix and variable - calls operator == of var
//* Parameters    : const Variable& var				
//* Return value  : VarPtr
//************************************************************************************************************

VarPtr Matrix::operator==(const Variable& var) const
{
	return var == ((Matrix)*this);
}

//************************************************************************************************************
//* Function name : Matrix::operator==(const Scalar& s) const
//* Description   : operator == for matrix and scalar
//* Parameters    : const Scalar& s				
//* Return value  : VarPtr - ptr to matrix of 1's and 0's
//************************************************************************************************************

VarPtr Matrix::operator==(const Scalar& s) const
{
	Matrix* m1 = new Matrix(rows_, cols_, 0);//result matrix
	int val = s[1];
	for (int i = 0; i < rows_; i++)//loop over mat rows
	{
		for (int j = 0; j < cols_; j++)//loop over mat cols
		{
			if (mat_[i][j] == val)//if mat elem equals the scalar put 1
			{
				(*m1).mat_[i][j] = 1;
			}
			else//else put 0
				(*m1).mat_[i][j] = 0;
		}
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Matrix::operator==(const Matrix& matrix) const
//* Description   : operator == for matrix and matrix
//* Parameters    : const Matrix& matrix			
//* Return value  : VarPtr - ptr to matrix
//************************************************************************************************************

VarPtr Matrix::operator==(const Matrix& matrix) const
{
	if (rows_ != matrix.rows_ || cols_ != matrix.cols_)//check if matricies dims agree
	{
		throw(BAD_MAT_DIMS("=="));//if not throw us out
	}
	Matrix* m1 = new Matrix(rows_, cols_, 0);//create result matrix
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			if (mat_[i][j] == matrix.mat_[i][j])
				(*m1).mat_[i][j] = 1;
			else
				(*m1).mat_[i][j] = 0;
		}
	}
	return m1;
}

//************************************************************************************************************
//* Function name : Matrix::operator&&(const Variable& var) const
//* Description   : operator && for matrix with var
//* Parameters    : const Variable& var			
//* Return value  : VarPtr - ptr to exeption "BAD_INPUT"
//************************************************************************************************************

VarPtr Matrix::operator&&(const Variable& var) const
{
	throw(BAD_INPUT);
}

//************************************************************************************************************
//* Function name : Matrix::operator&&(const Scalar& s) const
//* Description   : operator && for matrix with scalar
//* Parameters    : const Scalar& s			
//* Return value  : VarPtr - ptr to exeption "BAD_INPUT"
//************************************************************************************************************

VarPtr Matrix::operator&&(const Scalar& s) const
{
	throw(BAD_INPUT);
}

//************************************************************************************************************
//* Function name : Matrix::operator&&(const Matrix& matrix) const
//* Description   : operator && for matrix with matrix
//* Parameters    : const Matrix& matrix			
//* Return value  : VarPtr - ptr to exeption "BAD_INPUT"
//************************************************************************************************************

VarPtr Matrix::operator&&(const Matrix& matrix) const
{
	throw(BAD_INPUT);
}

//************************************************************************************************************
//* Function name : Matrix::operator||(const Variable& var) const
//* Description   : operator || for matrix with var
//* Parameters    : const Variable& var			
//* Return value  : VarPtr - ptr to exeption "BAD_INPUT"
//************************************************************************************************************

VarPtr Matrix::operator||(const Variable& var) const
{
	throw(BAD_INPUT);
}

//************************************************************************************************************
//* Function name : Matrix::operator||(const Scalar& s) const
//* Description   : operator || for matrix with scalar
//* Parameters    : const Scalar& s			
//* Return value  : VarPtr - ptr to exeption "BAD_INPUT"
//************************************************************************************************************

VarPtr Matrix::operator||(const Scalar& s) const
{
	throw(BAD_INPUT);
}

//************************************************************************************************************
//* Function name : Matrix::operator||(const Matrix& matrix) const
//* Description   : operator || for matrix with matrix
//* Parameters    : const Matrix& matrix			
//* Return value  : VarPtr - ptr to exeption "BAD_INPUT"
//************************************************************************************************************

VarPtr Matrix::operator||(const Matrix& matrix) const
{
	throw(BAD_INPUT);
}

//************************************************************************************************************
//* Function name : Matrix::print(ostream& ro) const
//* Description   : helper func to the << operator so we can use it on matrix
//* Parameters    : ostream& ro				
//* Return value  : void
//************************************************************************************************************

void Matrix::print(ostream& ro) const
{
	int stop_line = rows_ - 1;
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			ro << mat_[i][j] << '\t';//as instructed we should print matrix elemnts with "tab" spacing 
		}
		if (i != stop_line)//dont go a line down after finishing the last row
			ro << '\n';
	}
	return;
}
