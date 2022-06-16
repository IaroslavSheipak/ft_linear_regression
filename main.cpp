#include "csv.h"
#include <Eigen/Dense>
#include <vector>
#include <iostream>
//#include <ranges>

using namespace Eigen;

auto GradientDescentIteration(std::vector<double> x, std::vector<double> y, double lr) {
	double a = 10000.;	
	double b = 10000.;	
	double a_gradient = 0.;
	double b_gradient = 0.;

	
	for (auto iter = 0; iter < 1000; iter++) {	
		a_gradient = 0.;
		b_gradient = 0.;
		for (auto i=0; i < x.size(); i++) {
			a_gradient += (-2. / x.size()) * x[i] * (y[i] - (b + a*x[i]));
			b_gradient += (-2. / x.size()) * (y[i] - (b + a*x[i]));
		}
		a -= a_gradient * lr;
		b -= b_gradient * lr;
		//std::cout << a_gradient << "\t" << b_gradient <<std::endl;
	}
	return std::pair(a, b);
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

int main() {
	io::CSVReader<2> in("data/data.csv");
	in.read_header(io::ignore_extra_column, "km", "price");
	std::vector<double> kms, prices;
	double km, price;
	while(in.read_row(km,  price)){
			kms.push_back(km);
			prices.push_back(price);
	}
	auto weights = GradientDescentIteration(NormalizeData(kms), NormalizeData(prices), 0.005);
	std::cout << weights.first << "\t" << weights.second;
	Eigen::MatrixXd m(2,2);
	return 0;
}
