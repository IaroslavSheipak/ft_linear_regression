#include "csv.h"
#include "LinearRegression.hpp"
#include <fstream>
#include <string>
#include "matplotlibcpp.h"

int main(int ac, char **av) {
	if (ac != 3) {
		std::cout << "Input iterations and learning rate please." << std::endl;
		exit(1);
	}

	io::CSVReader<2> in("data/data.csv");
	in.read_header(io::ignore_extra_column, "km", "price");
	std::vector<double> kms, prices;
	double km, price;
	while(in.read_row(km,  price)){
			kms.push_back(km);
			prices.push_back(price);
	}
	auto model = LinearRegression(std::stoi(av[1]), std::stof(av[2]));
	model.fit(kms, prices);
	std::fstream coefs;
	coefs.open("coefs.txt");
	coefs << model.intercept() << " " << model.coef() << std::endl;
	return 0;
}
