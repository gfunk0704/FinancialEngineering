#include <short_rate_model.h>

namespace FinancialEngineering
{
	ZcbClosedForm::ZcbClosedForm(Date value_date, 
		                         DayCountConvention day_count):
		_value_date(value_date),
		_year_fraction(set_year_fraction(day_count))
	{}


	ShortRateModel::ShortRateModel(Date initial_date, 
								   DayCountConvention day_count):
		ParametricModel(initial_date),
		_day_count(day_count)
	{}

	ShortRateModel::ShortRateModel(DayCountConvention day_count) :
		ParametricModel(),
		_day_count(day_count)
	{}
}