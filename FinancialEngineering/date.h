#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>

#include <base.h>

namespace FinancialEngineering 
{
	using Date = boost::gregorian::date;
	using DateArray = std::vector<Date>;
	using Year = SmallInteger;
	using Month = boost::gregorian::greg_month;
	using Day = SmallInteger;

	inline Integer operator-(Date date1, 
		                     Date date2)
	{
		return Integer(date1.modjulian_day() - date2.modjulian_day());
	}
}