#include <lbfgsb.h>

namespace FinancialEngineering
{
	static const Real machine_epsilon = std::numeric_limits<Real>::epsilon();

	void Lbfgsb::update_cauchy_point(Real, RealMatrix, RealMatrix)
	{
		RealVector t(_n_par);
		RealVector d = -_gradient;

		for (Eigen::Index i = 0; i < _n_par; i++)
		{
			if (_gradient(i) == 0.0)
			{
				t(i) = std::numeric_limits<Real>::max();
			}
			else
			{
				Real minus_num = (_gradient(i) > 0.0) ? _lower(i) : _upper(i);
				t(i) = (_x(i) - minus_num) / _gradient(i);
			}
			
			if (t(i) < machine_epsilon)
			{
				d(i) = 0.0;
			}
		}

		
	}


	OptimizationResult Lbfgsb::optimize(SharedPointer<ObjectiveFunction> func, RealArray lower, RealArray upper, RealArray x0)
	{
		Lbfgsb::initialize(func, x0, lower, upper);
		SmallNatural convergence = 0;
		Natural iteration;
		
		RealMatrix big_y = RealMatrix::Zero(_n_par, 0);
		RealMatrix big_s = RealMatrix::Zero(_n_par, 0);
		RealMatrix big_w = RealMatrix::Zero(_n_par, 0);
		RealMatrix big_m = RealMatrix::Zero(1, 1);
		Real theta = 1.0;

		for (iteration = 0; iteration < _max_iter; iteration++)
		{
			if (projection_gradient_inf_norm() < _tol)
			{
				convergence = 1;
				break;
			}

			RealArray x_old = _x;
			RealVector gradient_old = _gradient;
			update_cauchy_point(theta, big_w, big_m);

			if (!subspace_minimization(theta, big_w, big_m))
			{
				convergence = -1;
				break;
			}

			_x += _alpha * (_x_bar - _x);
			_f = _func->evaluate(_x);
			_gradient = calculate_gradient(_x, _f);
			RealVector y = _gradient - gradient_old;
			RealVector s = (_x - x_old).matrix();

			if ((s.transpose() * y).array().abs()(0) < 2.2204e-16)
				continue;

			if (iteration < _m)
			{
				big_y = column_bind(big_y, y);
				big_s = column_bind(big_s, s);
			}
			else
			{
				big_y.col(_m - 1) = y;
				big_s.col(_m - 1) = s;
			}

			theta = ((y.transpose() * y) / (y.transpose() * s))(0);
			big_w = column_bind(big_y, theta * big_s);
			RealMatrix a = big_s.transpose() * big_y;
			RealMatrix l = RealMatrix(a.triangularView<Eigen::StrictlyLower >());
			RealMatrix d = RealMatrix(-1.0 * a.diagonal());
			RealMatrix mm(d.rows() + l.rows(), d.cols() + l.rows());
			RealMatrix rhs_lower_mat = theta * s.transpose() * s;
			mm.block(0, 0, d.rows(), d.cols()) = d;
			mm.block(d.rows(), 0, l.rows(), l.cols()) = l;
			mm.block(0, d.cols(), l.cols(), l.rows()) = l.transpose();
			mm.block(d.rows(), d.cols(), rhs_lower_mat.rows(), rhs_lower_mat.cols()) = rhs_lower_mat;
		}
	}
}