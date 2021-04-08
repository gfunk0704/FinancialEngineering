#include <black_scholes_simulator.h>

namespace FinancialEngineering
{
	BlackScholesSimulator::BlackScholesSimulator(SharedPointer<BlackScholes> model,
		                                         SharedPointer<Gaussian> gaussian_rng):
		Simulator(gaussian_rng, model->get_risk_free_rate()),
		_model(model)
	{}

	void BlackScholesSimulator::initialize(Date end_date)
	{
		_gaussian_rng->reset();
		_random = generate_random_numbers((Natural)(end_date - GlobalVariable::get_evaluation_date()));
	}

	SimulationSample BlackScholesSimulator::generate_sample()
	{
		Real tau = 0.0;
		Natural n_sample = GlobalVariable::get_simulation_path();
		SimulationSample sample{RealEigenArray::Constant(n_sample, _model->get_initial_value())};
		Real sigma = _model->get_parameter()["sigma"];
		Real drift_coef = 0.5 * sigma * sigma;
		Real log_diffusion_coef = sigma * sqrt_dt;
		YieldCurve yield_curve = _term_structure->to_yield_curve();
		for (SimulationSample::iterator iter = _random.begin(); iter != _random.end(); ++iter)
		{
			Real log_drift = (yield_curve.forward_rate(tau, tau + dt) - drift_coef);
			sample.push_back(sample.back() * Eigen::exp(log_drift + log_diffusion_coef * (*iter)));
			tau += dt;
		}
		return sample;
	}

}