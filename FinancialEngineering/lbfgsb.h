#pragma once

#include <Eigen/src/core/ArithmeticSequence.h>

#include <quasi_newton.h>

namespace FinancialEngineering
{
	class Lbfgsb : public QuasiNewton
	{
	public:
		OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray) override;
	private:
		SmallNatural _m;
		RealArray _xc;
		RealArray _x_bar;
		RealArray _c;
		Real _alpha;

		void initialize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray) override;
		RealArray projection(const RealArray&);
		Real projection_gradient_inf_norm();
		void update_cauchy_point(Real, RealMatrix, RealMatrix);
		bool subspace_minimization(Real, RealMatrix, RealMatrix);
		RealMatrix column_bind(const RealMatrix&, const RealMatrix&);
	};

	inline void Lbfgsb::initialize(SharedPointer<ObjectiveFunction> func, RealArray x, RealArray lower, RealArray upper)
	{
		QuasiNewton::initialize(func, x, lower, upper);
		_xc = RealVector::Zero(_n_par);
		_c = RealVector::Zero(2 * _m);
	}

	inline RealArray Lbfgsb::projection(const RealArray& x)
	{
		return x.max(_lower).min(_upper);
	}

	inline Real Lbfgsb::projection_gradient_inf_norm()
	{
		RealArray projected_gradient = projection(_x - _gradient.array());
		return (projected_gradient - _x).abs().maxCoeff();
	}

	inline RealMatrix Lbfgsb::column_bind(const RealMatrix& lhs, const RealMatrix& rhs)
	{
		RealMatrix new_mat(lhs.rows(), lhs.cols() + rhs.cols());
		new_mat << lhs, rhs;
		return new_mat;
	}
}