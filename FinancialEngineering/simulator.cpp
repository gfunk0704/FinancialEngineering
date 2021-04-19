#include <simulator.h>

namespace FinancialEngineering
{
	Simulator::Simulator(SharedPointer<AssetModel> model,
						 SharedPointer<Rng32Bits> rng,
						 bool antithetic_variates):
		_model(model),
		_rng(rng),
		_antithetic_variates(antithetic_variates),
		_n_step(0)
	{}

	Simulator::Simulator(SharedPointer<AssetModel> model,
						 SharedPointer<Rng32Bits> rng):
		Simulator(model, rng, true)
	{}

	void Simulator::initialize(Date end_date)
	{
		_rng->reset();
		_n_step = (Natural)(end_date - GlobalVariable::get_evaluation_date());
		_rt = RealArray(_n_step);
		Real tau = 0.0;
		YieldCurve yield_curve = _model->get_risk_free_rate()->to_yield_curve();
		for (Size i = 0; i < _n_step; i++)
		{
			_rt(i) = (yield_curve.forward_rate(tau, tau + dt));
			tau += dt;
		}
	}

	SimulationSample Simulator::generate_random_numbers(Natural step, Natural path, bool antithetic_variates)
	{
		SimulationSample random(path, step);
		if (!antithetic_variates)
		{
			Natural half_index = path / 2;
			SimulationSample sub_random = generate_random_numbers(step, half_index, false);
			random.block(0, 0, half_index, step) = sub_random;
			random.block(half_index, 0, half_index, step) = -sub_random;
		}
		else
		{
			Real* random_ptr = random.data();
			for (Size i = 0; i < random.size(); i++)
			{
				*random_ptr = Gaussian::next_gaussian(_rng);
				++random_ptr;
			}
		}
		return random;
	}
}