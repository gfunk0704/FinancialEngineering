#pragma once

#include <asset_model.h>

namespace FinancialEngineering
{
	class Heston : public AssetModel
	{
	public:
		Heston(Date, Real, SharedPointer<NonparametricYieldTermStructure>);
		Heston(Real, SharedPointer<NonparametricYieldTermStructure>);
		virtual SmallNatural n_parameter() override;
		virtual RealArray parameter_lower() override;
		virtual RealArray parameter_upper() override;
		ModelType model_type() override;
	protected:
		//parameter order: v0, kappa, theta, sigma, rho
		virtual std::vector<std::string> parameter_name() override;
	};

	inline SmallNatural Heston::n_parameter()
	{
		return 5;
	}

	inline RealArray Heston::parameter_lower()
	{
		RealArray par(5);
		par << sqrt_double_epsilon, sqrt_double_epsilon, sqrt_double_epsilon, sqrt_double_epsilon, -1.0;
		return par;
	}

	inline RealArray Heston::parameter_upper()
	{
		RealArray par(5);
		par << 1.0, 3.0, 1.0, 1.0, 1.0;
		return par;
	}

	inline std::vector<std::string> Heston::parameter_name()
	{
		return std::vector<std::string>{"v0", "kappa", "theta", "sigma", "rho"};
	}

	inline AssetModel::ModelType Heston::model_type()
	{
		return ModelType::HESTON;
	}
}