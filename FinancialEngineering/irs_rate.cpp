#include <irs_rate.h>

namespace FinancialEngineering
{
	IrsRateImpliedQuote::IrsRateImpliedQuote(Date value_date, 
		                                     DateArray schedule, 
		                                     YearFraction year_fraction)
	{
		_tau = RealArray(schedule.size());
		_time_schedule = RealArray(schedule.size());
		_time_schedule[0] = year_fraction(value_date, schedule[0]);
		Real dominator = 0.0;
		for (Size i = 1; i < _time_schedule.size(); i++)
		{
			_time_schedule[i] = year_fraction(value_date, schedule[i]);
			_tau[i - 1] = _time_schedule[i] - _time_schedule[i - 1];
		}
	}

	Real IrsRateImpliedQuote::evaluate(NonparametricYieldTermStructure term_structure)
	{
		YieldCurve yield_curve = term_structure.to_yield_curve();
		RealArray zcb_price(_time_schedule.size());
		std::transform(_time_schedule.begin(), _time_schedule.end(), zcb_price.begin(), [&yield_curve](Real time) {return yield_curve.discount_factor(time); });
		Real numerator = zcb_price[0] - zcb_price.back();
		Real dominator = 0.0;
		for (Size i = 1; i < zcb_price.size(); i++)
		{
			dominator += zcb_price[i] * _tau[i - 1];
		}
		return dominator / numerator;
	}

	IrsRate::IrsRate(Date value_date, 
		             Period tenor, 
		             Period period, 
		             Real value,
		             DayCountConvention day_count,
		             SharedPointer<Calendar> calendar, 
		             SmallNatural spot_lag):
		DepositRate(value_date, tenor, value, day_count, calendar, spot_lag), 
		_period(period)
	{}

	inline SharedPointer<InterestRateImpliedQuote> IrsRate::implied_quote()
	{
		Date expiry = expiry_date();
		DateArray schedule{_value_date + _period};
		while (schedule.back() < expiry)
		{
			Date next_date = schedule.back() + _period;
			if (next_date <= expiry)
				schedule.push_back(next_date);
			if (next_date > expiry)
				break;
		}
		return SharedPointer<InterestRateImpliedQuote>(new IrsRateImpliedQuote(_value_date, schedule, set_year_fraction(_day_count)));
	}

}