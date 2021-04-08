#include <yield_curve.h>

namespace FinancialEngineering
{
	YieldCurve::YieldCurve(Date value_date,
					       YearFraction year_fraction,
		                   SharedPointer<Curve> curve):
		_value_date(value_date), 
		_year_fraction(year_fraction),
		_curve(curve)
	{}
}