#pragma once

#include <base.h>
#include <calendar.h>

namespace FinancialEngineering
{
	class Instrument
	{
	public:
		Instrument(SharedPointer<Calendar>, SmallNatural);
	protected:
		SharedPointer<Calendar> _calendar;
		SmallNatural _delivery;
	};
}