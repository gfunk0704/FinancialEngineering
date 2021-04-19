#pragma once

#include <option.h>

namespace FinancialEngineering
{
	class EuropeanStyleOption : public Option
	{
	public:
		EuropeanStyleOption(SharedPointer<Calendar>, Date, SmallNatural, SharedPointer<OptionPayoff>);
		DateArray exercie_date(Date) override;
	};

	inline DateArray EuropeanStyleOption::exercie_date(Date value_date)
	{
		return DateArray{expiry()};
	}
}