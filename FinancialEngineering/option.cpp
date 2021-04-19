#include <option.h>

namespace FinancialEngineering
{
	Option::Option(SharedPointer<Calendar> calendar, 
				   Date expiry, 
				   SmallNatural delivery, 
		           SharedPointer<OptionPayoff> payoff):
				   Instrument(calendar, delivery),
				   _expiry(expiry),
				   _payoff(payoff)
	{}
}