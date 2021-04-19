#include <calibration.h>

namespace FinancialEngineering
{
	static Parameter to_black_scholes_parameter(RealArray value)
	{
		Parameter par;
		par["sigma"] = value(0);
		return par;
	}

	static Parameter to_heston_parameter(RealArray value)
	{
		Parameter par;
		par["v0"] = value(0);
		par["kappa"] = value(1);
		par["theta"] = value(2);
		par["sigma"] = value(3);
		par["rho"] = value(4);
		return par;
	}

	static Parameter to_uncertain_volatility_parameter(RealArray value)
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

	Real EquityOptionObjectiveFunction::evaluate(RealArray par)
	{
		_evaluator->get_model()->set_parameter(_to_parameter(par));
		_evaluator->update();
		RealArray price_diff = _evaluator->evaluate(_portfolio) - _premiums;
		return (price_diff * price_diff / _premiums).mean();
	}	

	void EquityOptionObjectiveFunction::initialize_parameter_converter(AssetModel::ModelType type)
	{
		switch (type)
		{
		case AssetModel::ModelType::BLACK_SCHOLES:
			_to_parameter = to_black_scholes_parameter;
			break;
		case AssetModel::ModelType::HESTON:
			_to_parameter = to_heston_parameter;
			break;
		case AssetModel::ModelType::UNCERTAIN_VOLATILITY:
			_to_parameter = to_uncertain_volatility_parameter;
			break;
		}
	}

	CalibrationResult::CalibrationResult(OptimizationResult result1,
										 SharedPointer<AssetModel> model):
		result1(result1),
		model(model)
	{}
}