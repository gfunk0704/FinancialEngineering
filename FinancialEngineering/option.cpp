#include <option.h>

namespace FinancialEngineering
{
	Option::Option(SharedPointer<Calendar> calendar, 
				   Date expiry, 
				   SmallNatural 
				   delivery, Real strike):
				   Instrument(calendar, delivery),
				   _expiry(expiry),
				   _strike(strike)
	{}
}