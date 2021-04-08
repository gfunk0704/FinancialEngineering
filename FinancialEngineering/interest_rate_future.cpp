#include <interest_rate_future.h>

namespace FinancialEngineering
{
	InterestRateFuture::InterestRateFuture(Date value_date,
		                                   Date start_date, 
		                                   Date end_date,
		                                   Real value,
		                                   DayCountConvention day_count, 
		                                   SharedPointer<Calendar> calendar):
		InterestRateQuote(value_date, value, day_count, calendar),
		_start_date(start_date),
		_end_date(end_date)
	{}
}