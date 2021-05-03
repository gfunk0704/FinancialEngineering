#include <cir.h>

namespace FinancialEngineering
{
	CirZcbClosedForm::CirZcbClosedForm(Date value_date,
					                   DayCountConvention day_count,
					                   RealArray par) :
		ZcbClosedForm(value_date, day_count),
		_x0(par(0))
	{
		_power = 2.0 * par(1) * par(2) / (par(3) * par(3));
		_h = std::sqrt(par(1) * par(1) + 2.0 * par(3) * par(3));
		_h2 = 2.0 * _h;
		_kappa_h = par(1) + _h;
	}

	Cir::Cir(Date initial_date, 
		     DayCountConvention day_count):
		ShortRateModel(initial_date, day_count)
	{}

	Cir::Cir(DayCountConvention day_count) :
		ShortRateModel(day_count)
	{}
}