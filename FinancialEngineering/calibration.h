#pragma once

#include <evaluator.h>
#include <optimization.h>
#include <jde.h>
#include <equity_option_quote.h>

namespace FinancialEngineering
{
	using OptionCollection = std::vector<EquityOptionQuote>;
	using ToParameter = Parameter(*)(const RealArray&);
	class EquityOptionObjectiveFunction : public ObjectiveFunction
	{
	public:
		EquityOptionObjectiveFunction(SharedPointer<Evaluator>, OptionCollection);
		Real evaluate(const RealArray&) override;
	private:
		Date _end_date;
		SharedPointer<Evaluator> _evaluator;
		std::vector<SharedPointer<Option>> _portfolio;
		RealArray _premiums;
		Size _n_option;
		ToParameter _to_parameter;

		void initialize_parameter_converter(AssetModel::ModelType);
	};

	inline Real EquityOptionObjectiveFunction::evaluate(const RealArray& par)
	{
		_evaluator->get_model()->set_parameter(_to_parameter(par));
		_evaluator->update();
		RealArray price_diff = _evaluator->evaluate(_portfolio) - _premiums;
		return (price_diff * price_diff / _premiums).mean();
	}

	struct CalibrationResult
	{
		CalibrationResult(OptimizationResult, SharedPointer<AssetModel>);
		OptimizationResult result1;
		SharedPointer<AssetModel> model;
	};

	inline CalibrationResult calibrate(SharedPointer<Evaluator> evaluator, OptionCollection col)
	{
		SharedPointer<AssetModel> model = evaluator->get_model();
		SharedPointer<ObjectiveFunction> func = SharedPointer<ObjectiveFunction>(new EquityOptionObjectiveFunction(evaluator, col));
		RealArray lower = model->parameter_lower();
		RealArray upper = model->parameter_upper();
		OptimizationResult result = Jde().optimize(func, lower, upper);
		return CalibrationResult(result, model);
	}
}
