//Source file for Derived Class European Option
//Contains the definitions for members and member function declared in the header file
//for Derived Class European Option

#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>
#include "Option.hpp"
#include "EuropeanOption.hpp"
#include "GlobalFunction.hpp"


//Default Constructor
EuropeanOption::EuropeanOption() :m_T(0.25), Option()
{
}

//Copy Constructor
EuropeanOption::EuropeanOption(const EuropeanOption& old_euro_option) :m_T(old_euro_option.m_T),Option(old_euro_option)
{
}


//Parametric Constructor
EuropeanOption::EuropeanOption(double new_T, double new_K, double new_sig, double new_r, double new_S, double new_b, std::string new_option_type) :m_T(new_T),Option(new_K, new_sig, new_r, new_S, new_b, new_option_type)
{
}


//Destructor
EuropeanOption::~EuropeanOption()
{
}

//Assignment Operator
EuropeanOption& EuropeanOption::operator=(const EuropeanOption& source)
{
	//check for self-assignment, if not self-assigned then
	if (this != &source)
	{
		//Call the Base Class Assignment Operator
		Option::operator=(source);

		//Assign source's T to this object's T
		m_T = source.m_T;
	}
	//return the object
	return *this;
}

//Function to Calculate Call Option Price
double EuropeanOption::CallPrice() const
{
	//Declaring and initializing the variables d1
	double d1 = (log(S() / K()) + (b() + pow(sig(), 2) * 0.5) * T()) / (sig() * sqrt(T()));

	//Declaring and initializing the variables d2
	double d2 = d1 - sig() * sqrt(T());

	//Calculate and return Call Option Price
	return (S() * exp((b() - r()) * T()) * N(d1) - K() * exp(-r() * T()) * N(d2));
}

//Function to Calculate Call Option Price Taking Stock Price as Argument
double EuropeanOption::CallPrice(double S_val) const
{
	//Declaring and initializing the variables d1
	double d1 = (log(S_val / K()) + (b() + pow(sig(), 2) * 0.5) * T()) / (sig() * sqrt(T()));

	//Declaring and initializing the variables d2
	double d2 = d1 - sig() * sqrt(T());

	//Calculate and return Call Option Price
	return (S_val * exp((b() - r()) * T()) * N(d1) - K() * exp(-r() * T()) * N(d2));
}
//Function to Calculate Put Option Price
double EuropeanOption::PutPrice() const
{
	//Declaring and initializing the variables d1
	double d1 = (log(S() / K()) + (b() + pow(sig(), 2) * 0.5) * T()) / (sig() * sqrt(T()));

	//Declaring and initializing the variables d2
	double d2 = d1 - sig() * sqrt(T());

	//Calculate and return Put Option Price
	return (K() * exp(-r() * T()) * N(-d2) - S() * exp((b() - r()) * T()) * N(-d1));
}

//Function to Calculate Put Option Price Taking Stock price as Argument
double EuropeanOption::PutPrice(double S_val) const
{
	//Declaring and initializing the variables d1
	double d1 = (log(S_val / K()) + (b() + pow(sig(), 2) * 0.5) * T()) / (sig() * sqrt(T()));

	//Declaring and initializing the variables d2
	double d2 = d1 - sig() * sqrt(T());

	//Calculate and return Put Option Price
	return (K() * exp(-r() * T()) * N(-d2) - S_val * exp((b() - r()) * T()) * N(-d1));
}

//Function to Calculate Option Price using Put-Call Parity
double EuropeanOption::PutCallParity() const
{
	//If option type is Call, then
	if (option_type == "Call")
	{
		//Calculate and return the price of a Put Option
		return (OptionPrice() + K() * exp(-r() * T()) - S());
	}
	//if option type is not Call, then
	else
	{
		//Calculate and return the price of a Call Option
		return (OptionPrice() + S() - K() * exp(-r() * T()));
	}
}

//Function that checks if Put Call Parity is satisfied or not
bool EuropeanOption::PutCallParityCheck() const
{
	//if the absoluate difference of the LHS and RHS of the Put Call Parity equation
	//C + K*e(-rT) = P + S
	//is less 1e-10 (tolerance level), then
	//return True else False
	return abs(CallPrice() + K() * exp(-r() * T()) - PutPrice() - S()) < 1e-10;
}

//Toggle function that changes the type of the option
void EuropeanOption::ToggleOption()
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

//Getter Function for Time to Expiry
double EuropeanOption::T() const
{
	//return Time to Expiry of an Option
	return m_T;
}

//Setter Function for Time to Expiry
void EuropeanOption::T(double set_T_value)
{
	//Set Time to Expiry the same as the argument in the function
	m_T = set_T_value;
}


//Getter Function to Get Option Type
std::string EuropeanOption::OptionType() const
{
	//return Option Type (Call or Put) of the Option
	return option_type;
}

//Calculate Delta for a Call Option
double EuropeanOption::CallDelta()const
{
	//Declaring and initializing the variables d1
	double d1 = (log(S() / K()) + (b() + pow(sig(), 2) * 0.5) * T()) / (sig() * sqrt(T()));

	//Calculate and return Call Delta
	return exp((b() - r()) * T()) * N(d1);
}

//Calculate Delta for a Put Option
double EuropeanOption::PutDelta() const
{
	//Declaring and initializing the variables d1
	double d1 = (log(S() / K()) + (b() + pow(sig(), 2) * 0.5) * T()) / (sig() * sqrt(T()));

	//Calculate and return Put Delta
	return -exp((b() - r()) * T()) * N(-d1);
}

//Calculate Delta for a Given Option
double EuropeanOption::Delta() const
{
	//if the option type is call, then
	if (option_type == "Call")
	{
		//return Call Delta
		return CallDelta();
	}
	//else (i.e. if the option type is Put)
	else
	{
		//return Put Delta
		return PutDelta();
	}
}

//Calculate Gamma for Put and Call
//Gamma is the same for both Put and Call Options
double EuropeanOption::Gamma()const
{
	//Declaring and initializing the variables d1
	double d1 = (log(S() / K()) + (b() + pow(sig(), 2) * 0.5) * T()) / (sig() * sqrt(T()));

	//Calculate and return Gamma of the Option
	return (n(d1) * exp((b() - r()) * T())) / (S() * sig() * sqrt(T()));
}

//Calculate approximate Delta
//Using Divided Difference Method
double EuropeanOption::ApproximateDelta(double S, double h) const
{
	//Calculate and return the value of Approximate Delta
	return (OptionPrice(S + h) - OptionPrice(S - h)) / (2 * h);
}

//Calculate approximate Gamma
//Using Divided Difference Method
double EuropeanOption::ApproximateGamma(double S, double h) const
{
	//Calculate and return the value of Approximate Gamma
	return (OptionPrice(S + h) - (2 * OptionPrice(S)) + OptionPrice(S - h))/(h*h);
}