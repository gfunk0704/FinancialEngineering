#include <black_scholes_simulator.h>

namespace FinancialEngineering
{
	BlackScholesSimulator::BlackScholesSimulator(SharedPointer<AssetModel> model,
		                                         SharedPointer<Rng32Bits> rng):
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
		SimulationSample sample{RealEigenArray::Constant(n_sample, _model->get_initial_value())};
		Real sigma = _model->get_parameter()["sigma"];
		Real drift_coef = 0.5 * sigma * sigma;
		Real log_diffusion_coef = sigma * sqrt_dt;
		Size i = 0;
		for (SimulationSample::iterator iter = _random.begin(); iter != _random.end(); ++iter)
		{
			Real log_drift = (_rt[i++] - drift_coef) * dt;
			sample.push_back(sample.back() * Eigen::exp(log_drift * dt + log_diffusion_coef * (*iter)));
		}
		return sample;
	}

}