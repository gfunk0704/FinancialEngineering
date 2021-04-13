#include <simulator_factory.h>

namespace FinancialEngineering
{
	SharedPointer<Simulator> simulator_factory (SharedPointer<AssetModel> model, SharedPointer<Rng32Bits> rng)
	{
		switch (model->model_type())
		{
		case AssetModel::ModelType::BLACK_SCHOLES:
			return SharedPointer<Simulator>(new BlackScholesSimulator(model, rng));
		case AssetModel::ModelType::HESTON:
			return SharedPointer<Simulator>(new HestonSimulator(model, rng));
		case AssetModel::ModelType::UNCERTAIN_VOLATILITY:
			return SharedPointer<Simulator>(new UncertainVolatilitySimulator(model, rng));
		}
	}
	
}