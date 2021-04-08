#include <interest_rate_quote.h>

namespace FinancialEngineering
{
	InterestRateQuote::InterestRateQuote(Date value_date,
		                                 Real value, 
		                                 DayCountConvention day_count,
		                                 SharedPointer<Calendar> calendar):
		Quote(value_date, value, calendar), 
		_day_count(day_count)
	{}
}