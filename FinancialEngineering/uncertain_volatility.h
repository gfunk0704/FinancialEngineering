#pragma once

#include <asset_model.h>

namespace FinancialEngineering
{
	class UncertainVolatility : public AssetModel
	{
	public:
		UncertainVolatility(Date, Real, SharedPointer<NonparametricYieldTermStructure>);
		UncertainVolatility(Real, SharedPointer<NonparametricYieldTermStructure>);
		SmallNatural n_parameter() override;
		RealArray parameter_lower() override;
		RealArray parameter_upper() override;
		ModelType model_type() override;
	protected:
		//parameter order: sigma1, sigma2, lambda
		std::vector<std::string> parameter_name() override;
	};

	inline SmallNatural UncertainVolatility::n_parameter()
	{
		return 3;
	}

	inline RealArray UncertainVolatility::parameter_lower()
	{
		return RealArray::Constant(3, sqrt_double_epsilon);
	}

	inline RealArray UncertainVolatility::parameter_upper()
	{
		return RealArray::Constant(3, 1.0);
	}

	inline std::vector<std::string> UncertainVolatility::parameter_name()
	{
		return std::vector<std::string>{"sigma1", "sigma2", "lambda"};
	}

	inline AssetModel::ModelType UncertainVolatility::model_type()
	{
		return ModelType::UNCERTAIN_VOLATILITY;
	}
}