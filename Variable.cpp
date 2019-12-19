#include<iostream>
#include"Variable.h"
#include"ScriptExceptions.h"

using namespace std;


IdxVec operator+(const IdxVec& lhs, const IdxVec& rhs)
{
	if (lhs.size() != rhs.size())
		throw ScriptException("IdxVec operator+, vector sizes mismatch.");
	IdxVec res = lhs;
	int resSize = res.size();
	for (int ii = 0;ii < resSize;++ii)
		res[ii] += rhs[ii];
	return res;
}

//************************************************************************************************************
//* Function name : Variable::Variable()
//* Description   : default c'tor of variable 
//* Parameters    : None				
//* Return value  : None
//************************************************************************************************************

Variable::Variable()
{}

//************************************************************************************************************
//* Function name : Variable::Variable
//* Description   : c'tor of Variable 'type' uses to know if it is scalar or matrix
//* Parameters    : int type		
//* Return value  : None
//************************************************************************************************************

Variable::Variable(int type) :
	type_(type)
{}

//************************************************************************************************************
//* Function name : Variable::~Variable
//* Description   : destructor of Variable
//* Parameters    : None					
//* Return value  : None
//************************************************************************************************************

Variable::~Variable()
{}

//************************************************************************************************************
//* Function name : Variable::get_type
//* Description   : return the typee of variable scalar or matrix
//* Parameters    : None				
//* Return value  : int type_
//************************************************************************************************************

int Variable::get_type() const
{
	return type_;
}

//************************************************************************************************************
//* Function name : ostream& operator<<
//* Description   : the "<<" operator so we can print scalar or matrix(they inherit from variable)
//* Parameters    : stream& ro
//*					VarPtr var - VarPtr is a smart pointer to Variable	
//* Return value  : ostream& ro - we write what we want to print into the ro which is a ostream object
//************************************************************************************************************

ostream& operator<<(ostream& ro, VarPtr var)
{
	var->print(ro);
	return ro;
}