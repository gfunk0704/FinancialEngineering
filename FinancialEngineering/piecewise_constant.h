#pragma once

#include <curve.h>

namespace FinancialEngineering
{
	class PiecewiseConstantCurve : public Curve
	{
	public:
		PiecewiseConstantCurve(PointArray);
	protected:
		Real interpolate(Real, PointArray::iterator) override;
		void set_cumulative_integral() override;
		Real integral_interpolate(Real, PointArray::iterator) override;
		Real lhs_extrapolation(Real) override;
		Real rhs_extrapolation(Real) override;
	};

	inline Real PiecewiseConstantCurve::interpolate(Real tau, 
		                                            PointArray::iterator rhs_iter)
	{
		return rhs_iter->value;
	}

	inline Real PiecewiseConstantCurve::integral_interpolate(Real tau, 
		                                                     PointArray::iterator rhs_iter)
	{
		std::size_t lhs_pos = std::distance(_data.begin(), rhs_iter);
		return _cumulative_integral[lhs_pos] + rhs_iter->value * (tau - _data[lhs_pos].time);
	}

	inline Real PiecewiseConstantCurve::lhs_extrapolation(Real tau)
	{
		return tau * _data[0].value;
	}

	inline Real PiecewiseConstantCurve::rhs_extrapolation(Real tau)
	{
		return _cumulative_integral.back() + (tau - _data.back().time) * _data.back().value;
	}
}

