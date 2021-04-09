#pragma once

#include <american_style_option.h>

namespace FinancialEngineering
{
	class AmericanCallWarrant : public AmericanStyleOption
	{
	public:
		Real exercise_payoff(Real) override;
	private:
		Real _laverage;
	};

	inline Real AmericanCallWarrant::exercise_payoff(Real spot)
	{
		Real moneyness = spot - _strike;
		return (moneyness > 0.0) ? (_laverage * moneyness) : 0.0;
	}
}