//Source file with definitions of all global functions
//in the header file GlobalFunction.hpp

#include "GlobalFunction.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>

//Functions for Standard Cummulative Normal Distribution Function
double N(double x)
{
	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	//return the CDF
	return cdf(myNormal, x);
}

//Functions for Standard Probability Density Function
double n(double x)
{
	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	//return the PDF
	return pdf(myNormal, x);
}