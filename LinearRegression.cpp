#include <cmath>
#include <vector>
#include <numeric>
#include <iostream>
#include "LinearRegression.hpp"
#include "PlotAutoscale.hpp"
#include <unistd.h>

LinearRegression::LinearRegression(unsigned int iterations, double lr) : _iterations(iterations), _lr(lr){

}

void LinearRegression::fit(std::vector<double> const X, std::vector<double> const Y) {
	double theta0_ = 0.;	
	double theta1_ = 0.;	
	double size = X.size();

	auto  X_Normalized = NormalizeData(X);
	for (int iter = 0; iter < _iterations; iter++) {	
		double tmpT0 = 0.;
		double tmpT1 = 0.;
		for (auto i=0; i < size; i++) {
			double estimatePrice = _intercept + (_coef * X_Normalized[i]);
			double error = estimatePrice - Y[i];
			tmpT0 += error;
			tmpT1 += error * X_Normalized[i];
		}
		_intercept -= _lr * tmpT0 / size;
		_coef -= _lr * tmpT1 / size;
		if ((iter % 1000) == 0) {
			PlotAutoscale(Y,X, *this);
			usleep(500000);
			std::cout << iter << " iterations. Score: " << score(X, Y) << std::endl;
		}
	}
}

std::vector<double> LinearRegression::NormalizeData(std::vector<double> const & data) {
	std::vector<double> output = data;
	double mod = 0.0;

	std::for_each(data.begin(), data.end(), [&](double data) {
		mod += std::pow(data, 2);
	});
    _mag = std::sqrt(mod);
    if (_mag == 0) {
        throw std::logic_error("The input vector is a zero vector");
    }

	std::for_each(output.begin(), output.end(), [this](double & data) {
		data /= _mag;
	});
	return output;
}

double 	LinearRegression::predict(double X, bool normalizeX) const {
	if (normalizeX == true)
		X /= _mag;// normalization reasons
	return (_coef * X + _intercept);
}

double LinearRegression::score(std::vector<double> const & X, std::vector<double> const & Y) {
	auto X_iter = X.cbegin();
	double RMSE = 0.;

		
	std::for_each(Y.cbegin(), Y.cend(), [&](double value) {
		RMSE += std::pow(value - predict(*X_iter),2);
		X_iter++;
	});
	return std::sqrt(RMSE / Y.size());
}

double	LinearRegression::coef() {return _coef;}

double	LinearRegression::intercept() {return _intercept;}

LinearRegression::~LinearRegression() {}
