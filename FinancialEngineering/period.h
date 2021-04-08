#pragma once

#include <date.h>

namespace FinancialEngineering 
{
	class Period 
	{
	public:
		enum class TimeUnit 
		{
			DAYS,
			WEEKS,
			MONTHS, 
			YEARS
		};

		Period(SmallInteger, TimeUnit);
		SmallNatural num();
		TimeUnit unit();
	private:
		SmallNatural _num;
		TimeUnit _unit;
	};

	inline SmallNatural Period::num() 
	{
		return _num;
	}

	inline Period::TimeUnit Period::unit() {
		return _unit;
	}

	Period days(SmallInteger num);
	Period weeks(SmallInteger num);
	Period months(SmallInteger num);
	Period years(SmallInteger num);
	Date operator+(Date, Period);

	inline Date operator-(Date date, 
		                  Period period)
	{
		return (date + Period(-period.num(), period.unit()));
	}
}