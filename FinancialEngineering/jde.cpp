#include <jde.h>
#include <ctime>
namespace FinancialEngineering
{
	static double diffclock(std::clock_t clock1, std::clock_t clock2)
	{
		double diffticks = clock1 - clock2;
		double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
		return diffms;
	}

	JdeSetting::JdeSetting(Real cr_threshold,
						   Real f_lower,
						   Real f_upper,
						   Real f_threshold,
						   Real tol,
						   Natural max_iter,
						   Natural np):
		cr_threshold(cr_threshold),
		f_lower(f_lower),
		f_upper(f_upper),
		f_threshold(f_threshold),
		tol(tol),
		max_iter(max_iter),
		np(np)
	{}

	JdeSetting::JdeSetting():
		JdeSetting(0.1, 0.1, 1.0, 0.1, std::sqrt(std::numeric_limits<double>::epsilon()), 0, 0)
	{}

	Jde::Jde(JdeSetting setting):
		PopulationBasedOptimization(GlobalVariable::get_rng()),
		_cr_threshold(setting.cr_threshold),
		_f_threshold(setting.f_threshold),
		_f_lower(setting.f_lower),
	    _f_range(setting.f_upper - setting.f_lower),
		_tol(setting.tol),
		_np(setting.np),
		_max_iter(setting.max_iter)
	{}

	Jde::Jde():
		Jde(JdeSetting())
	{}

	OptimizationResult Jde::optimize(SharedPointer<ObjectiveFunction> func, RealArray lower, RealArray upper)
	{
		SmallNatural convergence = 0;
		Natural d = lower.size();
		Natural np = (_np <= 0) ? (10 * d) : _np;
		Natural max_iter = (_max_iter <= 0) ? (5000 * d) : _max_iter;
		std::vector<RealArray> samples = generate_samples(np, lower ,upper);
		RealArray values(np);
		RealArray f = _f_lower + _f_range * Uniform::next_real_uniform(_rng, np);
		RealArray cr = Uniform::next_real_uniform(_rng, np);
		RealArray interval = upper - lower;
		_rng->reset();
		for (Natural i = 0; i < np; i++)
		{
			values(i) = func->evaluate(samples[i]);
		}

		pair_sort(values, samples);
		Natural count = 0;

		while (count < max_iter)
		{
			Real tol = std::abs(values.tail(1)(0) - values(0));
			std::cout << "iter " << count << ": " << tol << ", " << values[0] << std::endl;

			if (tol < _tol)
			{
				convergence = 1;
				break;
			}

			++count;
			std::time_t start_time;

			for (Natural i = 0; i < np; i++)
			{
				std::cout << "sample " << i << std::endl;
				std::cout << "step 1" << std::endl;
				start_time = std::clock();
				RealArray u = samples[i];
				Natural must_mutation = Uniform::next_natural_uniform(_rng, d);

				NaturalArray indexes = NonreplacementSampling::sampling(_rng, 3, np - 1);
				std::cout << "time spend: " << diffclock(std::clock(), start_time) << std::endl;
				
				std::cout << "step 2" << std::endl;
				start_time = std::clock();

				for (Natural* iter = indexes.data(); iter != (indexes.data() + indexes.size()); iter++)
				{
					(*iter) = (*iter >= i) ? (*iter + 1) : (*iter);
				}

				std::cout << "time spend: " << diffclock(std::clock(), start_time) << std::endl;
				std::cout << "step 3" << std::endl;
				start_time = std::clock();

				for (Natural k = 0; k < d; k++)
				{
					if ((k == must_mutation) || Uniform::next_real_uniform(_rng) > cr(i))
					{
						u(k) = samples[indexes(0)](k) + f(i) * (samples[indexes(1)](k) - samples[indexes(2)](k));
						if ((u(k) > upper(k)) || (u(k) < lower(k)))
							u(k) = lower(k) + interval(k) * Uniform::next_real_uniform(_rng);
					}
				}

				std::cout << "time spend: " << diffclock(std::clock(), start_time) << std::endl;
				std::cout << "step 4" << std::endl ;
				start_time = std::clock();

				if (Uniform::next_real_uniform(_rng) < _cr_threshold)
					cr(i) = Uniform::next_real_uniform(_rng);
				if (Uniform::next_real_uniform(_rng) < _f_threshold)
					f(i) = _f_lower + _f_range * Uniform::next_real_uniform(_rng);

				std::cout << "time spend: " << diffclock(std::clock(), start_time) << std::endl;
				std::cout << "step 5" << std::endl;
				start_time = std::clock();

				Real new_value = func->evaluate(u);
				if (new_value < values(i))
				{
					values(i) = new_value;
					samples[i] = u;
				}

				std::cout << "time spend: " << diffclock(std::clock(), start_time) << std::endl;
				std::cout << "end" << std::endl;

			}

			pair_sort(values, samples);
		}

		return OptimizationResult(samples[0], values(0), count, convergence);
	}

	void Jde::pair_sort(RealArray& value, std::vector<RealArray>& samples)
	{
		Natural np = value.size();
		for (Size i = 0; i < (np - 1); i++)
		{
			for (Size j = (i + 1); j < np; j++)
			{
				if (value(i) > value(j))
				{
					Real temp_value = value(i);
					value(i) = value(j);
					value(j) = temp_value;
					RealArray temp_sample = samples[i];
					samples[i] = samples[j];
					samples[j] = temp_sample;
				}
			}
		}
	}
}