#include <period.h>

namespace FinancialEngineering
{

	Period::Period(SmallInteger num, 
				   TimeUnit unit):
		_num(num),
		_unit(unit)
	{}

	Period days(SmallInteger num) 
	{
		return Period(num, Period::TimeUnit::DAYS);
	}

	Period weeks(SmallInteger num)
	{
		return Period(num, Period::TimeUnit::WEEKS);
	}

	Period months(SmallInteger num) 
	{
		return Period(num, Period::TimeUnit::MONTHS);
	}

	Period years(SmallInteger num) 
	{
		return Period(num, Period::TimeUnit::YEARS);
	}

	Date operator+(Date date, Period period)
	{
		SmallInteger num = period.num();

		switch (period.unit()) 
		{
		case Period::TimeUnit::DAYS:
			return date + boost::gregorian::days(num);
		case Period::TimeUnit::WEEKS:
			return date + boost::gregorian::weeks(num);
		case Period::TimeUnit::MONTHS:
			return date + boost::gregorian::months(num);
		case Period::TimeUnit::YEARS:
			return date + boost::gregorian::years(num);
		}
	}
	
}