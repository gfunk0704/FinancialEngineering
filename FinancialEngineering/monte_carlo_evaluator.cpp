#include <monte_carlo_evaluator.h>

namespace FinancialEngineering
{
	MonteCarloEvaluator::MonteCarloEvaluator(SharedPointer<AssetModel> model,
											 SharedPointer<Rng32Bits> rng,
											 Date end_date) :
		Evaluator(model),
		_simulator(simulator_factory(model, rng)),
		_end_date(end_date)
	{
		_simulator->initialize(end_date);
		_sample = _simulator->generate_sample();
	}

	Real MonteCarloEvaluator::evaluate(SharedPointer<AmericanStyleOption> option)
	{
		Date value_date = _model->get_initial_date();
		Natural n_path = GlobalVariable::get_simulation_path();
		DateArray exercise_date = option->exercie_date(value_date);
		DateArray delivery_date = option->delivery_date(value_date);
		
		NaturalArray exercise_step(exercise_date.size());
		std::transform(exercise_date.begin(), exercise_date.end(), exercise_step.begin(), [&value_date](Date date)->Natural {return (date - value_date); });
		YieldCurve yield_curve = _model->get_risk_free_rate()->to_yield_curve();

		if (exercise_date.back() > _end_date)
		{
			_end_date = exercise_date.back();
			_simulator->initialize(_end_date);
			_sample = _simulator->generate_sample();
		}
		else if (exercise_date.back() == value_date)
		{
			return (_sample.back().mean()) * yield_curve.discount_factor(delivery_date.back());
		}

		SimulationSample payoff_sample;

		for (Size i = 0; i < exercise_step.size(); i++)
		{
			RealEigenArray payoff_array(n_path);
			RealEigenArray spot_array = _sample[exercise_step[i]];
			Real discount_to_exercise_date = yield_curve.discount_factor(delivery_date[i]) / yield_curve.discount_factor(exercise_date[i]);
			for (Size j = 0; j < n_path; j++)
				payoff_array(j) = option->exercise_payoff(spot_array(j));
			payoff_sample.push_back(payoff_array);
		}

		RealEigenArray final_payoff = payoff_sample.back();
		Real this_discount_factor = yield_curve.discount_factor(exercise_date.back());

		exercise_step.pop_back();
		exercise_date.pop_back();

		Real previous_discount_factor = yield_curve.discount_factor(exercise_date.back());
		final_payoff *= this_discount_factor / previous_discount_factor;

		for (Size i = exercise_step.size() - 1; i > 0; i--)
		{
			RealEigenArray exercise_payoff = payoff_sample[i];

			if (exercise_payoff.maxCoeff() > 0.0)
			{
				std::vector<Size> indexes;
				for (Size j = 0; j < n_path; j++)
				{
					if (exercise_payoff[j] > 0.0)
						indexes.push_back(j);
				}

				RealEigenArray step_sample = _sample[exercise_step[i]];
				RealVector exercise_spot(indexes.size());
				RealVector continuation(indexes.size());

				for (Size j = 0; j < indexes.size(); j++)
				{
					exercise_spot(j) = step_sample(indexes[j]);
					continuation(j) = final_payoff(indexes[j]);
				}

				RealArray expecation = calculate_expectation(exercise_spot, continuation);

				for (Size j = 0; j < indexes.size(); j++)
				{
					if (exercise_payoff(indexes[j]) > expecation[j])
						final_payoff(indexes[j]) = exercise_payoff(indexes[j]);
				}
			}
			this_discount_factor = previous_discount_factor;
			previous_discount_factor = yield_curve.discount_factor(exercise_date[i - 1]);
			final_payoff *= this_discount_factor / previous_discount_factor;
		}

		for (Size i = 0; i < n_path; i++)
			final_payoff(i) = final_payoff(i) > payoff_sample[0](i) ? final_payoff(i) : payoff_sample[0](i);

		return final_payoff.mean();
	}

	RealArray MonteCarloEvaluator::calculate_expectation(RealVector exercise_spot, RealVector continuation)
	{
		RealMatrix linear_equs(exercise_spot.rows(), 3);
		linear_equs << RealVector::Constant(exercise_spot.rows(), 1.0), exercise_spot, exercise_spot.array().square().matrix();
		RealVector coef = linear_equs.colPivHouseholderQr().solve(continuation);
		RealArray expectation(exercise_spot.size());
		for (Size i = 0; i < expectation.size(); i++)
		{
			expectation[i]= coef(0) + coef(1) * exercise_spot(i) + coef(2) * exercise_spot(i) * exercise_spot(i);
		}
		return expectation;
	}
}