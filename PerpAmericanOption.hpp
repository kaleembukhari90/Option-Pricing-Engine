//Header files containing declarations for Perpetual American Option Class
//The file contains declarations for
//	Default Constructor
//	Parametric Constructor
//	Copy Constructor
//	Destructor, declared virtual
//	Assignment Operator
//	Other Member Functions
//		CallPrice()		--	Function that calculates the Call Option Price
//		PutPrice()		--	Function that calculates the Put Option Price
//	Getter and Setter for
//		OptionType()	--	Option Type is either Call or Put
//	Overloaded Exact Formulae Function for Greeks
//		CallDelta()	--	Over-ridden to throw an exception
//		PutDelta()	--	Over-ridden to throw an exception	
//		Delta()		--	Over-ridden to throw an exception
//		Gamma()		--	Over-ridden to throw an exception
//		ApproximateDelta(double S, double h)	--	Over-ridden to Throw an Exception
//		ApproximateGamma(double S, double h)	--	Over-ridden to Throw an Exception


#ifndef PerpAmericanOption_hpp
#define PerpAmericanOption_hpp

#include <string>
#include <sstream>
#include <iostream>
#include "Option.hpp"

class PerpAmericanOption :public Option
{

public:					//Access Specifier for Public Member Declarations
	PerpAmericanOption();												//Default Constructor
	PerpAmericanOption(const PerpAmericanOption& old_PerpAmericanOption);//Copy Constructor
	PerpAmericanOption(double new_K, double new_sig, double new_r, double new_S, double new_b, std::string new_option_type);	//Parametric Constructor
	virtual ~PerpAmericanOption();											//Destructor Declared Virtual


	//Operator Overloading
	PerpAmericanOption& operator = (const PerpAmericanOption& source);	//Assignment Operator
	
	//Member Functions
	//Call and Put Price Calculating Functions
	virtual double CallPrice() const;									//Function for Call Option Price
	virtual double PutPrice() const;									//Function for Put Option Price

	//Call and Put Price Calculation Function with Stock Price as Argument
	virtual double CallPrice(double S_val) const;						//Function for Call Option Price with Stock Price Argument
	virtual double PutPrice(double S_val) const;						//Function for Put Option Price with Stock Price Argument

	//Getters Option Type
	virtual std::string OptionType() const;								//Getter for Option Type

	//Modifier Function
	virtual void ToggleOption();										//Function that changes/Toggles the Option Type

	//Option Greeks (Implemented to throw an exception)
	virtual double CallDelta() const;									//Over-ridden to Throw an Exception
	virtual double PutDelta() const;									//Over-ridden to Throw an Exception
	virtual double Delta() const;										//Over-ridden to Throw an Exception
	virtual double Gamma() const;										//Over-ridden to Throw an Exception

	//Option Greeks with Approximate Solutions
	//Using Divided Difference Method
	virtual double ApproximateDelta(double S, double h) const;			//Over-ridden to Throw an Exception
	virtual double ApproximateGamma(double S, double h) const;			//Over-ridden to Throw an Exception

};

#endif