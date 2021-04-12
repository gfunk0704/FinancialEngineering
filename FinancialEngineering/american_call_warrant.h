#pragma once

#include <instrument.h>
#include <option.h>
#include <american_style_option.h>

namespace FinancialEngineering
{
	class AmericanCallWarrant : public AmericanStyleOption
	{
	public:
		AmericanCallWarrant(SharedPointer<Calendar>, Date, SmallNatural, Real, Real);
		AmericanCallWarrant(SharedPointer<Calendar>, Date, SmallNatural, Real);
		Real exercise_payoff(Real) override;
	private:
		Real _leverage;
	};

	inline Real AmericanCallWarrant::exercise_payoff(Real spot)
	{
		Real moneyness = spot - _strike;
		return (moneyness > 0.0) ? (_leverage * moneyness) : 0.0;
	}
}