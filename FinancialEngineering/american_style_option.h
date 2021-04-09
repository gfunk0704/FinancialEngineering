#pragma once

#include <option.h>

namespace FinancialEngineering
{
	class AmericanStyleOption : public Option
	{
	public:
		AmericanStyleOption(SharedPointer<Calendar>, Date, SmallNatural, Real);
		DateArray exercie_date(Date) override;
		DateArray delivery_date(Date) override;
	};

	inline DateArray AmericanStyleOption::delivery_date(Date value_date)
	{
		DateArray dates = exercie_date(value_date);
		for (DateArray::iterator iter = dates.begin(); iter != dates.end(); ++iter)
		{
			*iter = _calendar->next_n_business_day(*iter, _delivery);
		}
		return dates;
	}
}