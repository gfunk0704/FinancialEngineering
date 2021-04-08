#include <deposit_rate.h>

namespace FinancialEngineering
{
	DepositRateImpliedQuote::DepositRateImpliedQuote(Date value_date, 
		                                             Date fixing_date,
		                                             Date expiry_date,
		                                             YearFraction year_fraction) :
		_fixing_time(year_fraction(value_date, fixing_date)), 
		_expiry_time(year_fraction(value_date, expiry_date)), 
		_calculation_period(year_fraction(fixing_date, expiry_date))
	{}

	DepositRate::DepositRate(Date value_date,
		                     Period tenor,
		                     Real value, 
		                     DayCountConvention day_count,
		                     SharedPointer<Calendar> calendar, 
		                     SmallNatural spot_lag) :
		InterestRateQuote(value_date, value, day_count, calendar), 
		_tenor(tenor),
		_spot_lag(spot_lag)
	{}
}