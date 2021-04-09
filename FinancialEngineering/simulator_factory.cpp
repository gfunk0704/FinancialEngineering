#include <simulator_factory.h>

namespace FinancialEngineering
{
	SharedPointer<Simulator> simulator_factory(SharedPointer<AssetModel> model, SharedPointer<Rng32Bits> rng)
	{
		SharedPointer<Gaussian> gaussian_rng = SharedPointer<Gaussian>(new GaussianZiggurat(rng));
		switch (model->model_type())
		{
		case AssetModel::ModelType::BLACK_SCHOLES:
			return SharedPointer<Simulator>(new BlackScholesSimulator(model, gaussian_rng));
		case AssetModel::ModelType::HESTON:
			return SharedPointer<Simulator>(new HestonSimulator(model, gaussian_rng));
		case AssetModel::ModelType::UNCERTAIN_VOLATILITY:
			return SharedPointer<Simulator>(new UncertainVolatilitySimulator(model, gaussian_rng, SharedPointer<RealUniform>(new RealUniform32(rng))));
		}
	}
}