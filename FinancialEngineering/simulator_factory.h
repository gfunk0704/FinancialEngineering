#pragma once

#include <asset_model.h>
#include <simulator.h>
#include <black_scholes.h>
#include <black_scholes_simulator.h>
#include <heston.h>
#include <heston_simulator.h>
#include <uncertain_volatility.h>
#include <uncertain_volatility_simulator.h>
#include <gaussian.h>

namespace FinancialEngineering
{
	SharedPointer<Simulator> simulator_factory(SharedPointer<AssetModel>, bool);
}
