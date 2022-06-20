#include "LinearRegression.hpp"
#include "csv.h"
#include <cmath>
#include <vector>
#include <iostream>
#include "LinearRegression.hpp"
#include "plot.h"
#include "utils.h"

LinearRegression::LinearRegression(unsigned int iterations, double lr) : _iterations(iterations), _lr(lr){

}

void LinearRegression::fit(std::vector<double> X, std::vector<double> Y) {
	double theta0_ = 0.;	
	double theta1_ = 0.;	
	double size = X.size();

	X = NormalizeData(X);
	for (auto iter = 0; iter < _iterations; iter++) {	
		double tmpT0 = 0.;
		double tmpT1 = 0.;
		for (auto i=0; i < size; i++) {
			double estimatePrice = theta0_ + (theta1_ * X[i]);
			double error = estimatePrice - Y[i];
			tmpT0 += error;
			tmpT1 += error * X[i];
		}
		theta0_ -= _lr * tmpT0 / size;
		theta1_ -= _lr * tmpT1 / size;
	}
	_coef  = theta1_;
	_intercept  = theta0_;
}

std::vector<double> LinearRegression::NormalizeData(std::vector<double> data) {
	std::vector<double> output;
	double mod = 0.0;

    for (size_t i = 0; i < data.size(); ++i) {
        mod += data[i] * data[i];
    }

    _mag = std::sqrt(mod);

    if (_mag == 0) {
        throw std::logic_error("The input vector is a zero vector");
    }

    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = data[i] / _mag;
    }
    //return std::pair(data, mag);
	return data;
}

double 	LinearRegression::predict(double X) {
	X /= _mag;// normalization reasons
	return (_coef * X + _intercept);
}

double	LinearRegression::coef() {return _coef;}

double	LinearRegression::intercept() {return _intercept;}

LinearRegression::~LinearRegression() {}
