#include <piecewise_constant.h>

namespace FinancialEngineering
{
	PiecewiseConstantCurve::PiecewiseConstantCurve(PointArray data): Curve(data)
	{
		set_cumulative_integral();
	}

	void PiecewiseConstantCurve::set_cumulative_integral()
	{
		_cumulative_integral = RealArray();
		Real lhs_time = 0.0;
		Real cumulative_value = 0.0;
		for (PointArray::iterator iter = _data.begin(); iter != _data.end(); iter++)
		{
			cumulative_value += (iter->time - lhs_time) * iter->value;
			lhs_time = iter->time;
			_cumulative_integral.push_back(cumulative_value);
		}
	}
}