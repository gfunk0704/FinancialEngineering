#pragma once

#include <instrument.h>

namespace FinancialEngineering
{
	class Option : public Instrument
	{
	public:
		Option(SharedPointer<Calendar>, Date, SmallNatural, Real);
		Date expiry();
		Real strike();
		virtual DateArray exercie_date(Date) = 0;
		virtual DateArray delivery_date(Date) = 0;
		virtual Real exercise_payoff(Real) = 0;

	protected:
		Real _strike;
		Date _expiry;
	};

	inline Date Option::expiry()
	{
		return _expiry;
	}

	inline Real Option::strike()
	{
		return _strike;
	}
}