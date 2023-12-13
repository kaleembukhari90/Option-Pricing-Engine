//Header file that has declarations for the Exceptions Class for Options


#ifndef OptionException_hpp
#define OptionException_hpp

#include <string>
#include <sstream>
#include <iostream>

class OptionException
{
public:
	//Constructor and Destructor for the Class
	OptionException();							//Default Constructor
	virtual ~OptionException();					//Destructor, declared virtual

	//Other Member Functions
	virtual std::string GetMessage() const = 0;	//PVMF to be overridden in the derived classes
};

class GreekException:public OptionException
{
private:
	std::string ErrorFunctionName;				//Holds the name of the function for which an exception is thrown
	GreekException();											//Default Constructor
public:
	//Constructor and Destructor of the Class
	GreekException(const GreekException& old_GreekException);	//Copy Constructor
	GreekException(std::string new_ErrorFunctionName);			//Parametric Constructor
	virtual ~GreekException();									//Destructor, declared virtual

	//Operator Overloading
	GreekException& operator = (const GreekException& source);	//Assingment Operator

	//Other Member Functions
	virtual std::string GetMessage() const;
};

#endif 
