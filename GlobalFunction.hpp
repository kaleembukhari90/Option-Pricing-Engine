//Header File containing declarations for all global functions and global variables
//Global variable is:
// enum for Option Category (i.e. European or American)
//Global functions are:
//	N(double val)	---		Calculates and return the CDF for "val"
//	n(double val)	---		Calculates and return the pdf for "val"


#ifndef GlobalFunction_hpp
#define GlobalFunction_hpp

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>

//Declaring and Intializing an enum type
//To distinguish between and American and European Option
enum OptionCategory { European = 1, PerpAmerican = 2 };

//Gaussian Functions
double N(double x);			//Function for CDF
double n(double x);			//Function for PDF


#endif
