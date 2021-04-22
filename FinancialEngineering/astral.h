#pragma once

#include <gradient_based_optimization.h>

namespace FinancialEngineering
{
	/*
	struct AstralSetting
	{
		AstralSetting(RealArray, RealArray, Real, Real, Real, Real, Natural);
		AstralSetting();
		RealArray beta;
		RealArray sigma;
		Real delta_0_hat;
		Real tau0;
		Real gamma;
		Real tol;
		Natural max_iter;
		Natural m;
	};

	class Astral : public GradientBasedOptimization
	{
	public:
		Astral(AstralSetting);
		Astral();
		OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray) override;

	private:
		class TrustRegionSubproblem : public ObjectiveFunction
		{
		public:
			TrustRegionSubproblem(RealMatrix, RealVector);
			Real evaluate(const RealArray&) override;
		private:
			RealMatrix _hessian_tilde;
			RealVector _gradient_tilde;
		};

		std::vector<Natural> _b;
		RealMatrix _hessian;
		RealArray _p;
		RealArray _beta;
		RealArray _sigma;
		std::vector<RealArray> _s;
		std::vector<RealArray> _y;
		Real _delta;
		Real _delta_0_hat;
		Real _tau_0;
		Real _tau;
		Real _gamma;
		Real _tol;
		Natural _max_iter;
		Natural _m;
		
		SharedPointer<Optimization> _tr_solver;

		Real infinity_norm(RealArray);
		RealArray gradient_projection_mapping(RealArray, RealVector);
		RealVector calculate_gradient(const RealArray&, const Real&);
		RealMatrix phi();
		void remove_matrix_column(RealMatrix& mat, Natural index);
		void update_hessian(const RealArray&, const RealArray&, const RealVector&, const RealVector&);
		std::vector<Natural> binding_constraint(const RealArray&, const RealVector&);
		void initialize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray);
	};

	inline void Astral::remove_matrix_column(RealMatrix& mat, Natural index)
	{
		mat.block(0, index, mat.rows(), mat.cols() - index) = mat.block(0, index + 1, mat.rows(), mat.cols() - index);
		mat.conservativeResize(mat.rows(), mat.cols() - 1);
	}

	inline RealArray Astral::gradient_projection_mapping(RealArray x, RealVector gradient)
	{
		return projection(x - gradient.array()) - x;
	}

	inline Real Astral::infinity_norm(RealArray v)
	{
		return v.abs().maxCoeff();
	}
	*/
	


}