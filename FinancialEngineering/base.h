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

	using ComplexArray = std::vector<Complex>;
	using BooleanArray = std::vector<bool>;
	using NaturalArray = std::vector<Natural>;
	using BigNaturalArray = std::vector<BigNatural>;
	using RealArray = std::vector<Real>;

	using ComplexVector = Eigen::VectorXcd;
	using RealVector = Eigen::VectorXd;

	using ComplexEigenArray = Eigen::ArrayXcd;
	using RealEigenArray = Eigen::ArrayXd;

	using ComplexMatrix = Eigen::MatrixXcd;
	using NaturalMatrix = Eigen::Matrix<Natural, Eigen::Dynamic, Eigen::Dynamic>;
	using RealMatrix = Eigen::MatrixXd;

	template<class T>
	using SharedPointer = std::shared_ptr<T>;
}