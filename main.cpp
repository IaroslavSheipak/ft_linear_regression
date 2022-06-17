#include "csv.h"
//#include <Eigen/Dense>
#include <cmath>
#include <vector>
#include <iostream>
//#include <ranges>

//using namespace Eigen;

auto GradientDescentIteration(std::vector<double> x, std::vector<double> y, double lr) {
	double theta0_ = 0.;	
	double theta1_ = 0.;	
	double size = x.size();

	for (auto iter = 0; iter < 4000; iter++) {	
		double tmpT0 = 0.;
		double tmpT1 = 0.;
		for (auto i=0; i < size; i++) {
			double estimatePrice = theta0_ + (theta1_ * x[i]);
			double error = estimatePrice - y[i];
			tmpT0 += error;
			tmpT1 += error * x[i];
		}
		theta0_ -= lr * tmpT0 / size;
		theta1_ -= lr * tmpT1 / size;
	}
	return std::pair(theta1_, theta0_);
}

auto NormalizeData(std::vector<double> data) {
	std::vector<double> output;
	double mod = 0.0;

    for (size_t i = 0; i < data.size(); ++i) {
        mod += data[i] * data[i];
    }

    double mag = std::sqrt(mod);

    if (mag == 0) {
        throw std::logic_error("The input vector is a zero vector");
    }

    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = data[i] / mag;
    }
    return data;
}

auto PredictY(double first, double second, double mileage) {
	return (first * mileage + second);
}

int main() {
	io::CSVReader<2> in("data/data.csv");
	in.read_header(io::ignore_extra_column, "km", "price");
	std::vector<double> kms, prices;
	double km, price;
	while(in.read_row(km,  price)){
			//std::cout << km << "\t" << price << std::endl;
			kms.push_back(km);
			prices.push_back(price);
	}
	auto weights = GradientDescentIteration(NormalizeData(kms), prices, 0.02);
	std::cout << weights.first << "\t" << weights.second << std::endl;
	std::cout << PredictY(weights.first,weights.second,240000);
	//Eigen::MatrixXd m(2,2);
	return 0;
}
