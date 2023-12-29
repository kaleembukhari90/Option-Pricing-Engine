//Header file for MatrixPricer Class
//The header file contains declarations for the following
//public member functions, including
//	Default Constructor
//	Destructor, declared virtual
//	Static Function that Takes an input of Option Parameters, Type of Calculation, Option Type(Call or Put) and then performs the required calculation


#ifndef MatrixPricer_hpp
#define MatrixPricer_hpp


#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include "Option.hpp"
#include "EuropeanOption.hpp"
#include "PerpAmericanOption.hpp"
#include "GlobalFunction.hpp"

class MatrixPricer
{

public:
	MatrixPricer();				//Default Constructor
	virtual ~MatrixPricer();	//Destructor

	//Function for Matrix Pricing
	//ParameterMatrix: A matrix of Parameters based on which an option will be constructed, the last column tells if an option is European or American
	//OptionType: The user specifies whether an option is Call or Put
	//CalcType: The user specifier if the calculation needs to be done for 
	//Since not all calculations use "h", it is default intialized as 0.0
	static std::vector<double>MatrixCalculator(const std::vector<std::vector<double>>& ParameterMatrix, std::string OptionType, std::string CalcType, double h = 0.0);
};


#endif
