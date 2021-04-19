#include <black_scholes_simulator.h>

namespace FinancialEngineering
{
	BlackScholesSimulator::BlackScholesSimulator(SharedPointer<AssetModel> model,
		                                         SharedPointer<Rng32Bits> rng,
												 bool antithetic_variates):
		Simulator(model, rng, antithetic_variates)
	{}

	BlackScholesSimulator::BlackScholesSimulator(SharedPointer<AssetModel> model,
		SharedPointer<Rng32Bits> rng) :
		Simulator(model, rng)
	{}

	void BlackScholesSimulator::initialize(Date end_date)
	{
		Simulator::initialize(end_date);
		_random = generate_random_numbers(_n_step);
	}

	SimulationSample BlackScholesSimulator::generate_sample()
	{
		Real tau = 0.0;
		Natural n_sample = GlobalVariable::get_simulation_path();
		SimulationSample sample(n_sample, _n_step + 1);
		sample.col(0).fill(_model->get_initial_value());
		Real sigma = _model->get_parameter()["sigma"];
		Real drift_coef = 0.5 * sigma * sigma;
		Real log_diffusion_coef = sigma * sqrt_dt;
		for (Size i = 0; i < _n_step; i++)
		{
			sample.col(i + 1) = sample.col(i) * ((_rt(i) - drift_coef) * dt + +log_diffusion_coef * _random.col(i)).exp();
		}
		return sample;
	}

}