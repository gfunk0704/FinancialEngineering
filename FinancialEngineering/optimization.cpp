#include <optimization.h>

namespace FinancialEngineering
{
	OptimizationResult::OptimizationResult(RealArray par, 
		                                   Real value, 
		                                   Natural iter, 
										   SmallInteger convergence) :
		par(par), 
		value(value), 
		iter(iter), 
		convergence(convergence)
	{}

	RealVector GradientBasedAlgorithm::calculate_gradient(const RealArray& x, const Real& f)
	{
		if (_func->update_gradient(x))
		{
			return  _func->gradient();
		}
		else
		{
			return numerical_gradient(x, f);
		}
	}

	RealVector GradientBasedAlgorithm::numerical_gradient(const RealArray& x, const Real& f)
	{
		SmallNatural n_par = x.size();
		RealVector gradient(n_par);
		for (SmallNatural i = 0; i < n_par; i++)
		{
			RealArray x_plus = x;
			x_plus(i) += _h;
			RealArray x_minus = x;
			x_minus(i) -= _h;

			if (x_plus(i) > _upper(i))
			{
				gradient(i) = (f - _func->evaluate(x_minus)) / _h;
			}
			else if (x_minus(i) < _lower(i))
			{
				gradient(i) = (_func->evaluate(x_plus) - f) / _h;

			}
			else
			{
				gradient(i) = (_func->evaluate(x_plus) - _func->evaluate(x_minus)) / _h2;
			}
		}
		return gradient;
	}
}