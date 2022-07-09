#include "csv.h"
#include "LinearRegression.hpp"
#include <fstream>
#include <string>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main() {
	double mileage;	
	auto model = LinearRegression();
	double coef, intercept;

	io::CSVReader<2> in("data/data.csv");
	in.read_header(io::ignore_extra_column, "km", "price");
	std::vector<double> kms, prices;
	double km, price;
	while(in.read_row(km,  price)){
			kms.push_back(km);
			prices.push_back(price);
	}
	std::ifstream coefs;
	coefs.open("coefs.txt");
	coefs >> intercept >> coef;
	model.set_intercept(intercept);
	model.set_coef(coef);
	std::cout << "Please input mileage" << std::endl;
	std::cin >> mileage;
	std::cout << model.predict(mileage) << std::endl;
	std::cout << model.coef() << "\t" << model.intercept() << std::endl;
	plt::scatter(kms, prices, 10.);
	plt::scatter(std::vector<double>(1, mileage), 
					std::vector<double>(1, model.predict(mileage)), 
						10., 
							{{"color", "purple"}});
	plt::show();
	return (0);
}
