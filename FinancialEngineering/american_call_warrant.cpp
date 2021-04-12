#include <american_call_warrant.h>

namespace FinancialEngineering
{
	AmericanCallWarrant::AmericanCallWarrant(SharedPointer<Calendar> calendar,
											 Date expiry,
											 SmallNatural delivery, 
											 Real strike,
											 Real leverage) :
		AmericanStyleOption(calendar, expiry, delivery, strike),
		_leverage(leverage)
	{}

	AmericanCallWarrant::AmericanCallWarrant(SharedPointer<Calendar> calendar,
											 Date expiry,
											 SmallNatural delivery,
											 Real strike) :
		AmericanCallWarrant(calendar, expiry, delivery, strike, 1.0)
	{}
}