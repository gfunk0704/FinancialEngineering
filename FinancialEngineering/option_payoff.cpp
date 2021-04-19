#include <option_payoff.h>

namespace FinancialEngineering
{
	OptionPayoff::OptionPayoff(OptionPayoff::Type type):
		_type(type)
	{}

	PlainVanillaPayoff::PlainVanillaPayoff(OptionPayoff::Type type,
										   Real strike):
		OptionPayoff(type),
		_strike(strike),
		_phi((type == OptionPayoff::Type::CALL)? 1.0 : -1.0)
	{}

	WarrantPayoff::WarrantPayoff(OptionPayoff::Type type,
							     Real strike,
							     Real leverage):
		PlainVanillaPayoff(type, strike),
		_leverage(leverage)
	{}
}