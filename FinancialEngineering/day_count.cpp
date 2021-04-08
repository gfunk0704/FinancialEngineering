#include <day_count.h>
namespace FinancialEngineering
{
	YearFraction set_year_fraction(DayCountConvention convention)
	{
		switch (convention)
		{
		case DayCountConvention::ACT_360:
			return actual_360;
		case DayCountConvention::ACT_365_FIXED:
			return actual_365_fixed;
		}
	}

	Real actual_360(Date start_date,
		            Date end_date)
	{
		Real numerator = Real(end_date - start_date);
		return numerator / 360.0;
	}

	Real actual_365_fixed(Date start_date, 
		                  Date end_date)
	{
		Real numerator = Real(end_date - start_date);
		return numerator / 365.0;
	}
}