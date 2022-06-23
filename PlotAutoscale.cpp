#include "PlotAutoscale.hpp"


void PlotAutoscale::operator()(const std::vector<double>& y, const std::vector<double>& x, LinearRegression const  & model) {
	std::vector<double> y_pred;

	y_pred.reserve(y.size());
	_plt.Flush();
	std::transform(x.begin(), x.end(), y_pred.begin(), [=, &model](double value) {
		return model.predict(value);
	} );	
	_plt.Draw2D(plotcpp::Points(x.begin(), x.end(), y.begin(), "points"),
		  plotcpp::Lines(x.begin(), x.end(), y_pred.begin(), "linear"));
}
