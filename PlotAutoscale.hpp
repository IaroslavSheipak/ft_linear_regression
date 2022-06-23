#pragma once
#include "plot.h"
#include "LinearRegression.hpp"

class PlotAutoscale {
	public:
		PlotAutoscale(const std::vector<double>& y, const std::vector<double>& x)  {
			_plt.SetTerminal("qt");
			_plt.SetTitle("LinearRegression");
			_plt.SetXLabel("X");
			_plt.SetYLabel("Y");
			_plt.SetAutoscale();
			_plt.Draw2D(plotcpp::Points(x.begin(), x.end(), y.begin(), "points"));
		};
		~PlotAutoscale() {_plt.Flush();};
		PlotAutoscale(PlotAutoscale & src)=delete;
		PlotAutoscale operator=(PlotAutoscale & src)=delete;

		void operator()(const std::vector<double>& y, const std::vector<double>& x, LinearRegression const  & model);

	private:
		plotcpp::Plot _plt=plotcpp::Plot(true);
};
