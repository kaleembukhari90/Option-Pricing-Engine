//Header File for the Abstract Base Class Options
//Contains declarations for
// private members
//	Strike (m_K), Volatility (m_sig), Risk Free Rate(m_r), Stock Price(m_S), Cost of Carry (m_b)
// protected members
//	option_type (Call or Put)
// Public Members 
//	Default Constructor
//	Parametric Constructor
//	Copy Constructor
//	Destructor, declared Virtual
//	Assignment Operator
//	Pure Virtual Member Functions, for the following, which make the class an Abstract Class
//		Call Price
//		Put Price
//		Call Delta
//		Put Delta
//		Delta (Exact Method)
//		Gamma (Exact Method)	
//		Toggle Option (allows to change option type from Call to Put and vice versa)
//	Option Price function that helps achieve the behavior of "Template Method Pattern"
//	Getters and Setter for Option Parameters


#ifndef Option_hpp
#define Option_hpp

#include <string>
#include <iostream>
#include <vector>

class Option
{
private:

	double m_K;			//Variable for Strike
	double m_sig;		//Variable for Volatility
	double m_r;			//Variable for risk free rate
	double m_S;			//Variable for Stock Price
	double m_b;			//Variable for cost to carry

protected:

	std::string option_type;	//Variable for Option Type. i.e. Call Option or Put Option

public:

	Option();								//Defaul Constructorr
	Option(const Option& old_option);		//Copy Constructor
	Option(double new_K, double new_sig, double new_r, double new_S, double new_b, std::string new_option_type);	//Parametric Constructor
	virtual ~Option();						//Destructor

	//Operator Overloading
	Option& operator = (const Option& Source);				//Assignment Operator

	//Pure Virtual Member Function for Option Price
	virtual double CallPrice() const = 0;					//PVMF for Call Option Price (Overridden in derived classes)
	virtual double PutPrice() const = 0;					//PVMF for Put Option Price (Overridden in derived classes)
	virtual double OptionPrice() const;						//Option Price Function (To Leverage Template Method Pattern Design)

	//Pure Virtual Member Functions for Option Price, taking Stock Price as Argument
	virtual double CallPrice(double S_val) const = 0;		//PVMF for Call Option Price, using Price as Arugment (Overridden in derived Classes)
	virtual double PutPrice(double S_val) const = 0;		//PVMF for Put Option Price, using Price as Arugment (Overridden in derived Classes)
	virtual double OptionPrice(double S_val) const;			//Option Price Function (To Leverage Template Method Pattern Design)

	//Getters (Accessing) Functions
	double K() const;						//Getter function for Strike Parameter
	double sig() const;						//Getter function for Volatility Parameter
	double r() const;						//Getter function for Interest rate Parameter
	double S() const;						//Getter function for Stock price Parameter
	double b() const;						//Getter function for cost to carry Parameter
	virtual std::string OptionType() const = 0;	//PVMF to Get the Option Type of an Option (Overridden in derived Classes)

	//Setters (Modifer) Functions
	void K(double set_K_val);				//Setter Function for Strike Parameter
	void sig(double set_sig_val);			//Setter Function for Volatility Parameter
	void r(double set_r_val);				//Setter Function for Interest rate Parameter
	void S(double set_S_val);				//Setter Function for Stock price Parameter
	void b(double set_b_val);				//Setter Function for cost to carry Parameter

	//Option Greeks with Exact Solutions
	//PVMF will be overridden in the derived class/es
	virtual double CallDelta() const = 0;	//PVMF Calculate Delta for Call Option
	virtual double PutDelta() const = 0;	//PVMF Calculate Delta for Put Option
	virtual double Delta() const = 0;		//PVMF Calculate Delta of a Given Option
	virtual double Gamma() const = 0;		//PVMF Calculate Gamma for a Given Option

	virtual void ToggleOption() = 0;		//PVMF To change the type of Option (Call ot Put and Vice Versa)

	//Option Greeks with Approximate Solutions
	//Using Divided Difference Method
	virtual double ApproximateDelta(double S, double h) const = 0;	//PVMF for Approximate Delta (Overridden in derived Classes)
	virtual double ApproximateGamma(double S, double h) const = 0;	//PVMF for Approximate Gamma (Overridden in derived Classes)
};


#endif
