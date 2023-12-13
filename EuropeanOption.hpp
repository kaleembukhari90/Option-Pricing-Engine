//Header File for European Options
//Contains the declarations for the following
//prviate members
//	m_T	---	Time to Expiry of European Option
//public members functions
//	Default Constructor
//	Copy Constructor
//	Parametric Constructor
//	Destructor, declared virtual
//	Assignment Operator
//	CallPrice()		---		over-ride the PVMF of the Abstract Base Class Option
//	PutPrice()		---		over-ride the PVMF of the Abstract Base Class Option
//	CallPrice(double new_Stock_val)	---	over-ride the PVMF of the Abstract Base Class Option
//	PutPrice(double new_Stock_val)	---	over-ride the PVMF of the Abstract Base Class Option
//	PutCallParity()			---		Calculates the Option Price using Put Call Parity equation
//	PutCallParityCheck()	---		Check if Put Call Parity if satisfied for two options
//	ToggleOption()			---		over-ride the PVMF of the Abstract Base Class Option
//	CallDelta()				---		over-ride the PVMF of the Abstract Base Class, calculates Call Option Delta using Exact Formula
//	PutDelta()				---		over-ride the PVMF of the Abstract Base Class, calculates Put Option Delta using Exact Formula
//	Delta()					---		over-ride the PVMF of the Abstract Base Class, calculates Call/Put Option Delta using Exact Formula
//	ApproximateDetla()		---		over-ride the PVMF of the Abstract Base Class, calculates Call/Put Option Delta using Approximation
//	ApproximateGamma()		---		over-ride the PVMF of the Abstract Base Class, calculates Call/Put Option Gamma using Approximation



#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp

#include "Option.hpp"
#include "GlobalFunction.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class EuropeanOption : public Option
{
private:
	double m_T;			//Variable for Time to Expiry

public:

	//Constructors and Destructor
	EuropeanOption();										//Default Constructor
	EuropeanOption(const EuropeanOption& old_euro_option);	//Copy Constructor
	EuropeanOption(double new_T, double new_K, double new_sig, double new_r, double new_S, double new_b, std::string new_option_type);	//Parametric Constructor
	virtual ~EuropeanOption();								//Destructor

	//Operator Overloading
	EuropeanOption& operator = (const EuropeanOption& source);	//Assignment Operator

	//Other Member Functions

	//Call and Put Price Calculating Functions
	virtual double CallPrice() const;						//Function for Call Option Price
	virtual double PutPrice() const;						//Function for Put Option Price

	//Call and Put Price Calculation Function with Stock Price as Argument
	virtual double CallPrice(double S_val) const;			//Function for Call Option Price with Stock Price Argument
	virtual double PutPrice(double S_val) const;			//Function for Put Option Price with Stock Price Argument
	
	//Put Call Parity Functions
	double PutCallParity() const;							//PutCallParity for Option Price
	bool PutCallParityCheck() const;						//Function to Check if Put Call Parity is Satified

	//Modifier Function
	virtual void ToggleOption();							//Function that changes/Toggles the Option Type

	//Getter Functions
	virtual double T() const;								//Function to Get Time to Expiry of the Option
	std::string OptionType() const;							//Getter for Option Type

	//Setter Functions
	virtual void T(double set_T_value);						//Set the value of Time to Expiry
	

	//Functions for Calculating the Greeks of the Options
	virtual double CallDelta() const;						//Calculate Delta for Call Option
	virtual double PutDelta() const;						//Calculate Delta for Put Option
	virtual double Delta() const;							//Calculate Delta of a Given Option
	virtual double Gamma() const;							//Calculate Gamma for a Given Option

	//Option Greeks with Approximate Solutions
	//Using Divided Difference Method
	virtual double ApproximateDelta(double S, double h) const;	//Calculate Delta for an Option using approximation method
	virtual double ApproximateGamma(double S, double h) const;	//Calculate Gamma for an Option using approximation method

};

#endif

