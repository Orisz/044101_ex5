#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_

using namespace std;
#include <iostream>

template <class T> 
class MySharedPtr {
public:

//************************************************************************************************************
//* Function name : MySharedPtr
//* Description   : constructor with no parameters of the class
//* Parameters    : None.
//* Return value  : None.
//************************************************************************************************************

	MySharedPtr() :
		ptr_(0), counter_(new int)
	{
		(*counter_) = 1;
	}

//************************************************************************************************************
//* Function name : MySharedPtr
//* Description   : constructor with one parameter of the class
//* Parameters    : T* ptr, pointer to a new object, that the struct will point to, so the counter will be 1
//* Return value  : None.
//************************************************************************************************************

	MySharedPtr(T* ptr) :
		ptr_(ptr), counter_(new int)
	{
		(*counter_) = 1;
	}

//************************************************************************************************************
//* Function name : MySharedPtr
//* Description   : copy constructor of the class
//* Parameters    : const MySharedPtr<T>& ptr, the object that the copy constructor should copy, the counter will be increased by 1
//* Return value  : None.
//************************************************************************************************************

	MySharedPtr(const MySharedPtr<T>& ptr)
	{
		ptr_ = ptr.ptr_;
		counter_ = ptr.counter_;
		(*counter_)++;
	}

//************************************************************************************************************
//* Function name : ~MySharedPtr
//* Description   : destructor of the class, if the counter is one we need to delete the memory we point to, but if not, we need to decrease the value that the pointer of the counter points to
//* Parameters    : None.
//* Return value  : None.
//************************************************************************************************************

	~MySharedPtr()
	{
		if ((*counter_) > 1)
		{
			(*counter_)--;
		}
		else
		{
			if (counter_) delete counter_;
			if (ptr_) delete ptr_;
		}
	}


//************************************************************************************************************
//* Function name : operator*
//* Description   : we return a reference to the object that the shared pointer points to
//* Parameters    : None.
//* Return value  : T&, a reference to the object that the pointer points
//************************************************************************************************************

	T& operator*()
	{
		return *ptr_;
	}

//************************************************************************************************************
//* Function name : operator->
//* Description   : we return a pointer to the object that the shared pointer points to, so we can get to a pointers methods and member variables
//* Parameters    : None.
//* Return value  : T*, a pointer to the object that the pointer points
//************************************************************************************************************

	T* operator->()
	{
		return ptr_;
	}

//************************************************************************************************************
//* Function name : get()
//* Description   : we return a pointer to the object that the shared pointer points to, so we can get to a pointers methods and member variables
//* Parameters    : None.
//* Return value  : T*, a pointer to the object that the pointer points
//************************************************************************************************************

	T* get()
	{
		return ptr_;
	}

//************************************************************************************************************
//* Function name : operator=
//* Description   : if we pointed only to 1 and the counter is one we need to delete the counter_ and ptr_, if not we first decrease the counter, and then change the pointer of the counter to thw new counter, and increase it
//* Parameters    : const MySharedPtr<T>& ptr, the right side of an assignment
//* Return value  : MySharedPtr<T>&, the left side of an assignment
//************************************************************************************************************

	MySharedPtr<T>& operator=(const MySharedPtr<T>& ptr)
	{
//check of self assignment		
		if (this != &ptr)
		{
//decrease the counter
			(*counter_)--;
//chech if we are pointnig to one object
			if ((*counter_) < 1)
			{
//if yes delete the memory we point				
				if (counter_) delete counter_;
				if (ptr_) delete ptr_;
			}
//change the pointer to point to another object, and the counter, and increase it
			counter_ = ptr.counter_;
			(*counter_)++;
			ptr_ = ptr.ptr_;
		}
		return *this;
	}

private:
	T* ptr_;
	int* counter_;
};

#endif // _MY_SHARED_PTR_H_
