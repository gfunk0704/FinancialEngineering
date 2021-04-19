#include <heston_simulator.h>

namespace FinancialEngineering
{
	HestonSimulator::HestonSimulator(SharedPointer<AssetModel> model,
									 SharedPointer<Rng32Bits> rng,
									 bool antithetic_variates) :
		Simulator(model, rng, antithetic_variates)
	{}
	
	HestonSimulator::HestonSimulator(SharedPointer<AssetModel> model,
		                             SharedPointer<Rng32Bits> rng) :
		Simulator(model, rng)
	{}

	void HestonSimulator::initialize(Date end_date)
	{
		Simulator::initialize(end_date);
		_random1 = generate_random_numbers(_n_step);
		_random2 = generate_random_numbers(_n_step);
	}

	// volatility transform scheme
	SimulationSample HestonSimulator::generate_sample()
	{
		Natural n_sample = GlobalVariable::get_simulation_path();
		Parameter par = _model->get_parameter();
		Real v0 = par["v0"];
		Real kappa = par["kappa"];
		Real theta = par["theta"];
		Real sigma = par["sigma"];
		Real rho = par["rho"];
		Real beta_exp = std::exp(-kappa * dt);
		Real beta_coef = sigma * sigma * (1.0 - beta_exp) / (4.0 * kappa);
		Real theta_star_coef = std::exp(-0.5 * kappa * dt);
		Real theta_star_dominator = 1 - theta_star_coef;
		Real half_kappa = 0.5 * kappa;
		Real half_sigma = 0.5 * sigma;
		Real rho_coef = std::sqrt(1 - rho * rho);
		SimulationSample sample(n_sample, _n_step + 1);
		sample.col(0).fill(_model->get_initial_value());
		RealArray wt = RealArray::Constant(n_sample, std::sqrt(v0));
		for (Size i = 0; i < _n_step; i++)
		{
			RealArray log_drift = (_rt(i) - 0.5 * wt * wt) * dt;
			sample.col(i + 1) = sample.col(i) * (log_drift + wt * sqrt_dt * (rho * _random1.col(i) + rho_coef * _random2.col(i))).exp();
			RealArray beta_sqr = theta + (wt * wt - theta) * beta_exp - beta_coef;
			beta_sqr.max(0.0);
			RealArray theta_star = (beta_sqr.sqrt() - wt * theta_star_coef) / theta_star_dominator;
			wt += half_kappa * (theta_star - wt) * dt + half_sigma * sqrt_dt * _random1.col(i);
		}
		return sample;
	}

}