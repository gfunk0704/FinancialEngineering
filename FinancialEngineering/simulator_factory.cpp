#include <simulator_factory.h>

namespace FinancialEngineering
{
	SharedPointer<Simulator> simulator_factory (SharedPointer<AssetModel> model, bool antithetic_variates)
	{
		SharedPointer<Rng32Bits> rng = GlobalVariable::get_rng();
		switch (model->model_type())
		{
		case AssetModel::AssetModelType::BLACK_SCHOLES:
			return SharedPointer<Simulator>(new BlackScholesSimulator(model, rng, antithetic_variates));
		case AssetModel::AssetModelType::HESTON:
			return SharedPointer<Simulator>(new HestonSimulator(model, rng, antithetic_variates));
		case AssetModel::AssetModelType::UNCERTAIN_VOLATILITY:
			return SharedPointer<Simulator>(new UncertainVolatilitySimulator(model, rng, antithetic_variates));
		}
	}
	
}