#pragma once

#include <optimization.h>

namespace FinancialEngineering
{

	struct ImplicitFilteringSetting
	{
		ImplicitFilteringSetting(Real, Real, Real, Real, Natural, Natural);
		ImplicitFilteringSetting();
		Real initial_h;
		Real min_h;
		Real beta;
		Real tol; 
		Natural max_iter; 
		Natural max_cut;
	};

	class ImplicitFiltering : public GradientBasedOptimization
	{
	public:
		ImplicitFiltering(ImplicitFilteringSetting);
		ImplicitFiltering();
		OptimizationResult optimize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray) override;
	private:
		Real _initial_h;
		Real _min_h;
		Real _beta;
		Real _tol;
		Natural _max_iter;
		Natural _max_cut;
		RealArray _initial_value;
		RealArray _upper;
		RealArray _lower;
		RealMatrix _hessian;
		Size _n_par;
		SharedPointer<ObjectiveFunction> _func;

		void initialize(SharedPointer<ObjectiveFunction>, RealArray, RealArray, RealArray);
		RealVector finite_difference(RealArray, Real);
		Real calculate_tol(RealArray, RealArray);
		RealArray update_x(RealArray x, RealVector gradient);
		bool line_search(RealArray&, RealVector, Real&, Real);
		RealVector as_vector(RealArray);
		RealArray as_array(RealVector);
		OptimizationResult constrained_bfgs(RealArray, Real);
	};

	inline void ImplicitFiltering::initialize(SharedPointer<ObjectiveFunction> func, RealArray initial_value, RealArray lower, RealArray upper)
	{
		_func = func;
		_initial_value = initial_value;
		_n_par = initial_value.size();
		_lower = lower;
		_upper = upper;
		_hessian = RealMatrix::Identity(_n_par, _n_par);
	}

	inline RealArray ImplicitFiltering::update_x(RealArray x, RealVector gradient)
	{
		RealArray new_x;
		for (Size i = 0; i < _n_par; i++)
		{
			Real value = x[i] - gradient(i);
			new_x.push_back(std::min(std::max(value, _lower[i]), _upper[i]));
		}
		return new_x;
	}

	inline Real ImplicitFiltering::calculate_tol(RealArray x, RealArray new_x)
	{
		Real tol = 0.0;
		for (Size i = 0; i < _n_par; i++)
		{
			tol += std::abs(x[i] - new_x[i]);
		}
		return tol;
	}

	inline RealVector ImplicitFiltering::as_vector(RealArray real_array)
	{
		RealVector vec(real_array.size());
		for (Size i = 0; i < real_array.size(); i++)
			vec(i) = real_array[i];
		return vec;
	}

	inline RealArray ImplicitFiltering::as_array(RealVector vec)
	{
		RealArray real_array(vec.size());
		for (Size i = 0; i < vec.size(); i++)
			real_array[i] = vec(i);
		return real_array;
	}

	
}