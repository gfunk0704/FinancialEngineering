#include <instrument.h>

namespace FinancialEngineering
{
	Instrument::Instrument(SharedPointer<Calendar> calendar,
						   SmallNatural delivery):
		_calendar(calendar),
		_delivery(delivery)
	{}
}