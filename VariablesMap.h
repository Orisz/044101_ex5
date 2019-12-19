#ifndef _VARIABLES_MAP_H_
#define _VARIABLES_MAP_H_

#include <map>
#include <vector>
#include "MySharedPtr.h"
#include "Variable.h"

#define VALID_VAR_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

class VariablesMap
{
public:

	VariablesMap();
	~VariablesMap();
	void SetSavedName(const string& newSavedName);
	string GetTmpVariable();
	void ClearTmpVars();
	VarPtr& operator[] (const string& x);
	VarPtr& at(const string& x);
	void erase(const string& x);

private:
	map<string, VarPtr> my_variables_;
	char* saved_name_;
	vector<string> tmp_vec_;
};


#endif // _VARIABLES_MAP_H_
