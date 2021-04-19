#pragma once

#include <omp.h>

#include <date.h>
#include <day_count.h>
#include <rng_32bits.h>

namespace FinancialEngineering
{
	namespace GlobalVariable
	{
		void set_evaluation_date(Date);
		Date get_evaluation_date();
		void set_seed(Natural);
		Natural get_seed();
		void set_simulation_path(Natural);
		Natural get_simulation_path();
		void set_rng(SharedPointer<Rng32Bits>);
		SharedPointer<Rng32Bits> get_rng();

		inline void initialize_n_threads(unsigned n)
		{
			omp_set_num_threads(n);
			Eigen::setNbThreads(n);
		}
	};
}