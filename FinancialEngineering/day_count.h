#pragma once

#include <date.h>

namespace FinancialEngineering 
{
	enum class DayCountConvention 
	{
		ACT_360,
		ACT_365_FIXED
	};

	using YearFraction = Real(*)(Date, Date);
	YearFraction set_year_fraction(DayCountConvention);
	Real actual_360(Date, Date);
	Real actual_365_fixed(Date, Date);
}