#include "PlotAutoscale.hpp"

const bool persist_gnuplot_window = true;

void PlotAutoscale(const std::vector<double>& y, const std::vector<double>& x, LinearRegression const  & model) {
	const size_t n = 250;
	static plotcpp::Plot plt(persist_gnuplot_window);
	plt.SetTerminal("qt");
	plt.SetTitle("Sine");
	plt.SetXLabel("X");
	plt.SetYLabel("Y");
	plt.SetAutoscale();
	std::vector<double> y_pred;

	y_pred.reserve(y.size());
	//auto f = [&](double value) {model.predict( value);};
	
	std::transform(x.begin(), x.end(), y_pred.begin(), [=, &model](double value) {return model.predict(value);} );	
	plt.Draw2D(plotcpp::Points(x.begin(), x.end(), y.begin(), "points"),
		  plotcpp::Lines(x.begin(), x.end(), y_pred.begin(), "linear"));
	plt.Flush();
}
