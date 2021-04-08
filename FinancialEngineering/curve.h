#pragma once

#include <vector>

#include <day_count.h>

namespace FinancialEngineering
{
	
	struct Point
	{
	public:
		Point(Real, Real);
		Real time;
		Real value;
	};

	using PointArray = std::vector<Point>;

	class Curve
	{
	public:
		Curve(PointArray);
		Real evaluate(Real);
		Real integral(Real);
	protected:
		PointArray _data;
		RealArray _cumulative_integral;

		virtual void set_cumulative_integral() = 0;
		virtual Real lhs_extrapolation(Real) = 0;
		virtual Real rhs_extrapolation(Real) = 0;
		virtual Real interpolate(Real, PointArray::iterator) = 0;
		virtual Real integral_interpolate(Real, PointArray::iterator) = 0;
		PointArray::iterator find_rhs(Real);
	};

	inline PointArray::iterator Curve::find_rhs(Real tau)
	{
		return std::find_if(_data.begin(), _data.end(), [&tau](Point pt) {return (pt.time >= tau); });
	}

	
}

