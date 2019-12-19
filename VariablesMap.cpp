#include"VariablesMap.h"
#include"ScriptExceptions.h"
#include "Scalar.h"

//************************************************************************************************************
//* Function name : VariablesMap::VariablesMap
//* Description   : the constructor of the class, choose default value for the saved name and allocate memory for it
//* Parameters    : None.
//* Return value  : None.
//************************************************************************************************************

VariablesMap::VariablesMap()
{
	string str = "$variables";
	saved_name_ = new char[str.length() + 1];
	strcpy(saved_name_, str.c_str());
}

//************************************************************************************************************
//* Function name : ~VariablesMap::VariablesMap
//* Description   : the destructor of the class, free the saved name 
//* Parameters    : None.
//* Return value  : None.
//************************************************************************************************************

VariablesMap::~VariablesMap()
{
	delete []saved_name_;
}

//************************************************************************************************************
//* Function name : VariablesMap::SetSavedName
//* Description   : free the memory of the old saved name, allocate memory for the new and copy it
//* Parameters    : const string& newSavedName - the new saved name
//* Return value  : None.
//************************************************************************************************************

void VariablesMap::SetSavedName(const string& newSavedName)
{
	delete[]saved_name_;
	saved_name_ = new char[newSavedName.length() + 1];
	strcpy(saved_name_, newSavedName.c_str());
}

//************************************************************************************************************
//* Function name : VariablesMap::GetTmpVariable
//* Description   : return a new name for a temp variable, that he is not the saved name or a name in the map
//* Parameters    : None.
//* Return value  : string - new available name for a tmp variable
//************************************************************************************************************

string VariablesMap::GetTmpVariable()
{
	int size = -1;
	map<string, VarPtr>::const_iterator map_it = my_variables_.begin();
//run with an iterator on the map and get the size of the longest string
	while (map_it != my_variables_.end()) 
	{
		int cur_size = map_it->first.length();
		if (cur_size > size)
		{
			size = map_it->first.length();
		}
		++map_it;
	}
//check the size of the saved name, and if its longer then the size, update the size
	int size_saved = strlen(saved_name_);
	if (size < size_saved)
	{
		size = size_saved;
	}
//if the map is empty, and by accidante the saved name too set the size to 1, else we just increase the size because we want to make sure that the name we give does not exist by make it to be the new longest name
	if (size == -1)
	{
		size = 1;
	} 
	else
	{
		size++;
	}
//made the new temp name the longest and it will contain only a
	string tmp_name(size, 'a');
//we add it to the map, and also to the vector of the temp names, and return the name
	my_variables_[tmp_name];
	tmp_vec_.push_back(tmp_name);
	return tmp_name;
}

//************************************************************************************************************
//* Function name : VariablesMap::ClearTmpVars
//* Description   : clear the vector of temp variables, and all the places in the map that contain tmp variables
//* Parameters    : None.
//* Return value  : None.
//************************************************************************************************************

void VariablesMap::ClearTmpVars()
{
	int size = tmp_vec_.size() - 1;
	for (int i = size ; i >= 0; i--)
	{
		my_variables_.erase(tmp_vec_[i]);
		tmp_vec_.pop_back();
	}
	return;
}

//************************************************************************************************************
//* Function name : VariablesMap::operator[]
//* Description   : check that x is a good name of variable, and return its place in the map
//* Parameters    : const string& x - the string name of the place in the map we need to return
//* Return value  : VarPtr - the place in the map
//************************************************************************************************************

VarPtr& VariablesMap::operator[] (const string& x)
{
//check that the first char is a letter
	if (x[0] < 65 || (x[0] > 90 && x[0] < 97) || x[0] > 122)
		throw(INVALID_VAR_NAME(x));
	int i = 0;
//check that all the other chars are letters, numbers or underscore
	while (x[i])
	{
		if ((x[i] < 48 || (x[i] > 57 && x[i] < 65) || (x[i] > 90 && x[i] < 97 && x[i] != 95) || x[i] > 122))
			throw(INVALID_VAR_NAME(x));
		i++;
	}
//return the place
	return my_variables_[x];
}

//************************************************************************************************************
//* Function name : VariablesMap::at
//* Description   : return the pkace in the map, but in more safe way than, operator[], and only place that is already exists
//* Parameters    : const string& x - the string name of the place in the map we need to return
//* Return value  : VarPtr - the place in the map
//************************************************************************************************************

VarPtr& VariablesMap::at(const string& x)
{
	try
	{
		my_variables_.at(x);
	}
	catch (const std::out_of_range& e)
	{
		throw(e);
	}
	return my_variables_.at(x);
}

//************************************************************************************************************
//* Function name : VariablesMap::erase
//* Description   : eraese the place in the map of the given name
//* Parameters    : const string& x - the name of the place in the map that we need to erase
//* Return value  : None.
//************************************************************************************************************

void VariablesMap::erase(const string& x)
{
	my_variables_.erase(x);
	return;
}






