#pragma once

#include <nonparametric_yield_term_structure.h>
#include <gaussian.h>
namespace FinancialEngineering
{
	using Parameter = std::map<std::string, Real>;
	const Real sqrt_double_epsilon = std::sqrt(std::numeric_limits<Real>::epsilon());
	class AssetModel
	{
	public:
		enum class ModelType
		{
			BLACK_SCHOLES,
			HESTON,
			UNCERTAIN_VOLATILITY
		};

		AssetModel(Date, Real, SharedPointer<NonparametricYieldTermStructure>);
		AssetModel(Real, SharedPointer<NonparametricYieldTermStructure>);
		Date get_initial_date();
		Real get_initial_value();
		SharedPointer<NonparametricYieldTermStructure> get_risk_free_rate();
		virtual SmallNatural n_parameter() = 0;
		void set_parameter(Parameter);
		Parameter get_parameter();
		virtual ModelType model_type() = 0;
		virtual RealArray parameter_lower() = 0;
		virtual RealArray parameter_upper() = 0;
	protected:
		Date _initial_date;
		Real _initial_value;
		RealArray _parameter;
		SharedPointer<NonparametricYieldTermStructure> _term_structure;
		virtual std::vector<std::string> parameter_name() = 0;
	};

	inline Date AssetModel::get_initial_date()
	{
		return _initial_date;
	}

	inline Real AssetModel::get_initial_value()
	{
		return _initial_value;
	}

	inline SharedPointer<NonparametricYieldTermStructure> AssetModel::get_risk_free_rate()
	{
		return _term_structure;
	}
}