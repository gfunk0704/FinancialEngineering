#include <simulator.h>

namespace FinancialEngineering
{
	Simulator::Simulator(SharedPointer<AssetModel> model,
						 SharedPointer<Gaussian> gaussian_rng):
		_model(model),
		_gaussian_rng(gaussian_rng),
		_n_step(0)
	{}

	void Simulator::initialize(Date end_date)
	{
		_gaussian_rng->reset();
		_n_step = (Natural)(end_date - GlobalVariable::get_evaluation_date());
		_rt = RealArray();
		Real tau = 0.0;
		YieldCurve yield_curve = _model->get_risk_free_rate()->to_yield_curve();
		for (Size i = 0; i < _n_step; i++)
		{
			_rt.push_back(yield_curve.forward_rate(tau, tau + dt));
			tau += dt;
		}
	}

	SimulationSample Simulator::generate_random_numbers(Natural step)
	{
		Natural n_sample = GlobalVariable::get_simulation_path();
		SimulationSample random;
		while (step > 0)
		{
			RealEigenArray step_random(n_sample);
			for (Size i = 0; i < n_sample; i++)
			{
				step_random(i) = _gaussian_rng->next_gaussian();
			}
			random.push_back(step_random);
			--step;
		}
		return random;
	}
}