//Source File for Matrix Pricer Class
//The file contains definitions for all members and member function declared in the Header File
//Header file is: MatrixPricer.hpp


#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "MatrixPricer.hpp"
#include "Option.hpp"
#include "EuropeanOption.hpp"
#include "PerpAmericanOption.hpp"
#include "GlobalFunction.hpp"


//Default Constructor
MatrixPricer::MatrixPricer()
{
}

//Destructor
MatrixPricer::~MatrixPricer()
{
}


std::vector<double>MatrixPricer::MatrixCalculator(const std::vector<std::vector<double>>& ParameterMatrix, std::string OptionType, std::string CalcType, double h)
{
	//Mapping the Calculation Type Passed by the User to an Integer Value
	//Integer Value will be used in the switch-case statement
	std::map<std::string, int> calcType_to_int;
	calcType_to_int["Option Price"] = 1;
	calcType_to_int["Delta"] = 2;
	calcType_to_int["Gamma"] = 3;
	calcType_to_int["Approximate Delta"] = 4;
	calcType_to_int["Approximate Gamma"] = 5;

	//Variable that holds integer value for calculation type
	int calc = calcType_to_int[CalcType];

	//Declaraing and Initializing a Matrix of Parameters that will hold the Parameters passed as an argument
	//Each row represents the parameters of a single option
	std::vector<std::vector<double>> MatrixofParameters = ParameterMatrix;

	//Declaraing a vector of doubles that will hold option prices, delta, or Gamma calculations
	std::vector<double> VectorValues;

	//Declaraing a vector of Parameters to hold each row of the Matrix of Parameters
	std::vector<double> VectorParameters;

	//Take the Option Category (European or American) from the Parameter Matrix
	int OptionCategory = static_cast<int>(MatrixofParameters[0][6]);


	for (int r = 0; r < MatrixofParameters.size(); ++r)
	{
		//Intializing the VectorParameter variable by assing the 'r'th row of the Matrix
		VectorParameters = MatrixofParameters[r];

		//Pointer to Option Base Class, holds the address of the derived Option class in the code
		//To enable polymorphic behavior of the functions
		Option* Option_ptr;

		//if-else code block to check whether an Option is European, American, or other
		//and then instantiate the apt Option, and perform required calculations
		if (OptionCategory == European)
		{
			//Instantiating an Object of European Option, using Parametric Constructor
			EuropeanOption EuropeanOption(VectorParameters[0], VectorParameters[1], VectorParameters[2], VectorParameters[3], VectorParameters[4], VectorParameters[5], OptionType);

			//If a European Option is instantiated, assign its address to the Pointer
			Option_ptr = &EuropeanOption;
			switch (calc)
			{
				//If the user wants to Calculate Option Prices for a Matrix of Parameters
			case 1:
				//calculate the option price by calling Option Price function on the Option
				//Push back the value into the vector that holds value of the calculations
				VectorValues.push_back(Option_ptr->OptionPrice());
				break;

				//If the user wants to Calculate Delta of an Option, for a matrix of Parameters
			case 2:
				//calculate the Delta of the Option, by Calling Delta function
				//Push back the value into the vector that holds value of the calculations
				VectorValues.push_back(Option_ptr->Delta());
				break;

				//If the user wants to Calculate Gamma of an Option, for a matrix of Parameters
			case 3:
				//calculate the Gamma of the Option, by Calling Gamma function
				//Push back the value into the vector that holds value of the calculations
				VectorValues.push_back(Option_ptr->Gamma());
				break;

				//If the user wants to Calculate Approximate Delta of an Option, for a matrix of Parameters
			case 4:
				//calculate the Approximate Delta of the Option, by Calling the Approximate Delta Function
				//Push back the value into the vector that holds value of the calculations
				VectorValues.push_back(Option_ptr->ApproximateDelta(VectorParameters[4], h));
				break;

				//If the user wants to Calculate Approximate Gamma of an Option, for a matrix of Parameters
			case 5:
				//calculate the Approximate Gamma of the Option, by Calling the Approximate Gamma Function
				//Push back the value into the vector that holds value of the calculations
				VectorValues.push_back(Option_ptr->ApproximateGamma(VectorParameters[4], h));
				break;
			}
		}
		else if (OptionCategory == PerpAmerican)
		{
			//Instantiating an Object of American Option, using Parametric Constructor
			PerpAmericanOption PerpAmericanOption(VectorParameters[1], VectorParameters[2], VectorParameters[3], VectorParameters[4], VectorParameters[5], OptionType);

			Option_ptr = &PerpAmericanOption;
			//If a Perpetual American Option is instantiated, assign its address to the Pointer
			switch (calc)
			{
				//If the user wants to Calculate Option Prices for a Matrix of Parameters
			case 1:
				//calculate the option price by calling Option Price function on the Option
				//Push back the value into the vector that holds value of the calculations
				VectorValues.push_back(Option_ptr->OptionPrice());
				break;

				//If the user wants to Calculate Delta of an Option, for a matrix of Parameters
			case 2:
				//calculate the Delta of the Option, by Calling Delta function
				//Push back the value into the vector that holds value of the calculations
				VectorValues.push_back(Option_ptr->Delta());
				break;

				//If the user wants to Calculate Gamma of an Option, for a matrix of Parameters
			case 3:
				//calculate the Gamma of the Option, by Calling Gamma function
				//Push back the value into the vector that holds value of the calculations
				VectorValues.push_back(Option_ptr->Gamma());
				break;

				//If the user wants to Calculate Approximate Delta of an Option, for a matrix of Parameters
			case 4:
				//calculate the Approximate Delta of the Option, by Calling the Approximate Delta Function
				//Push back the value into the vector that holds value of the calculations
				VectorValues.push_back(Option_ptr->ApproximateDelta(VectorParameters[4], h));
				break;

				//If the user wants to Calculate Approximate Gamma of an Option, for a matrix of Parameters
			case 5:
				//calculate the Approximate Gamma of the Option, by Calling the Approximate Gamma Function
				//Push back the value into the vector that holds value of the calculations
				VectorValues.push_back(Option_ptr->ApproximateGamma(VectorParameters[4], h));
				break;
			}
		}
	}
	return VectorValues;
}