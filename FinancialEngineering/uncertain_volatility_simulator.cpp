#include <uncertain_volatility_simulator.h>

namespace FinancialEngineering
{
	UncertainVolatilitySimulator::UncertainVolatilitySimulator(SharedPointer<UncertainVolatility> model, 
		                                                       SharedPointer<Gaussian> gaussian_rng,
		                                                       SharedPointer<RealUniform> uniform_rng) :
		Simulator(gaussian_rng, model->get_risk_free_rate()), 
		_model(model), 
		_uniform_rng(uniform_rng)
	{}

	void UncertainVolatilitySimulator::initialize(Date end_date)
	{
		_gaussian_rng->reset();
		_uniform_rng.reset();
		_random = generate_random_numbers((Natural)(end_date - GlobalVariable::get_evaluation_date()));
		_uniform_random = RealArray(GlobalVariable::get_simulation_path());
		for (RealArray::iterator iter = _uniform_random.begin(); iter != _uniform_random.end(); ++iter)
		{
			*iter = _uniform_rng->next_uniform();
		}
	}

	SimulationSample UncertainVolatilitySimulator::generate_sample()
	{
		Real tau = 0.0;
		Natural n_sample = GlobalVariable::get_simulation_path();
		SimulationSample sample{ RealEigenArray::Constant(n_sample, _model->get_initial_value()) };
		Parameter par = _model->get_parameter();
		Real sigma1 = par["sigma1"];
		Real sigma2 = par["sigma2"];
		Real lambda = par["lambda"];
		RealEigenArray drift_coef(n_sample);
		RealEigenArray log_diffusion_coef(n_sample);
		YieldCurve yield_curve = _term_structure->to_yield_curve();
		for (Size i = 0; i < n_sample; i++)
		{
			Real sigma = lambda < _uniform_random[i] ? sigma1 : sigma2;
			drift_coef(i) = 0.5 * sigma * sigma;
			log_diffusion_coef(i) = sigma * sqrt_dt;
		}

		for (SimulationSample::iterator iter = _random.begin(); iter != _random.end(); ++iter)
		{
			RealEigenArray log_drift = (yield_curve.forward_rate(tau, tau + dt) - drift_coef);
			sample.push_back(sample.back() * Eigen::exp(log_drift + log_diffusion_coef * (*iter)));
			tau += dt;
		}
		return sample;
	}

}