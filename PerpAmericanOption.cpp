//Contains the Definitions for the functionality of Perpetual American Options
//Each Function/Member declared in the Header file is implemented in the source File

#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include "Option.hpp"
#include "PerpAmericanOption.hpp"
#include "OptionException.hpp"

//Default Constructor
PerpAmericanOption::PerpAmericanOption() : Option()
{
}

//Copy Constructor
PerpAmericanOption::PerpAmericanOption(const PerpAmericanOption& old_PerpAmericanOption) :Option(old_PerpAmericanOption)
{
}

//Parametric Constructor
PerpAmericanOption::PerpAmericanOption(double new_K, double new_sig, double new_r, double new_S, double new_b, std::string new_option_type):Option(new_K, new_sig, new_r, new_S, new_b, new_option_type)
{
}

//Destructor
PerpAmericanOption::~PerpAmericanOption()
{
}

//Assignment Operator
PerpAmericanOption& PerpAmericanOption::operator=(const PerpAmericanOption& source)
{
	//check for self-assignment, if not self-assigned then
	if (this != &source)
	{
		//Call the Base Class Assignment Operator
		Option::operator=(source);
	}
	//return the object
	return *this;
}

//Function to Calculte Call Option Price
double PerpAmericanOption::CallPrice() const
{
	//Calculating parameter y1
	double sqrt_part = sqrt(pow(((b() / (sig() * sig())) - 0.5), 2) + (2 * r() / (sig() * sig())));
	double y1 = 0.5 - (b()/pow(sig(), 2)) + sqrt_part;

	if (1.0 == y1)
	{
		return S();
	}
	
	//Calculate and Return Call Price
	return (K() / (y1 - 1)) * pow((((y1 - 1) / y1) * (S() / K())), y1);
}

//Function Calculate Call Option Price given Stock Price as Argument
double PerpAmericanOption::CallPrice(double S_val) const
{
	//Calculatng the parameter y1
	double sqrt_part = sqrt(pow(((b() / (sig() * sig())) - 0.5), 2) + (2 * r() / (sig() * sig())));
	double y1 = 0.5 - (b() / pow(sig(), 2)) + sqrt_part;

	if (1.0 == y1)
	{
		return S_val;
	}

	//Calculate and Return Call Price
	return (K() / (y1 - 1)) * pow((((y1 - 1) / y1) * (S_val / K())), y1);
}

//Function to Calculate Put Option Price
double PerpAmericanOption::PutPrice() const
{
	//Calculating parameter y2
	double sqrt_part = sqrt(pow(((b() / (sig() * sig())) - 0.5), 2) + (2 * r() / (sig() * sig())));
	double y2 = 0.5 - (b()/pow(sig(), 2)) - sqrt_part;

	if (0.0 == y2)
	{
		return S();
	}

	//Calculate and return Put Price
	return (K() / (1 - y2)) * pow((((y2 - 1) / y2) * (S() / K())), y2);
}

//Function to Calculate Put Option Price given Stock Price as Argument
double PerpAmericanOption::PutPrice(double S_val) const
{
	double sqrt_part = sqrt(pow(((b() / (sig() * sig())) - 0.5), 2) + (2 * r() / (sig() * sig())));
	double y2 = 0.5 - (b() / pow(sig(), 2)) - sqrt_part;

	if (0.0 == y2)
	{
		return S_val;
	}

	//Calculate and return Put Price
	return (K() / (1 - y2)) * pow((((y2 - 1) / y2) * (S_val / K())), y2);
}

//Toggle function that changes the type of the option
void PerpAmericanOption::ToggleOption()
{
	//If the option type is Call, then
	if (option_type == "Call")
	{
		//Set the option_type to Put
		//i.e. Toggle the option type
		option_type = "Put";
	}
	//If the option type is not Call, then
	else
	{
		//Set the option_type to Call
		//i.e. Toggle the option type
		option_type = "Call";
	}
}

//Getter Function to Get Option Type
std::string PerpAmericanOption::OptionType() const
{
	//return Option Type (Call or Put) of the Option
	return option_type;
}

//Function that throws an exception when Exact CallDelta method is called on
//a Perpetual American Option
double PerpAmericanOption::CallDelta()const
{
	//throw an exception when CallDelta() function is called on
	//an option for which no exact formula for Call Option Delta exists
	throw GreekException("CallDelta");
}

//Function that throws an exception when Exact PutDelta method is called on
//a Perpetual American Option
double PerpAmericanOption::PutDelta()const
{
	//throw an exception when PutDelta() function is called on
	//an option for which no exact formula for Put Option Delta exists
	throw GreekException("PutDelta");
}

//Function that throws an exception when Exact Delta method is called on
//a Perpetual American Option
double PerpAmericanOption::Delta() const
{
	//throw an exception when Delta() function is called on
	//an option for which no exact formula for Delta exists
	throw GreekException("Delta");
}

//Function that throws an exception when Exact Gamma method is called on
//a Perpetual American Option
double PerpAmericanOption::Gamma() const
{
	//throw an exception when Gamma() function is called on
	//an option for which no exact formula for Gamma exists
	throw GreekException("Gamma");
}

//Calculate approximate Delta
//Using Divided Difference Method
double PerpAmericanOption::ApproximateDelta(double S, double h) const
{
	//Calculate and return the value of Approximate Delta
	throw GreekException("Approximate Delta");
}

//Calculate approximate Gamma
//Using Divided Difference Method
double PerpAmericanOption::ApproximateGamma(double S, double h) const
{
	//Calculate and return the value of Approximate Gamma
	throw GreekException("Approximate Gamma");
}