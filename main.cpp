#include "csv.h"
#include <Eigen/Dense>
#include <vector>
#include <iostream>
//#include <ranges>

using namespace Eigen;

auto GradientDescent(std::vector<int>x, std::vector<int> y, double lr, int iterations) {
	std::vector<double> t0tmps(0.), t1tmps(0.);
	double t0tmp = 0., t1tmp = 0.;
	double a, b;

	for (int iter=0; i<iterations; i++) {
		auto dt0 = 0;
		auto dt1 = 0;
		for (auto i=0; i < x.size(); i++) {
			dt0 += (a * x[i] + b[i]) - y[i];
			dt1 += ((a * x[i] + b) - y[i]) * x[i];
		}
		t0 -= dt0 * lr;
		t1 -= dt1 * lr;
	
}

auto	MSELoss(std::vector<int> estimatedPrice, std::vector<int> realPrice) {
	double result = 0.;
	for (auto i=0; i < estimatedPrice.size(); i++) {
		result += std::pow((estimatedPrice[i] - realPrice[i]),2);
	}
	result /= estimatedPrice.size();
	return result;
}

int main() {
	io::CSVReader<2> in("data/data.csv");
	in.read_header(io::ignore_extra_column, "km", "price");
	std::vector<int> kms, prices;
	int km, price;
	while(in.read_row(km,  price)){
			kms.push_back(km);
			prices.push_back(price);
	}
	std::cout << kms[0];
	Eigen::MatrixXd m(2,2);
	return 0;
}
