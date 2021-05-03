#pragma once

#include <parametric_model.h>
#include <nonparametric_yield_term_structure.h>

namespace FinancialEngineering
{
	
	class AssetModel : public ParametricModel
	{
	public:
		enum class AssetModelType
		{
			BLACK_SCHOLES,
			HESTON,
			UNCERTAIN_VOLATILITY
		};

		AssetModel(Date, Real, SharedPointer<NonparametricYieldTermStructure>);
		AssetModel(Real, SharedPointer<NonparametricYieldTermStructure>);
		Real get_initial_value() override;
		SharedPointer<NonparametricYieldTermStructure> get_risk_free_rate();
		virtual AssetModelType model_type() = 0;
	protected:
		Real _initial_value;
		SharedPointer<NonparametricYieldTermStructure> _term_structure;
	};

	inline Real AssetModel::get_initial_value()
	{
		return _initial_value;
	}

	inline SharedPointer<NonparametricYieldTermStructure> AssetModel::get_risk_free_rate()
	{
		return _term_structure;
	}
}