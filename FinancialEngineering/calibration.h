#pragma once

#include <evaluator.h>
#include <optimization.h>
#include <jde.h>
#include <equity_option_quote.h>

namespace FinancialEngineering
{
	using OptionCollection = std::vector<EquityOptionQuote>;
	using ToParameter = Parameter(*)(RealArray);
	class EquityOptionObjectiveFunction : public ObjectiveFunction
	{
	public:
		EquityOptionObjectiveFunction(SharedPointer<Evaluator>, OptionCollection);
		Real evaluate(RealArray) override;
	private:
		Date _end_date;
		SharedPointer<Evaluator> _evaluator;
		std::vector<SharedPointer<Option>> _portfolio;
		RealArray _premiums;
		Size _n_option;
		ToParameter _to_parameter;

		void initialize_parameter_converter(AssetModel::ModelType);
	};

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
