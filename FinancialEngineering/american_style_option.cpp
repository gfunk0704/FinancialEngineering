#include <american_style_option.h>

namespace FinancialEngineering
{
	AmericanStyleOption::AmericanStyleOption(SharedPointer<Calendar> calendar,
										   	 Date expiry,
											 SmallNatural delivery,
											 SharedPointer<OptionPayoff> payoff) :
		Option(calendar, expiry, delivery, payoff)
	{}

	DateArray AmericanStyleOption::exercie_date(Date value_date)
	{
		if (value_date > _expiry)
			return DateArray();

		DateArray dates{ value_date };
		while (dates.back() < _expiry)
		{
			dates.push_back(_calendar->next_n_business_day(dates.back(), 1));
		}
		return dates;
	}
}