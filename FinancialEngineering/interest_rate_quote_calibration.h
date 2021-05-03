#pragma once

#include <calibration_result.h>
#include <jde.h>
#include <interest_rate_quote.h>

namespace FinancialEngineering
{
	class IrateQuoteObjectiveFunction : public ObjectiveFunction
	{
	public:
		IrateQuoteObjectiveFunction(SharedPointer<ShortRateModel>, InterestRateQuoteCollection);
		Real evaluate(const RealArray&) override;
	private:
		SharedPointer<ShortRateModel> _model;
		ToParameter _to_parameter;

		void initialize_parameter_converter(ShortRateModel::ShortRateModelType);
	};
}