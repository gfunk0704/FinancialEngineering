#include <uncertain_volatility_simulator.h>

namespace FinancialEngineering
{
	UncertainVolatilitySimulator::UncertainVolatilitySimulator(SharedPointer<AssetModel> model,
		                                                       SharedPointer<Rng32Bits> rng,
															   bool antithetic_variates) :
		Simulator(model, rng, antithetic_variates)
	{}

	UncertainVolatilitySimulator::UncertainVolatilitySimulator(SharedPointer<AssetModel> model,
															   SharedPointer<Rng32Bits> rng) :
		Simulator(model, rng)
	{}

	void UncertainVolatilitySimulator::initialize(Date end_date)
	{
		Simulator::initialize(end_date);
		_random = generate_random_numbers(_n_step);
		Natural n_sample = GlobalVariable::get_simulation_path();
		_uniform_random = RealArray(n_sample);

		if (_antithetic_variates)
		{
			RealArray sub_uniform = Uniform::next_real_uniform(_rng, n_sample / 2);
			_uniform_random << sub_uniform, sub_uniform;
		}
		else
		{
			_uniform_random << Uniform::next_real_uniform(_rng, n_sample);
		}
		
	}

	SimulationSample UncertainVolatilitySimulator::generate_sample()
	{
		Real tau = 0.0;
		Natural n_sample = GlobalVariable::get_simulation_path();
		SimulationSample sample{ RealArray::Constant(n_sample, _model->get_initial_value()) };
		Parameter par = _model->get_parameter();
		Real sigma1 = par["sigma1"];
		Real sigma2 = par["sigma2"];
		Real lambda = par["lambda"];
		RealArray drift_coef(n_sample);
		RealArray log_diffusion_coef(n_sample);
		for (Size i = 0; i < n_sample; i++)
		{
			Real sigma =  (_uniform_random(i) < lambda) ? sigma1 : sigma2;
			drift_coef(i) = 0.5 * sigma * sigma;
			log_diffusion_coef(i) = sigma * sqrt_dt;
		}

		for (Size i = 0; i < _n_step; i++)
		{
			sample.col(i + 1) = sample.col(i) * ((_rt(i) - drift_coef) * dt + log_diffusion_coef * _random.col(i)).exp();
		}
		
		return sample;
	}

}