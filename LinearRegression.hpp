#pragma once
#include "LinearRegression.hpp"
#include "csv.h"
#include <cmath>
#include <vector>
#include <iostream>
#include "LinearRegression.hpp"
#include "plot.h"
#include "utils.h"


class LinearRegression {
	
	public:
				LinearRegression(unsigned int iterations, double lr);
				LinearRegression(LinearRegression const & src);
				LinearRegression & operator=(LinearRegression const & src);
				~LinearRegression();
		auto	score();
		void 	fit(std::vector<double> X, std::vector<double> Y);
		double 	predict(double X);
		double	coef();
		double	intercept();
	private:
	std::vector<double> 		NormalizeData(std::vector<double> data);
		double		_lr;
		unsigned	_iterations;
		double		_intercept;	
		double		_coef;
		double		_mag;
};
