#include <implicit_filtering.h>

namespace FinancialEngineering
{
	ImplicitFilteringSetting::ImplicitFilteringSetting(Real initial_h,
													   Real min_h,
												   	   Real beta,
													   Real tol,
													   Natural max_iter,
													   Natural max_cut)
	{
		this->initial_h = initial_h;
		this->min_h = min_h;
		this->beta = beta;
		this->tol = tol;
		this->max_iter = max_iter;
		this->max_cut = max_cut;
	}

	ImplicitFilteringSetting::ImplicitFilteringSetting():
		ImplicitFilteringSetting(0.0009765625, 9.536743e-07, 0.5, 1E-8, 1000, 100)
	{}

	ImplicitFiltering::ImplicitFiltering(ImplicitFilteringSetting setting):
		_initial_h(setting.initial_h),
	    _min_h(setting.min_h),
	    _beta(setting.beta),
	    _tol(setting.tol),
	    _max_iter(setting.max_iter),
        _max_cut(setting.max_cut)
	{}

	ImplicitFiltering::ImplicitFiltering():
		ImplicitFiltering(ImplicitFilteringSetting())
	{}

	OptimizationResult ImplicitFiltering::optimize(SharedPointer<ObjectiveFunction> func, RealArray initial_value, RealArray lower, RealArray upper)
	{
		RealArray par = _initial_value;
		Real h = _initial_h;
		OptimizationResult result(_initial_value, 0.0, 0, 0);

		while (h >= _min_h)
		{
			result = constrained_bfgs(par, h);
			par = result.par;
			h *= 0.5;
			if (result.convergence <= 0)
				break;
		}

		return result;
	}

	RealVector ImplicitFiltering::finite_difference(RealArray par, Real h)
	{
		RealVector gradient(par.size());
		Real two_h = 2.0 * h;
		for (Size i = 0; i < par.size(); i++)
		{
			RealArray par_plus = par;
			RealArray par_minus = par;
			par_plus[i] += h;
			par_minus[i] -= h;
			if (par_plus[i] > _upper[i])
			{
				gradient(i) = (_func->evaluate(par) - _func->evaluate(par_minus)) / h;
			}
			else if (par_minus[i] < _lower[i])
			{
				gradient(i) = (_func->evaluate(par_plus) - _func->evaluate(par)) / h;
			}
			else
			{
				gradient(i) = (_func->evaluate(par_plus) - _func->evaluate(par_minus)) / two_h;
			}
		}
		return gradient;
	}

	bool ImplicitFiltering::line_search(RealArray& x, RealVector s, Real& value, Real h)
	{
		Real lambda = 1.0;
		RealVector dd = s;
		Real s_max = 10.0 * h;
		if (dd.norm() > s_max)
			dd = s_max * dd / dd.norm();

		for (Size j = 0; j < _max_cut; j++)
		{ 
			RealVector d = -lambda * dd;
			RealArray temp_x(_n_par);
			for (Size i = 0; i < _n_par; i++)
			{
				temp_x[i] = x[i] + d(i);
			}
			Real temp_value = _func->evaluate(temp_x);
			if (temp_value < value)
			{
				value = temp_value;
				x = temp_x;
				return true;
			}
			lambda *= _beta;
		}

		return false;
	}

	OptimizationResult ImplicitFiltering::constrained_bfgs(RealArray par, Real h)
	{
		SmallNatural convergence = 0;
		Natural count = 0;
		Real tolerance = 1.0;
		Real value;
		RealArray x_c = par;
		RealArray x_minus;
		RealVector gradient_c = finite_difference(x_c, h);
		RealVector gradient_minus;

		while (count < _max_iter)
		{
			if (tolerance < (h * _tol))
			{
				convergence = 1;
				break;
			}

			RealVector s = -_hessian.inverse() * gradient_c;
			x_minus = x_c;
			gradient_minus = gradient_c;
			bool is_success = line_search(x_c, s, value, h);

			if (is_success)
			{
				gradient_c = finite_difference(x_c, h);
				tolerance = calculate_tol(x_c, update_x(x_c, gradient_c));
				RealVector sigma = as_vector(x_c) - as_vector(x_minus);
				RealVector y = gradient_c - gradient_minus;
				RealMatrix delta_hessian = (y * y.transpose()) * (sigma.transpose() * y).inverse() - (_hessian * sigma * sigma.transpose() * _hessian) * (sigma.transpose() * _hessian * sigma);
				_hessian += delta_hessian;
			}
			else
			{
				convergence = -1;
				break;
			}

			++count;
		}
		return OptimizationResult(x_c, value, count, convergence);
	}
}