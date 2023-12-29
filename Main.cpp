//The Main() function program is designed to perform calculations for European Option
//	1. Find the exact solution for Option Prices (using the Black-Scholes Pricing Formula)
//	2. Calculate Option Prices using Put-Call Parity
//	3. Find if the option prices satisfy the Put-Call Parity
//	4. Compute the Greeks/Sensitivities of the Options
//		a. Greeks using the Exact Method
//		b. Greeks using the Approximation Method
//	5. Option Pricing and Greek Computations are also performed by using a MatrixCalculator function
//		that takes a matrix of option parameters and returns a vector of calculated values


#include "Option.hpp"
#include "EuropeanOption.hpp"
#include "PerpAmericanOption.hpp"
#include "MatrixPricer.hpp"
#include "GlobalFunction.hpp"
#include "OptionException.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>


int main()
{

	//Option Prices Using the Black-Scholes Exact Pricing Formula

	//The Inputs for the Batch are in the following order
	//T, K, sig, r, S, b, Option Type
	//We are pricing Stock options, therefore b = r
	//You can also change the value for b

	EuropeanOption Batch1(1.45, 120, 0.51, (4.5/100.0), 108, 0, "Call");
	EuropeanOption Batch2(1.0, 100, 0.2, 0.0, 100, 0.0, "Call");
	EuropeanOption Batch3(1.0, 10, 0.50, 0.12, 5, 0.12, "Call");
	EuropeanOption Batch4(30.0, 100.0, 0.30, 0.08, 100.0, 0.08, "Call");

	//Creating a vector of European Options
	std::vector<EuropeanOption> VectorofOptions;

	//Pushing Batches of European Options into the vector of European Option
	VectorofOptions.push_back(Batch1);
	VectorofOptions.push_back(Batch2);
	VectorofOptions.push_back(Batch3);
	VectorofOptions.push_back(Batch4);

	//Setting the iterator for Vector of Options
	std::vector<EuropeanOption>::iterator myIter = VectorofOptions.begin();

	std::cout << "For Group A, pricing Equity Options using Black-Scholes Formula. i.e. b = r. For part a,b,c,and d" << std::endl << "Note:Parametric Constructor allows for creating an option where b != r" << std::endl << std::endl;
	std::cout << "******* Part (a) Option Pricing Using Exact Formula *******" << std::endl << std::endl;

	//Declaring and Initializing the variable to print the apt Batch Number
	int BatchNum = 1;

	std::cout << "Batch#	" << "Call Price	" << "Put Price" << std::endl;

	//Iterating through the Vector of Options and calling Option Methods
	for (myIter; myIter != VectorofOptions.end(); ++myIter)
	{
		//Calling Option Price method on the option
		std::cout << BatchNum << "	" << myIter->OptionPrice();

		//Changing the type of Option. i.e Call becomes Put and Put becomes Call
		myIter->ToggleOption();

		//Calling Option Price method on the option
		std::cout << "		" << myIter->OptionPrice() << std::endl;

		//Incrementing BatchNum by 1
		++BatchNum;
	}


	//Option Prices Using Put Call Parity
	std::cout << std::endl << "******* Part (b) Option Pricing using Put-Call Parity *******" << std::endl << std::endl;

	//Printing the Option Prices using Put-Call Parity
	std::cout << "Batch#	" << "Exact Price Option	" << "Exact Price	" << "Put Call Parity Price for Opposite Option" << std::endl;

	//Reseting the iterator to begining of the Vector of European Options
	myIter = VectorofOptions.begin();

	//Re-initializing BatchNum to 1
	BatchNum = 1;

	//Iterating through the Vector of Options and calling Option Methods
	for (myIter; myIter != VectorofOptions.end(); ++myIter)
	{
		//Calling method OptionType() and OptionPrice() on the Option
		std::cout << BatchNum << "		" << myIter->OptionType() << "		" << myIter->OptionPrice();

		//Calling method PutCallParity() to get the price of Call if the Option is Put, and price of Put if the given Option is Call
		std::cout << "		" << myIter->PutCallParity() << std::endl;

		//Incrementing BatchNum by 1
		++BatchNum;
	}
	std::cout << std::endl;

	//is Put Call Parity Satisfied?
	//Calling the function PutCallParityCheck() to check if Put Call Parity is satisifed or not
	//If satisfied, the result will be true; false otherwise
	std::cout << "Is Put-Call Parity satisfied? true if satisfied, false otherwise" << std::endl << std::endl;

	std::cout << "Batch#	" << "Put Call Parity Satisfied?" << std::endl;

	//Reseting the iterator to begining of the Vector of European Options
	myIter = VectorofOptions.begin();

	//Re-intializing the BatchNum to 1
	BatchNum = 1;

	//Iterating through the Vector of Options and calling Option Methods
	for (myIter; myIter != VectorofOptions.end(); ++myIter)
	{
		//Calling the method to check if Put Call Parity is satified for a given Option
		std::cout << BatchNum << "	" << std::boolalpha << myIter->PutCallParityCheck() << std::endl;

		//Incrementing BatchNum by 1
		++BatchNum;
	}

	std::cout << std::endl;

	//Test Cases for Batch 1 - Monotonically increasing Stock Prices
	std::cout << std::endl << "******* Part (c) & (d) Option Pricing for monotonically increasing range of Parameters *******" << std::endl;

	//Reseting the iterator to begining of the Vector of European Options
	myIter = VectorofOptions.begin();

	//Declaraing and intializing the variable that defines the calculation type to be performed
	std::string CalculationType = "Option Price";

	//Re-initializing BatchNum to 1
	BatchNum = 1;

	//Iterating through the vector of Options to perform calculations on each of the Option
	for (myIter; myIter != VectorofOptions.end(); ++myIter)
	{
		//Declaring and initializing Option Parameters
		//Assignment is done by Calling Getter Function for each of the Option Parameter for a given Option
		double T = myIter->T();
		double K = myIter->K();
		double Vol = myIter->sig();
		double r = myIter->r();
		double S = myIter->S();
		double b = myIter->b();

		//Initializing a vector of Option Parameters for European Option for Batch 1 Parameters
		//Order of Parameters: T, K, sig, r, S, b, Category of Option (European)
		std::vector<double> OptionParameters{ T, K, Vol, r, S, b,European };

		//Declaraing and Intializing the variables to generate a matrix of Parameters with increasing Stock Price
		double Start_Stock = S;
		double End_Stock = S + 10.0;
		double StepSize_Stock = 0.5;

		//Declaraing and Intializing the variables to generate a matrix of Parameters with increasing Time to Expiry
		double Start_T = T;
		double End_T = Start_T + 5;
		double StepSize_T = 0.25;

		//Declaraing and Intializing the variables to generate a matrix of Parameters with increasing Volatility (sig)
		double Start_Vol = Vol;
		double End_Vol = Start_Vol + 2;
		double StepSize_Vol = 0.1;

		//Declaraing and Intializing the variables to generate a matrix of Parameters with increasing Strike
		double Start_K = K;
		double End_K = Start_K + 10;
		double StepSize_K = 0.5;

		//Calculating and storing Option Greek Calculation in a vector
		//Calculations are performed by using Static Function "MatrixCalculator" which takes a matrix of Option Parameters and returns
		//a vector of the specified calculation (user specifies the calculation to perform)
		std::vector<std::vector<double>> MatrixParam_IncreasingStock = GenerateMatrix(OptionParameters, Start_Stock, End_Stock, StepSize_Stock, "S");
		std::vector<std::vector<double>> MatrixParam_Increasing_T = GenerateMatrix(OptionParameters, Start_T, End_T, StepSize_T, "T");
		std::vector<std::vector<double>> MatrixParam_Increasing_Vol = GenerateMatrix(OptionParameters, Start_Vol, End_Vol, StepSize_Vol, "sig");
		std::vector<std::vector<double>> MatrixParam_Increasing_K = GenerateMatrix(OptionParameters, Start_K, End_K, StepSize_K, "K");

		std::cout << std::endl << "******* Option Pricing for monotonically increasing range of Stock Price *******" << std::endl << std::endl;
		std::cout << "Batch#	" << "T	" << "K	" << "Vol	" << "r	" << "S	" << "b	" << "Call Price	" << "Put Price	" << std::endl;

		//Calling the Static Function that Performs a specified calculation on the matrix of Parameters.
		std::vector<double>CallPriceVector_IncreasingStock = MatrixPricer::MatrixCalculator(MatrixParam_IncreasingStock, "Call", CalculationType);
		std::vector<double>PutPriceVector_IncreasingStock = MatrixPricer::MatrixCalculator(MatrixParam_IncreasingStock, "Put", CalculationType);

		//Iterating through the matrix to Print the Parameters of the Option and Priting the Calculation performed
		//for that specific option and print out the final output
		for (int r = 0; r < MatrixParam_IncreasingStock.size(); ++r)
		{
			std::cout << BatchNum << "	";
			for (int c = 0; c < (MatrixParam_IncreasingStock[r].size() - 1); c++)
			{
				//Print the value at the row-column intersection of the matrix
				std::cout << MatrixParam_IncreasingStock[r][c] << "	";
			}
			//Print the value on the 'r'th row of the vector
			std::cout << CallPriceVector_IncreasingStock[r] << "		" << PutPriceVector_IncreasingStock[r] << std::endl;
		}

		std::cout << std::endl << "******* Option Pricing for monotonically increasing range of Time to Expiry *******" << std::endl << std::endl;
		std::cout << "Batch#	" << "T	" << "K	" << "Vol	" << "r	" << "S	" << "b	" << "Call Price	" << "Put Price	" << std::endl;

		//Calling the Static Function that Performs a specified calculation on the matrix of Parameters.
		std::vector<double>CallPriceVector_IncreasingT = MatrixPricer::MatrixCalculator(MatrixParam_Increasing_T, "Call", CalculationType);
		std::vector<double>PutPriceVector_IncreasingT = MatrixPricer::MatrixCalculator(MatrixParam_Increasing_T, "Put", CalculationType);

		//Iterating through the matrix to Print the Parameters of the Option and Priting the Calculation performed
		//for that specific option and print out the final output
		for (int r = 0; r < MatrixParam_Increasing_T.size(); ++r)
		{
			std::cout << BatchNum << "	";
			for (int c = 0; c < (MatrixParam_Increasing_T[r].size() - 1); c++)
			{
				//Print the value at the row-column intersection of the matrix
				std::cout << MatrixParam_Increasing_T[r][c] << "	";
			}
			//Print the value on the 'r'th row of the vector
			std::cout << CallPriceVector_IncreasingT[r] << "		" << PutPriceVector_IncreasingT[r] << std::endl;
		}


		std::cout << std::endl << "******* Option Pricing for monotonically increasing range of Volatility *******" << std::endl << std::endl;
		std::cout << "Batch#	" << "T	" << "K	" << "Vol	" << "r	" << "S	" << "b	" << "Call Price	" << "Put Price	" << std::endl;

		//Calling the Static Function that Performs a specified calculation on the matrix of Parameters.
		std::vector<double>CallPriceVector_IncreasingVol = MatrixPricer::MatrixCalculator(MatrixParam_Increasing_Vol, "Call", CalculationType);
		std::vector<double>PutPriceVector_IncreasingVol = MatrixPricer::MatrixCalculator(MatrixParam_Increasing_Vol, "Put", CalculationType);

		//Iterating through the matrix to Print the Parameters of the Option and Priting the Calculation performed
		//for that specific option and print out the final output
		for (int r = 0; r < MatrixParam_Increasing_Vol.size(); ++r)
		{
			std::cout << BatchNum << "	";
			for (int c = 0; c < (MatrixParam_Increasing_Vol[r].size() - 1); c++)
			{
				//Print the value at the row-column intersection of the matrix
				std::cout << MatrixParam_Increasing_Vol[r][c] << "	";
			}
			//Print the value on the 'r'th row of the vector
			std::cout << CallPriceVector_IncreasingVol[r] << "		" << PutPriceVector_IncreasingVol[r] << std::endl;
		}
		std::cout << std::endl;

		std::cout << std::endl << "******* Option Pricing for monotonically increasing range of Strike *******" << std::endl << std::endl;
		std::cout << "Batch#	" << "T	" << "K	" << "Vol	" << "r	" << "S	" << "b	" << "Call Price	" << "Put Price	" << std::endl;

		//Calling the Static Function that Performs a specified calculation on the matrix of Parameters.
		std::vector<double>CallPriceVector_IncreasingK = MatrixPricer::MatrixCalculator(MatrixParam_Increasing_K, "Call", CalculationType);
		std::vector<double>PutPriceVector_IncreasingK = MatrixPricer::MatrixCalculator(MatrixParam_Increasing_K, "Put", CalculationType);

		//Iterating through the matrix to Print the Parameters of the Option and Priting the Calculation performed
		//for that specific option and print out the final output
		for (int r = 0; r < MatrixParam_Increasing_K.size(); ++r)
		{
			std::cout << BatchNum << "	";
			for (int c = 0; c < (MatrixParam_Increasing_K[r].size() - 1); c++)
			{
				//Print the value at the row-column intersection of the matrix
				std::cout << MatrixParam_Increasing_K[r][c] << "	";
			}
			//Print the value on the 'r'th row of the vector
			std::cout << CallPriceVector_IncreasingK[r] << "		" << PutPriceVector_IncreasingK[r] << std::endl;
		}
		std::cout << std::endl;
	
	std::cout << "*******	*******	*******	*******	*******	*******	*******	*******	*******	*******	*******	" << std::endl << std::endl;

	//Increment variable BatchNum by 1
	++BatchNum;
	}
	



	std::cout << "Calculating Option Sensitivities (Greeks) for Future Option. i.e. b = 0" << std::endl << std::endl;
	
	//
	//*********************************Option Greeks Exact (Single Option)*****************************
	//

	//Instantiating a European Option, Parametric Constructor is called
	//Future Option: b = 0;
	//Order of Parameters: T, K, sig, r, S, b, Option Tyoe (Call or Put)
	EuropeanOption FutureOption(1.45, 120, 0.51, (4.5 / 100.0), 108, 0, "Call");

	std::cout << "******* Part (a) Calculating Delta and Gamma of Future Option (Call and Put)	*******" << std::endl << std::endl;

	std::cout << "T: " << FutureOption.T() << " K: " << FutureOption.K() << " Vol: " << FutureOption.sig() << " r: " << FutureOption.r() << "	S: " << FutureOption.S() << " b: " << FutureOption.b() << std::endl << std::endl;
	
	std::cout << "Option Type	" << "Exact Delta	" << "Exact Gamma	" << std::endl;
	
	//Calling Exact formula methods for Delta and Gamma of European Options
	std::cout << FutureOption.OptionType() << "		" << FutureOption.Delta() << "	" << FutureOption.Gamma() << std::endl;
	
	//Change the Option Type (from Call to Put Vice Versa)
	FutureOption.ToggleOption();

	//Calling Exact formula methods for Delta and Gamma of European Options
	std::cout << FutureOption.OptionType() << "		" << FutureOption.Delta() << "	" << FutureOption.Gamma() << std::endl;

	//Change the Option Type (from Call to Put Vice Versa)
	FutureOption.ToggleOption();

	//
	//************** Greeks using Matrix Pricer*******************************************
	// 

	//Creating a vector of European Options to Perform Calculations for Greeks
	std::vector<EuropeanOption> VectorofOptions_forGreeks;

	//Pushing the FutureOption (European Option) to the vector of European Option
	VectorofOptions_forGreeks.push_back(FutureOption);

	//Declaraing and intializing the variable that defines the calculation type to be performed
	std::string CalculationTypeDelta = "Delta";
	std::string CalculationTypeGamma = "Gamma";

	//Setting the Iterator for the Vector to begining of the vector
	std::vector<EuropeanOption>::const_iterator myIter2 = VectorofOptions_forGreeks.begin();
	
	//Iterating through the Vector to perform calculations
	for (myIter2; myIter2 != VectorofOptions_forGreeks.end(); ++myIter2)
	{

		//Declaring and initializing Option Parameters
		//Assignment is done by Calling Getter Function for each of the Option Parameter for a given Option
		double T = myIter2->T();
		double K = myIter2->K();
		double Vol = myIter2->sig();
		double r = myIter2->r();
		double S = myIter2->S();
		double b = myIter2->b();

		//Creating a vector of Option Parameters, for which the calculations for Option Greeks will be performed
		std::vector<double> OptionParameters = {T,K, Vol, r, S, b, European };

		//Declaraing and Intializing the variables to generate a matrix of Parameters with increasing Stock Price
		double Start_Stock = S;
		double End_Stock = Start_Stock + 10;
		double StepSize_Stock = 0.5;

		//Generating a matrix of Option Parameters, with increasing Stock Price; keeping all other Parameters Constant
		std::vector<std::vector<double>> MatrixParam_IncreasingStock = GenerateMatrix(OptionParameters, Start_Stock, End_Stock, StepSize_Stock, "S");

		//Calculating and storing Option Greek Calculation in a vector
		//Calculations are performed by using Static Function "MatrixCalculator" which takes a matrix of Option Parameters and returns
		//a vector of the specified calculation (user specifies the calculation to perform)
		std::vector<double>CallDelta_IncreasingStock = MatrixPricer::MatrixCalculator(MatrixParam_IncreasingStock, "Call", CalculationTypeDelta);
		std::vector<double>PutDelta_IncreasingStock = MatrixPricer::MatrixCalculator(MatrixParam_IncreasingStock, "Put", CalculationTypeDelta);
		std::vector<double>CallGamma_IncreasingStock = MatrixPricer::MatrixCalculator(MatrixParam_IncreasingStock, "Call", CalculationTypeGamma);
		std::vector<double>PutGamma_IncreasingStock = MatrixPricer::MatrixCalculator(MatrixParam_IncreasingStock, "Put", CalculationTypeGamma);


		std::cout << std::endl << "******* part(b) and (c) Option Greeks for monotonically increasing range of Stock Price *******" << std::endl << std::endl;
		std::cout << "T	" << "K	" << "Vol	" << "r	" << "S	" << "b	" << "Call Delta	" << "Put Delta	" << "Call Gamma	" << "Put Gamma" << std::endl;

		//Using a loop to print the values of the Option Parameter Matrix and the Calculations for Greeks
		for (int r = 0; r < CallDelta_IncreasingStock.size(); ++r)
		{
			for (int c = 0; c < (MatrixParam_IncreasingStock[r].size() - 1); c++)
			{
				//Print the value at the row-column intersection of the matrix
				std::cout << MatrixParam_IncreasingStock[r][c] << "	";
			}
			//Print the value on the 'r'th row of the vector
			std::cout << CallDelta_IncreasingStock[r] << "	" << PutDelta_IncreasingStock[r] << "	" << CallGamma_IncreasingStock[r] << "	" << PutGamma_IncreasingStock[r] << std::endl;
		}
		std::cout << std::endl;
	}
	
	//
	//******************** Greeks Using Approximate Method*************************
	//
	
	std::cout << "******* part(d) Greeks using Approximate Method for a Stock Price and a varying range of h values	" << std::endl << std::endl;
	std::cout << "Option" << "	h	" << "S	" << "Exact Delta	" << "Approx Delta	" << "Exact Gamma	" << "Approx Gamma	" << std::endl;
	
	//Declaring and Initializing a value for h, which will be decremented
	double h = 2.0;

	//Getting the Stock Price of the Option
	double S = FutureOption.S();

	//Running a for loop to print the value of Delta(), ApproximateDelta(), Gamma(), and ApproximateGamma() for an Option
	//ApproximateDelta() and ApproximateGamma() are called for various values of "h" to compare the accuracy
	//between the exact formula for Delta and Gamma and the approximation results for Delta and Gamma
	for (int i = 0; i < 20; ++i)
	{ 
		std::cout << FutureOption.OptionType() << "	" << h << "	" << S << "	" << FutureOption.Delta() << "	" << FutureOption.ApproximateDelta(S, h) << "	" << FutureOption.Gamma() << "	" << FutureOption.ApproximateGamma(S, h) << std::endl;
		h -= 0.1;
	}

	FutureOption.ToggleOption();
	std::cout << std::endl;

	std::cout << "Option" << "	h	" << "S	" << "Exact Delta	" << "Approx Delta	" << "Exact Gamma	" << "Approx Gamma	" << std::endl;

	//Resetting the value for h
	h = 2.0;

	//Running a for loop to print the value of Delta(), ApproximateDelta(), Gamma(), and ApproximateGamma() for an Option
	//ApproximateDelta() and ApproximateGamma() are called for various values of "h" to compare the accuracy
	//between the exact formula for Delta and Gamma and the approximation results for Delta and Gamma
	for (int i = 0; i < 20; ++i)
	{
		std::cout << FutureOption.OptionType() << "	" << h << "	" << S << "	" << FutureOption.Delta() << "	" << FutureOption.ApproximateDelta(S, h) << "	" << FutureOption.Gamma() << "	" << FutureOption.ApproximateGamma(S, h) << std::endl;
		h -= 0.1;
	}

	//Statement on the analysis
	std::cout << std::endl << "Analysis: As the value for h becomes smaller and smaller, the value for both Delta and Gamma using Approximate method gets close to the value using Exact Formula" << std::endl << std::endl;
	

	//Test Case for using a matrix of Option Parameters to calculate Approximate Detla and Approximate Gamma
	std::cout << "******** Use case for Calculating Approximate Delta and Gamma using Matrix of Parameters ******** " << std::endl << std::endl;

	//Creating a vector of Option Parameters, for which the calculations for Option Greeks will be performed
	//Order of Parameters: T, K, sig(Volatility), r, S, b, Option Category (European)
	std::vector<double> FutureOptionParameters = { 0.5,100, 0.36, 0.1, 105, 0, European };

	//Generating a matrix of Option Parameters, with increasing Stock Price; keeping all other Parameters Constant
	std::vector<std::vector<double>> MatrixofParametersNewGreeks = GenerateMatrix(FutureOptionParameters, 105, 115, 0.5, "S");

	//Resting the value of h, and intializing it to 0.001
	h = 0.001;

	//Calculating Option Greeks using a matrix of Option Parameters
	//Each Greek is stored in a vector
	std::vector<double>CallApproxDelta = MatrixPricer::MatrixCalculator(MatrixofParametersNewGreeks, "Call", "Approximate Delta",h);
	std::vector<double>CallExactDelta = MatrixPricer::MatrixCalculator(MatrixofParametersNewGreeks, "Call", "Delta");
	std::vector<double>PutApproxDelta = MatrixPricer::MatrixCalculator(MatrixofParametersNewGreeks, "Put", "Approximate Delta", h);
	std::vector<double>PutExactDelta = MatrixPricer::MatrixCalculator(MatrixofParametersNewGreeks, "Put", "Delta");
	std::vector<double>CallApproxGamma = MatrixPricer::MatrixCalculator(MatrixofParametersNewGreeks, "Call", "Approximate Gamma", h);
	std::vector<double>CallExactGamma = MatrixPricer::MatrixCalculator(MatrixofParametersNewGreeks, "Call", "Gamma");
	std::vector<double>PutApproxGamma = MatrixPricer::MatrixCalculator(MatrixofParametersNewGreeks, "Put", "Approximate Gamma", h);
	std::vector<double>PutExactGamma = MatrixPricer::MatrixCalculator(MatrixofParametersNewGreeks, "Put", "Gamma", h);


	std::cout << "Note: D represents Delta and G represents Gamma" << std::endl << std::endl;
	std::cout << "h	" << "T	" << "K	" << "Vol	" << "r	" << "S	" << "b	" << "Call D Approx	" << "Call D Exact	" << "Put D Approx	" << "Put D Exact	" << "Call/Put G Approx	" << "Call/Put G Exact	"<<std::endl;

	//Using a loop to print the values of the Option Parameter Matrix and the Calculations for Greeks
	for (int r = 0; r < MatrixofParametersNewGreeks.size(); ++r)
	{
		std::cout << h << "	";
		for (int c = 0; c < (MatrixofParametersNewGreeks[r].size() - 1); c++)
		{
			//Print the value at the row-column intersection of the matrix
			std::cout << MatrixofParametersNewGreeks[r][c] << "	";
		}
		//Print the value on the 'r'th row of the vector
		std::cout << CallApproxDelta[r] << "	" <<  CallExactDelta[r] << "	" << PutApproxDelta[r] <<  "	" << PutExactDelta[r] << "	"<<PutApproxGamma[r] << "		" << CallExactGamma[r] << std::endl;
	}
	std::cout << std::endl;
	
	return 0;
}