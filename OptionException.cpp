//Source File that contains the definitions for the Abstract Base Class of OptionException
//and the definitions for derived class/es
//	1.GreekException

#include "OptionException.hpp"
#include <string>
#include <sstream>
#include <iostream>

//Definitions for Abstract Base Class: OptionException
//Default Constructor
OptionException::OptionException()
{
}

//Destructor
OptionException::~OptionException()
{
}

//Definitions for Derived Class: GreekException
//Parametric Constructor
GreekException::GreekException(std::string errorFunctioName):ErrorFunctionName(errorFunctioName),OptionException()
{
}

//Copy Constructor
GreekException::GreekException(const GreekException& old_GreekException) :ErrorFunctionName(old_GreekException.ErrorFunctionName), OptionException()
{
}

//Destructor
GreekException::~GreekException()
{
}

//Assignment Operator
GreekException& GreekException::operator = (const GreekException& source)
{
	//check for self-assignment, if not self-assigned
	if (this != &source)
	{
		//Assign the value of ErrorFunctionName from source to ErrorFunctionName of "this" object
		ErrorFunctionName = source.ErrorFunctionName;
	}
	//return "this" object
	return *this;
}

//Function that outputs an error message
std::string GreekException::GetMessage() const
{
	//Creating a string object object that holds the error message
	std::stringstream error_message;
	error_message << "Error! Function for Greek " << ErrorFunctionName << " is not implemented for this Option" << std::endl;
	//return the string object
	return error_message.str();
}