#include <jde.h>

namespace FinancialEngineering
{
	DeSetting::DeSetting(Real cr_threshold,
						 Real f_lower,
						 Real f_upper,
						 Real f_threshold,
						 Real tol,
						 Natural max_iter,
						 Natural np)
	{
		this->cr_threshold = cr_threshold;
		this->f_lower = f_lower;
		this->f_upper = f_upper;
		this->f_threshold = f_threshold;
		this->tol = tol;
		this->max_iter = max_iter;
		this->np = np;
	}

	DeSetting::DeSetting():
		DeSetting(0.1, 0.1, 1.0, 0.1, std::sqrt(std::numeric_limits<double>::epsilon()), 0, 0)
	{}

	Jde::Jde(DeSetting setting):
		_rng(GlobalVariable::get_rng()),
		_cr_threshold(setting.cr_threshold),
		_f_threshold(setting.f_threshold),
		_f_lower(setting.f_lower),
	    _f_range(setting.f_upper - setting.f_lower),
		_tol(setting.tol),
		_np(setting.np),
		_max_iter(setting.max_iter)
	{}

	Jde::Jde():
		Jde(DeSetting())
	{}

	OptimizationResult Jde::optimize(SharedPointer<ObjectiveFunction> func, RealArray lower, RealArray upper)
	{
		SmallNatural convergence = 0;
		Natural d = lower.size();
		Natural np = (_np <= 0) ? (10 * d) : _np;
		Natural max_iter = (_max_iter <= 0) ? (5000 * d) : _max_iter;
		std::vector<RealArray> samples;
		RealArray values(np);
		RealArray f(np);
		RealArray cr(np);
		RealArray interval = upper - lower;
		_rng->reset();
		for (Natural i = 0; i < np; i++)
		{
			RealArray new_sample  = lower + interval * Uniform::next_real_uniform(_rng, d);
			samples.push_back(new_sample);
			values(i) = func->evaluate(new_sample);
			f(i) = _f_lower + _f_range * Uniform::next_real_uniform(_rng);
			cr(i) = Uniform::next_real_uniform(_rng);
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

			for (Natural i = 0; i < np; i++)
			{
				RealArray u = samples[i];
				Natural must_mutation = Uniform::next_natural_uniform(_rng, d);

				NaturalArray indexes = NonreplacementSampling::sampling(_rng, 3, np - 1);
				
				for (Natural* iter = indexes.data(); iter != (indexes.data() + indexes.size()); iter++)
				{
					(*iter) = (*iter >= i) ? (*iter + 1) : (*iter);
				}

				for (Natural k = 0; k < d; k++)
				{
					if ((k == must_mutation) || Uniform::next_real_uniform(_rng) > cr(i))
					{
						u(k) = samples[indexes(0)](k) + f(i) * (samples[indexes(1)](k) - samples[indexes(2)](k));
						if ((u(k) > upper(k)) || (u(k) < lower(k)))
							u(k) = lower(k) + interval(k) * Uniform::next_real_uniform(_rng);
					}
				}
			
				if (Uniform::next_real_uniform(_rng) < _cr_threshold)
					cr(i) = Uniform::next_real_uniform(_rng);
				if (Uniform::next_real_uniform(_rng) < _f_threshold)
					f(i) = _f_lower + _f_range * Uniform::next_real_uniform(_rng);

				Real new_value = func->evaluate(u);
				if (new_value < values(i))
				{
					values(i) = new_value;
					samples[i] = u;
				}
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