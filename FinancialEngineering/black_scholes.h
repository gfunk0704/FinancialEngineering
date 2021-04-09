#pragma once

#include <asset_model.h>

namespace FinancialEngineering
{
	class BlackScholes : public AssetModel
	{
	public:
		BlackScholes(Date, Real, SharedPointer<NonparametricYieldTermStructure>);
		BlackScholes(Real, SharedPointer<NonparametricYieldTermStructure>);
		SmallNatural n_parameter() override;
		RealArray parameter_lower() override;
		RealArray parameter_upper() override;
		ModelType model_type() override;
	protected:
		//parameter order: sigma
		std::vector<std::string> parameter_name() override;
	};

	inline SmallNatural BlackScholes::n_parameter()
	{
		return 1;
	}

	inline RealArray BlackScholes::parameter_lower()
	{
		return RealArray{ sqrt_double_epsilon };
	}

	inline RealArray BlackScholes::parameter_upper()
	{
		return RealArray{ 1.0 };
	}

	inline std::vector<std::string> BlackScholes::parameter_name()
	{
		return std::vector<std::string>{"sigma"};
	}

	inline AssetModel::ModelType BlackScholes::model_type()
	{
		return ModelType::BLACK_SCHOLES;
	}
}
