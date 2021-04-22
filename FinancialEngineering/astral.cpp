#include <astral.h>

namespace FinancialEngineering
{
	/*
	void Astral::initialize(SharedPointer<ObjectiveFunction> func, RealArray x, RealArray lower, RealArray upper)
	{
		GradientBasedOptimization::initialize(func, x, lower, upper);
		_p = gradient_projection_mapping(_x, _gradient);
		_hessian = RealMatrix(_n_par, _n_par).Identity();
		_delta = std::min((_upper - _lower).maxCoeff(), _delta_0_hat);
		_tau = _tau_0;
		_b = binding_constraint(_x, _gradient);
	}

	std::vector<Natural> Astral::binding_constraint(const RealArray& x, const RealVector& gradient)
	{
		std::vector<Natural> b;
		for (Natural i = 0; i < _n_par; i++)
		{
			if ((x(i) == _lower(i) && gradient(i) > 0) ||
				(x(i) == _upper(i) && gradient(i) < 0))
			{
				b.push_back(i);
			}
		}
		return b;
	}

	

	OptimizationResult Astral::optimize(SharedPointer<ObjectiveFunction> func, RealArray x, RealArray lower, RealArray upper)
	{
		initialize(func, x, lower, upper);
		Natural k = 0;
		SmallNatural convergence = 0;

		while (k < _max_iter)
		{
			if (infinity_norm(_p) == 0.0)
			{
				convergence = 1;
				break;
			}
			else if (infinity_norm(_p) <= _tau)
			{
				_tau *= _gamma;
				RealArray x_hat = projection((_x - _gradient.array()));
				Real f_hat = _func->evaluate(x_hat);
				RealVector gradient_hat = calculate_gradient(x_hat, f_hat);
				std::vector<Natural> b_hat = binding_constraint(x_hat, gradient_hat);
				if (b_hat.size() == 0 || (b_hat != _b))
				{
					update_hessian(_x, x_hat, _gradient, gradient_hat);
					_x = x_hat;
					_f = f_hat;
					_gradient = gradient_hat;
					_b = b_hat;
					++k;
				}

				RealArray l_k = (_lower - _x).max(-_delta);
				RealArray u_k = (_upper - _x).min(_delta);
				RealMatrix phi_mat = phi();
				RealMatrix hessian_tilde = phi_mat.transpose() * _hessian * phi_mat;
				RealVector gradient_tilde = phi_mat.transpose() * _gradient;
				RealArray l_k_tilde = (phi_mat.transpose() * l_k.matrix()).array();
				RealArray u_k_tilde = (phi_mat.transpose() * u_k.matrix()).array();
				SharedPointer<ObjectiveFunction> subproblem = SharedPointer<ObjectiveFunction>(new TrustRegionSubproblem(hessian_tilde, gradient_tilde));
				OptimizationResult subproblem_solution = _tr_solver->optimize(subproblem, l_k_tilde, u_k_tilde);
				RealArray s_bar = subproblem_solution.par;
			}
		}
	}
	*/
	
}