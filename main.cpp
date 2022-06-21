#include "csv.h"
#include <cmath>
#include <vector>
#include <iostream>
#include "LinearRegression.hpp"
#include "plot.h"
#include "utils.h"
#include <algorithm>


int main() {
	io::CSVReader<2> in("data/data.csv");
	in.read_header(io::ignore_extra_column, "km", "price");
	std::vector<double> kms, prices;
	double km, price;
	while(in.read_row(km,  price)){
			kms.push_back(km);
			prices.push_back(price);
	}
	auto model = LinearRegression(10000, 0.02);
	model.fit(kms, prices);
	std::cout << model.coef() << "\t" << model.intercept() << std::endl;
	std::cout << model.predict(240000) << std::endl;
	std::cout << "score: " << model.score(kms, prices);
	return 0;
}
