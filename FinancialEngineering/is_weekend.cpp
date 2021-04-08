#include <is_weekend.h>

namespace FinancialEngineering
{
	bool is_weekend(Date& date)
	{
		return (date.day_of_week() == boost::gregorian::Saturday || date.day_of_week() == boost::gregorian::Sunday);
	}
}