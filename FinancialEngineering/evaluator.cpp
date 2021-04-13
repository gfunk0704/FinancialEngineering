#include <evaluator.h>

namespace FinancialEngineering
{
	Evaluator::Evaluator(SharedPointer<AssetModel> model):
		_model(model)
	{}
}