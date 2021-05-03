#pragma once

#include <evaluator.h>
#include <optimization.h>

namespace FinancialEngineering
{
	using ToParameter = Parameter(*)(const RealArray&);

	struct CalibrationResult
	{
		CalibrationResult(OptimizationResult, SharedPointer<AssetModel>);
		OptimizationResult result;
		SharedPointer<AssetModel> model;
	};
}