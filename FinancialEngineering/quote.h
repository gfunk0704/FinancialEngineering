#pragma once

#include <calendar.h>
#include <period.h>
#include <global_variable.h>

namespace FinancialEngineering
{
	class Quote 
	{
	public:
		Quote(Date, Real, SharedPointer<Calendar>);
		Quote(Real, SharedPointer<Calendar>);
		Real value();
	protected:
		SharedPointer<Calendar> _calendar;
		Date _value_date;
		Real _value;
	};

	inline Real Quote::value()
	{
		return _value;
	}
}

