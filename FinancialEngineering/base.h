#pragma once

#include <complex>
#include <cstdint>
#include <vector>


#include <Eigen/Eigen>

namespace FinancialEngineering 
{
	using Complex = std::complex<double>;
	using Complex = std::complex<double>;
	using Integer = std::int32_t;
	using SmallInteger = std::int16_t;
	using Natural = std::uint32_t;
	using BigNatural = std::uint64_t;
	using SmallNatural = unsigned short;
	using Real = double;
	using Size = std::size_t;

	using ComplexArray = Eigen::ArrayXcd;
	using NaturalArray = Eigen::Array<Natural, -1, 1>;
	using RealArray = Eigen::ArrayXd;

	using ComplexVector = Eigen::VectorXcd;
	using RealVector = Eigen::VectorXd;

	using ComplexMatrix = Eigen::MatrixXcd;
	using NaturalMatrix = Eigen::Matrix<Natural, Eigen::Dynamic, Eigen::Dynamic>;
	using RealMatrix = Eigen::MatrixXd;

	template<class T>
	using SharedPointer = std::shared_ptr<T>;
}