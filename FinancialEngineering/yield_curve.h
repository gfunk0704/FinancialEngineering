#pragma once

#include <cmath>

#include <curve.h>
#include <day_count.h>

namespace FinancialEngineering 
{
	class YieldCurve 
	{
	public:
		YieldCurve(Date, YearFraction, SharedPointer<Curve>);
		Real discount_factor(Real);
		Real discount_factor(Date);
		Real forward_rate(Real);
		Real forward_rate(Date);
		Real forward_rate(Real, Real);
		Real forward_rate(Date, Date);
		Real zero_rate(Real);
		Real zero_rate(Date);

	protected:
		SharedPointer<Curve> _curve;
		Date _value_date;
		YearFraction _year_fraction;
	};

	inline Real YieldCurve::discount_factor(Real tau)
	{
		return std::exp(-_curve->integral(tau));
	}

	inline Real YieldCurve::discount_factor(Date date)
	{
		return discount_factor(_year_fraction(_value_date, date));
	}

	inline Real YieldCurve::forward_rate(Real tau)
	{
		return _curve->evaluate(tau);
	}

	inline Real YieldCurve::forward_rate(Date date)
	{
		return forward_rate(_year_fraction(_value_date, date));
	}

	inline Real YieldCurve::forward_rate(Real start_time, 
		                                 Real end_time)
	{
		return (std::log(discount_factor(start_time)) - std::log(discount_factor(end_time))) / (end_time - start_time);
	}

	inline Real YieldCurve::forward_rate(Date start_date, 
		                                 Date end_date)
	{
		return forward_rate(_year_fraction(_value_date, start_date), _year_fraction(_value_date, end_date));
	}

	inline Real YieldCurve::zero_rate(Real tau)
	{
		return _curve->integral(tau) / tau;
	}

	inline Real YieldCurve::zero_rate(Date date)
	{
		return zero_rate(_year_fraction(_value_date, date));
	}
}

