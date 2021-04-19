#pragma once

#include <base.h>

namespace FinancialEngineering
{
	class OptionPayoff
	{
	public:
		enum class Type
		{
			CALL,
			PUT
		};

		OptionPayoff(OptionPayoff::Type);
		virtual RealArray exercise_payoff(RealArray) = 0;
		OptionPayoff::Type type();

	protected:
		OptionPayoff::Type _type;
	};

	inline OptionPayoff::Type OptionPayoff::type()
	{
		return _type;
	}

	class PlainVanillaPayoff : public OptionPayoff
	{
	public:
		PlainVanillaPayoff(OptionPayoff::Type, Real);
		virtual RealArray exercise_payoff(RealArray) override;
		Real strike();
	protected:
		Real _strike;
		Real _phi;
	};

	inline RealArray PlainVanillaPayoff::exercise_payoff(RealArray spot)
	{
		RealArray moneyness = (_phi * (spot - _strike)).max(0.0);
		return moneyness;
	}

	inline Real PlainVanillaPayoff::strike()
	{
		return _strike;
	}

	class WarrantPayoff : public PlainVanillaPayoff
	{
	public:
		WarrantPayoff(OptionPayoff::Type, Real, Real);
		RealArray exercise_payoff(RealArray) override;
		Real leverage();
	private:
		Real _leverage;
	};

	inline RealArray WarrantPayoff::exercise_payoff(RealArray spot)
	{
		return _leverage * PlainVanillaPayoff::exercise_payoff(spot);
	}

	inline Real WarrantPayoff::leverage()
	{
		return _leverage;
	}
}