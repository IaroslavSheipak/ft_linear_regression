#include "csv.h"
#include "LinearRegression.hpp"
#include <fstream>
#include <string>

int main() {
	double price;	
	auto model = LinearRegression();
	double coef, intercept;

	std::ifstream coefs;
	coefs.open("coefs.txt");
	coefs >> intercept >> coef;
	model.set_intercept(intercept);
	model.set_coef(coef);
	std::cout << "Please input mileage" << std::endl;
	std::cin >> price;
	std::cout << model.predict(price) << std::endl;
	std::cout << model.coef() << "\t" << model.intercept() << std::endl;
	return (0);
}
