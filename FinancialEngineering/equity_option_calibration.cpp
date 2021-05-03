#include <equity_option_calibration.h>

namespace FinancialEngineering
{
	static Parameter to_black_scholes_parameter(const RealArray& value)
	{
		Parameter par;
		par["sigma"] = value(0);
		return par;
	}

	static Parameter to_heston_parameter(const RealArray& value)
	{
		Parameter par;
		par["v0"] = value(0);
		par["kappa"] = value(1);
		par["theta"] = value(2);
		par["sigma"] = value(3);
		par["rho"] = value(4);
		return par;
	}

	static Parameter to_uncertain_volatility_parameter(const RealArray& value)
	{
		Parameter par;
		par["sigma1"] = value(0);
		par["sigma2"] = value(1);
		par["lambda"] = value(2);
		return par;
	}

	EquityOptionObjectiveFunction::EquityOptionObjectiveFunction(SharedPointer<Evaluator> evaluator,
		OptionCollection col) :
		_evaluator(evaluator)
	{
		initialize_parameter_converter(evaluator->get_model()->model_type());
		_n_option = col.size();
		_portfolio = std::vector<SharedPointer<Option>>(_n_option);
		_premiums = RealArray(_n_option);
		for (Size i = 0; i < _n_option; i++)
		{
			_portfolio[i] = col[i].option();
			_premiums[i] = col[i].premium();
		}
	}

	void EquityOptionObjectiveFunction::initialize_parameter_converter(AssetModel::AssetModelType type)
	{
		switch (type)
		{
		case AssetModel::AssetModelType::BLACK_SCHOLES:
			_to_parameter = to_black_scholes_parameter;
			break;
		case AssetModel::AssetModelType::HESTON:
			_to_parameter = to_heston_parameter;
			break;
		case AssetModel::AssetModelType::UNCERTAIN_VOLATILITY:
			_to_parameter = to_uncertain_volatility_parameter;
			break;
		}
	}

	
}