#include "Q_function.hpp"
#include <cmath>
//calculates if the car is within accepted range of the road
double Q_value(std::vector<double> sensor_data, double car_v)
{
	double accepted_range = 0.6;
	int n = 1;
	double sum = 0;
	auto i = sensor_data.begin();
	for (; (i!= sensor_data.end())&&(i+1 != sensor_data.end()); i++++)
	{
		double a = double(*i);
		double b = double(*(i + 1));
        sum += std::abs(a - b) / (a + b)==0?1:(a+b);
		n++;
	}
	double Q = (accepted_range - sum / n)*car_v;
	return Q;
}
