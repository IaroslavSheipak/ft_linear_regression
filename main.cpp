#include "csv.h"
#include <cmath>
#include <vector>
#include <iostream>
#include "LinearRegression.hpp"
#include "plot.h"
#include "utils.h"

const bool persist_gnuplot_window = true;
const size_t n = 250;
double g_mag = 0.;


void PlotAutoscale(const std::vector<double>& y, const std::vector<double>& x, std::vector<double> & linear_rg, std::vector<double> & linear_y) {
  using namespace plotcpp;

  Plot plt(persist_gnuplot_window);
  plt.SetTerminal("qt");
  plt.SetTitle("Sine");
  plt.SetXLabel("X");
  plt.SetYLabel("Y");
  plt.SetAutoscale();

  plt.Draw2D(Points(x.begin(), x.end(), y.begin(), "points"), 
		  Lines(linear_rg.begin(), linear_rg.end(), linear_y.begin(), "linear"));

  //plt.Flush();
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
	auto model = LinearRegression(100000, 0.02);
	model.fit(kms, prices);
	std::cout << model.coef() << "\t" << model.intercept() << std::endl;
	std::cout << model.predict(240000);
	return 0;
}
