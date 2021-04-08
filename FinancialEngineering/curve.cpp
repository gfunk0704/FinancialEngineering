#include <curve.h>

namespace FinancialEngineering 
{
	Point::Point(Real time, 
		         Real value)
	{
		this->time = time;
		this->value = value;
	}

	Curve::Curve(PointArray data):_data(data)
	{}

	Real Curve::evaluate(Real tau) 
	{
		if (tau <= _data[0].time)
		{
			return _data[0].value;
		} 
		else if (tau >= _data.back().time)
		{
			return _data.back().value;
		} 

		return interpolate(tau, find_rhs(tau));
	}

	Real Curve::integral(Real tau)
	{
		if (tau <= _data[0].time)
		{
			return lhs_extrapolation(tau);
		}
		else if (tau >= _data.back().time)
		{
			return rhs_extrapolation(tau);
		}

		return integral_interpolate(tau, find_rhs(tau));
	}
}