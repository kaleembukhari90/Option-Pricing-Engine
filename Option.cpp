//Source File for the Abstract Base Class Options
//Contains definitions members and member functions of the Abstract Base Class

#include "Option.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <map>

//Default Constructor
Option::Option() :m_K(65), m_sig(0.30), m_r(0.08), m_S(60), m_b(0.08), option_type("Call")
{
}

//Parametric Constructor
Option::Option(double new_K, double new_sig, double new_r, double new_S, double new_b, std::string new_option_type) : m_K(new_K), m_sig(new_sig), m_r(new_r), m_S(new_S), m_b(new_b), option_type(new_option_type)
{
}

//Copy Constructor
Option::Option(const Option& old_option) :m_K(old_option.m_K), m_sig(old_option.m_sig), m_r(old_option.m_r), m_S(old_option.m_S), m_b(old_option.m_b), option_type(old_option.option_type)
{
}


//Destructor
Option::~Option()
{
}

//Assignment Operator
Option& Option::operator=(const Option& source)
{
	//Check for self-assignment, if not self-assigned then
	if (this != &source)
	{
		m_K = source.m_K;
		m_sig = source.m_sig;
		m_r = source.m_r;
		m_b = source.m_b;
		m_S = source.m_S;
		option_type = source.option_type;
	}
	//return the object
	return *this;
}

//Option Price
double Option::OptionPrice() const
{
	//if option type input by the user is "Call", then:
	if (option_type == "Call")
	{
		//Return Call Option Price
		return CallPrice();
	}
	//if option_type is not Call, then
	else
	{
		//Return Put Option Price
		return PutPrice();
	}
}

//Option Price Taking Stock Price as Argument
double Option::OptionPrice(double S_val) const
{
	//if option type input by the user is "Call", then:
	if (option_type == "Call")
	{
		//Return Call Option Price
		return CallPrice(S_val);
	}
	//if option_type is not Call, then
	else
	{
		//Return Put Option Price
		return PutPrice(S_val);
	}
}

//Getter function for Strike Parameter
double Option::K() const
{
	//return Strike of the Option
	return m_K;
}

//Getter function for Volatility Parameter
double Option::sig() const
{
	//return Volatility of the Option
	return m_sig;
}
//Getter function for Interest rate Parameter
double Option::r() const
{
	//return risk-free rate of the Option
	return m_r;
}

//Getter function for Stock price Parameter
double Option::S() const
{
	//return Stock price of the Option
	return m_S;
}

//Getter function for cost to carry Parameter
double Option::b() const
{
	//return Cost of Carry of the Option
	return m_b;
}

//Setter Function for Strike
void Option::K(double set_K_val)
{
	//Set the value of K to the value passed as an argument
	m_K = set_K_val;
}

//Setter Function for Volatility
void Option::sig(double set_sig_val)
{
	//Set the value of sig to the value passed as an argument
	m_sig = set_sig_val;
}

//Setter Function for Interest Rate
void Option::r(double set_r_val)
{
	//Set the value of r to the value passed as an argument
	m_r = set_r_val;
}

//Setter Function for Stock Price
void Option::S(double set_S_val)
{
	//Set the value of S to the value passed as an argument
	m_S = set_S_val;
}

//Setter Function for cost to carry
void Option::b(double set_b_val)
{
	//Set the value of b to the value passed as an argument
	m_b = set_b_val;
}
