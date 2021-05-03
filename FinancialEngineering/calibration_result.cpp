#include <calibration_result.h>

namespace FinancialEngineering
{
	CalibrationResult::CalibrationResult(OptimizationResult result,
									     SharedPointer<AssetModel> model) :
		result(result),
		model(model)
	{}
}