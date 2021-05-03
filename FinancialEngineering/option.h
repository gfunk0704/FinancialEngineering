#pragma once

#include <instrument.h>
#include <option_payoff.h>

namespace FinancialEngineering
{
	class Option : public Instrument
	{
	public:
		Option(SharedPointer<Calendar>, Date, SmallNatural, SharedPointer<OptionPayoff>);
		Date expiry();
		RealArray exercise_payoff(RealArray);
		virtual DateArray exercie_date(Date) = 0;
		DateArray delivery_date(Date);

	protected:
		Date _expiry;
		SharedPointer<OptionPayoff> _payoff;
	};

	inline Date Option::expiry()
	{
		return _expiry;
	}

	inline DateArray Option::delivery_date(Date value_date)
	{
		DateArray dates = exercie_date(value_date);
		for (DateArray::iterator iter = dates.begin(); iter != dates.end(); ++iter)
		{
			*iter = _calendar->next_n_business_day(*iter, _delivery);
		}
		return dates;
	}

	inline RealArray Option::exercise_payoff(RealArray spot)
	{
		return _payoff->exercise_payoff(spot);
	}
}