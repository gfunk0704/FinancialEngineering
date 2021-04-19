#pragma once

#include <option.h>

namespace FinancialEngineering
{
	class AmericanStyleOption : public Option
	{
	public:
		AmericanStyleOption(SharedPointer<Calendar>, Date, SmallNatural, SharedPointer<OptionPayoff>);
		DateArray exercie_date(Date) override;
	};
}