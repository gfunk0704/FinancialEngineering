#include <monte_carlo_evaluator.h>

namespace FinancialEngineering
{

	static Real standard_monte_carlo(SharedPointer<Option> option, Date value_date, DateArray exercise_date, DateArray delivery_date, SimulationSample sample, YieldCurve yield_curve)
	{
		Natural exercise_step = exercise_date[0] - value_date;
		Natural n_path = GlobalVariable::get_simulation_path();
		Date single_delivery_date = delivery_date[0];
		Real discount_factor = yield_curve.discount_factor(single_delivery_date);
		RealArray payoff_vector = option->exercise_payoff(sample.col(exercise_step));
		return discount_factor * (payoff_vector.mean());
	}

	static RealArray calculate_expectation(RealVector exercise_spot, RealVector continuation)
	{
		RealMatrix x(exercise_spot.rows(), 3);
		x << RealVector::Constant(exercise_spot.rows(), 1.0), exercise_spot, exercise_spot.array().square().matrix();
		RealMatrix xTx = x.transpose() * x;
		RealVector xTy = x.transpose() * continuation;
		RealVector coef = xTx.colPivHouseholderQr().solve(xTy);
		RealArray spot_array = exercise_spot.array();
		return coef(0) + coef(1) * spot_array + coef(2) * spot_array * spot_array;
	}

	static Real least_square_monte_carlo(SharedPointer<Option> option, Date value_date, DateArray exercise_date, DateArray delivery_date, SimulationSample sample, YieldCurve yield_curve)
	{
		Natural n_path = GlobalVariable::get_simulation_path();
		NaturalArray exercise_step(exercise_date.size());

		for (Size i = 0; i < exercise_date.size(); i++)
		{
			exercise_step(i) = exercise_date[i] - value_date;
		}

		SimulationSample payoff_sample(n_path, exercise_step.size());

		for (Size i = 0; i < exercise_step.size(); i++)
		{
			Real discount_to_exercise_date = yield_curve.discount_factor(delivery_date[i]) / yield_curve.discount_factor(exercise_date[i]);
			payoff_sample.col(i) = option->exercise_payoff(sample.col(exercise_step(i))) * discount_to_exercise_date;
		}

		RealArray final_payoff = payoff_sample.rightCols(1);
		Real this_discount_factor = yield_curve.discount_factor(exercise_date.back());
		Real previous_discount_factor = yield_curve.discount_factor(exercise_date[exercise_date.size() - 2]);
		final_payoff *= this_discount_factor / previous_discount_factor;

		for (Size i = exercise_step.size() - 2; i > 0; i--)
		{
			RealArray exercise_payoff = payoff_sample.col(i);
			if (exercise_payoff.maxCoeff() > 0.0)
			{
				std::vector<Size> indexes;
				for (Size j = 0; j < n_path; j++)
				{
					if (exercise_payoff(j) > 0.0)
						indexes.push_back(j);
				}

				RealArray step_sample = sample.col(exercise_step(i));
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
					if (exercise_payoff(indexes[j]) > expecation(j))
						final_payoff(indexes[j]) = exercise_payoff(indexes[j]);
				}
			}
			this_discount_factor = previous_discount_factor;
			previous_discount_factor = yield_curve.discount_factor(exercise_date[i - 1]);
			final_payoff *= this_discount_factor / previous_discount_factor;
		}

		return final_payoff.max(payoff_sample.col(0)).mean();
	}

	MonteCarloEvaluator::MonteCarloEvaluator(SharedPointer<AssetModel> model,
											 Date end_date,
											 bool antithetic_variates) :
		Evaluator(model),
		_simulator(simulator_factory(model, antithetic_variates)),
		_end_date(end_date)
	{
		initialize(_end_date);
	}

	Real MonteCarloEvaluator::evaluate(SharedPointer<Option> option)
	{
		Date value_date = _model->get_initial_date();
		DateArray exercise_date = option->exercie_date(value_date);
		DateArray delivery_date = option->delivery_date(value_date);

		if (exercise_date.back() > _end_date)
		{
			initialize(exercise_date.back());
		}
		
		if (exercise_date.size() > 1)
		{
			return least_square_monte_carlo(option, value_date, exercise_date, delivery_date, _sample, _model->get_risk_free_rate()->to_yield_curve());
		}
		else
		{
			return standard_monte_carlo(option, value_date, exercise_date, delivery_date, _sample, _model->get_risk_free_rate()->to_yield_curve());
		}
	}

	RealArray MonteCarloEvaluator::evaluate(std::vector<SharedPointer<Option>> portfolio)
	{
		Date value_date = _model->get_initial_date();
		Size n_option = portfolio.size();
		RealArray price = RealArray::Zero(n_option);
		Date port_end = portfolio_end_date(portfolio);
		if (port_end > _end_date)
		{
			initialize(port_end);
		}

		YieldCurve yield_curve = _model->get_risk_free_rate()->to_yield_curve();
		
		#pragma omp parallel for 
		for (Integer i = 0; i < n_option; i++)
		{
			DateArray exercise_date = portfolio[i]->exercie_date(value_date);
			DateArray delivery_date = portfolio[i]->delivery_date(value_date);
			if (exercise_date.size() > 1)
			{
				price[i] = least_square_monte_carlo(portfolio[i], value_date, exercise_date, delivery_date, _sample, yield_curve);
			}
			else
			{
				price[i] = standard_monte_carlo(portfolio[i], value_date, exercise_date, delivery_date, _sample, yield_curve);
			}
		}
		
		return price;
	}

	Date MonteCarloEvaluator::portfolio_end_date(std::vector<SharedPointer<Option>> option_array)
	{
		Date target = _end_date;
		for (auto option : option_array)
		{
			Date expiry = option->expiry();
			if (expiry > target)
			{
				target = expiry;
			}
		}
		return target;
	}

	
}