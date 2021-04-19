#include <european_style_option.h>

namespace FinancialEngineering
{
	EuropeanStyleOption::EuropeanStyleOption(SharedPointer<Calendar> calendar,
											 Date expiry,
											 SmallNatural delivery,
											 SharedPointer<OptionPayoff> payoff) :
		Option(calendar, expiry, delivery, payoff)
	{}

}