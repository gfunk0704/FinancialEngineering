#include <uncertain_volatility_simulator.h>

namespace FinancialEngineering
{
	UncertainVolatilitySimulator::UncertainVolatilitySimulator(SharedPointer<AssetModel> model,
		                                                       SharedPointer<Rng32Bits> rng) :
		Simulator(model, rng)
	{}

	void UncertainVolatilitySimulator::initialize(Date end_date)
	{
		Simulator::initialize(end_date);
		_random = generate_random_numbers(_n_step);
		_uniform_random = RealArray(GlobalVariable::get_simulation_path());
		for (RealArray::iterator iter = _uniform_random.begin(); iter != _uniform_random.end(); ++iter)
		{
			*iter = RealUniform::next_uniform(_rng);
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
		for (Size i = 0; i < n_sample; i++)
		{
			Real sigma =  _uniform_random[i] < lambda ? sigma1 : sigma2;
			drift_coef(i) = 0.5 * sigma * sigma;
			log_diffusion_coef(i) = sigma * sqrt_dt;
		}

		Size i = 0;
		for (SimulationSample::iterator iter = _random.begin(); iter != _random.end(); ++iter)
		{
			RealEigenArray log_drift = (_rt[i++] - drift_coef) * dt;
			sample.push_back(sample.back() * Eigen::exp(log_drift + log_diffusion_coef * (*iter)));
		}
		return sample;
	}

}