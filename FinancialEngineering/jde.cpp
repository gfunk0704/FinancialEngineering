#include <jde.h>

namespace FinancialEngineering
{
	JdeSetting::JdeSetting(Real cr_threshold,
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

	JdeSetting::JdeSetting():
		JdeSetting(0.1, 0.1, 1.0, 0.1, std::sqrt(std::numeric_limits<double>::epsilon()), 0, 0)
	{}

	Jde::Jde(SharedPointer<Rng32Bits> rng, 
		     JdeSetting setting):
		_real_unifrom_rng(RealUniform32(rng)),
		_natural_unifrom_rng(NaturalUniform(rng)),
		_sampling(NonreplacementSampling(NaturalUniform(rng))),
		_cr_threshold(setting.cr_threshold),
		_f_threshold(setting.f_threshold),
		_f_lower(setting.f_lower),
	    _f_range(setting.f_upper - setting.f_lower),
		_tol(setting.tol),
		_np(setting.np)
	{}

	Jde::Jde(SharedPointer<Rng32Bits> rng):
		Jde(rng, JdeSetting())
	{}

	OptimizationResult Jde::optimize(SharedPointer<ObjectiveFunction> func, RealArray lower, RealArray upper)
	{
		SmallNatural convergence = 0;
		Natural d = lower.size();
		std::vector<RealArray> samples;
		RealArray values;
		RealArray f;
		RealArray cr;
		RealArray interval(d);
		Natural np = (_np <= 0)? (10 * d) : _np;
		Natural max_iter = (_max_iter <= 0) ? (5000 * d) : _max_iter;

		for (Size i = 0; i < d; i++)
			interval[i] = upper[i] - lower[i];

		_real_unifrom_rng.reset();
		_natural_unifrom_rng.reset();
		_sampling.reset();

		for (Natural i = 0; i < np; i++)
		{
			RealArray new_sample(d);
			for (Size j = 0; j < d; j++)
				new_sample[j] = lower[j] + interval[j] * _real_unifrom_rng.next_uniform();
			samples.push_back(new_sample);
			values.push_back(func->evaluate(new_sample));
			f.push_back(_f_lower + _f_range * _real_unifrom_rng.next_uniform());
			cr.push_back(_real_unifrom_rng.next_uniform());
		}

		pair_sort(values, samples);
		Natural count = 0;

		while (count < max_iter)
		{
			if (std::abs(values.back() - values[0]) < _tol)
			{
				convergence = 1;
				break;
			}

			++count;

			for (Natural i = 0; i < np; i++)
			{
				Natural j = _natural_unifrom_rng.next_uniform(d);
				NaturalArray indexes = _sampling.sampling(3, np - 1);
				std::vector<RealArray> x;

				for (NaturalArray::iterator iter = indexes.begin(); iter != indexes.end(); ++iter)
				{
					(*iter) = (*iter >= i) ? (*iter + 1) : (*iter);
				}

				RealArray u(d);
				for (Natural k = 0; k < d; k++)
				{
					if ((k == j) || _real_unifrom_rng.next_uniform() > cr[i])
					{
						u[k] = x[indexes[0]][k] + f[i] * (x[indexes[1]][k] - x[indexes[2]][k]);
						if ((u[k] > upper[k]) || (u[k] < lower[k]))
							u[k] = lower[k] + interval[k] * _real_unifrom_rng.next_uniform();
					}
				}

				if (_real_unifrom_rng.next_uniform() < _cr_threshold)
					cr[i] = _real_unifrom_rng.next_uniform();
				if (_real_unifrom_rng.next_uniform() < _f_threshold)
					f[i] = _f_lower + _f_range * _real_unifrom_rng.next_uniform();

				Real new_value = func->evaluate(u);
				if (new_value < values[i])
				{
					values[i] = new_value;
					samples[i] = u;
				}
			}

			pair_sort(values, samples);
		}

		return OptimizationResult(samples[0], values[0], count, convergence);
	}
}