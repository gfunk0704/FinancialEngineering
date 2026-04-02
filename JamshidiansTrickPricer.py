
from math import sqrt
import numpy as np
from scipy.stats import norm

from pricingengine.instrument.enumerator import OptionType
from pricingengine.instrument.interestrate.genericirs import VanillaSwapPropertyGetter
from pricingengine.instrument.interestrate.standardeuropeanswaption import StandardEuropeanSwaption
from pricingengine.instrument.interestrate.swaptype import SwapType
from pricingengine.instrument.leg.fixedratelegcharacters import FixedRateLegCharacters
from pricingengine.math.rootsolver.rootsolver import RootSolver
from pricingengine.model.interestrate.stochastic.genericdeterministicshiftextension import PrecomputedConditionalDiscountFactor
from pricingengine.model.interestrate.stochastic.hullwhite import HullWhite
from pricingengine.model.interestrate.volatility.swaptionvolstilitycube import SwaptionVolatilityCube
from pricingengine.pricer.interestrate.swaption.hullwhitestdeuroswaptionpricer import HullWhiteStandardEuropeanSwaptionPricer
from pricingengine.pricingcondition import PricingCondition


class JamshidiansTrickPricer(HullWhiteStandardEuropeanSwaptionPricer):

    def __init__(self,
                 solver: RootSolver) -> None:
        super().__init__()
        self.__solver = solver

    @property
    def solver(self) -> RootSolver:
        return self.__solver

    def optionMarketValue(self, 
                          instrument: StandardEuropeanSwaption, 
                          marketData: dict[str, SwaptionVolatilityCube], 
                          pricingCondition: PricingCondition) -> float:
        
        swaptionCube = marketData[instrument.impliedVolSourceName]
        riskFreeRateCurve = swaptionCube.closedFormGeneratorBuilder.riskFreeRateCurve
        hullWhite = HullWhite(riskFreeRateCurve)
        affineModel = hullWhite.affineModel
        affineModel.setParameters(self.gaussianModelParameter)
        underlyingSwap = instrument.underlyingSwap
        optionMaturity = instrument.optionMaturity

        swapType = VanillaSwapPropertyGetter.getSwapType(underlyingSwap)
        if swapType == SwapType.PAYER:
            fixedRateLegCharacters: FixedRateLegCharacters = underlyingSwap.payLegCharacters
            omega = -1
        else:
            fixedRateLegCharacters: FixedRateLegCharacters = underlyingSwap.receiveLegCharacters
            omega = 1

        nominal = instrument.underlyingSwap.payNominalGenerator.setter.initialNominal
        k = fixedRateLegCharacters.fixedRate
        dayCounter = fixedRateLegCharacters.dayCounter
        fixedRateLegTaus = [dayCounter(s.calculationPeriod.startDate, s.calculationPeriod.endDate) for s in fixedRateLegCharacters.schedule.schedulePeriods]
        cks = [k * tau for tau in fixedRateLegTaus]
        cks[-1] += 1
        cks = np.array(cks)

        # For Jamshidian's trick, we assume endDate == paymentDate & optionMaturity == firstStartDate
        paymentDates = [s.calculationPeriod.endDate for s in fixedRateLegCharacters.schedule.schedulePeriods]
        optionMatMktDiscount = riskFreeRateCurve.discount(optionMaturity)
        paymentDateMktDiscounts = np.array([riskFreeRateCurve.discount(d) for d in paymentDates])
        mktDiscounts = paymentDateMktDiscounts / optionMatMktDiscount
        taus = np.array([affineModel.dayCounter(optionMaturity, d) for d in paymentDates])
        a = affineModel.a
        bs = (1.0 - np.exp(-a * taus)) / a
        dummyZcbAdjuster = affineModel.conditionalZCBAdjuster(optionMaturity, paymentDates[0])
        precomputedParameters = dummyZcbAdjuster.precomputedParamters
        SIGMA = precomputedParameters["SIGMA"]
        I = precomputedParameters["I"]
        muSecTerems = 0.5 * bs * bs * SIGMA

        def rootSolver(xStar: float) -> float:
            mu = bs * (xStar + I) + muSecTerems
            ps = mktDiscounts * np.exp(-mu)
            return np.sum(ps * cks) - 1.0
        
        xStar = self.solver(rootSolver, -1.0, 1.0)
        mu = bs * (xStar + I) + muSecTerems
        strikes = mktDiscounts * np.exp(-mu)
        sigmaPs = sqrt(SIGMA) * bs
        logTerms = np.log(mktDiscounts /  strikes)
        hs = logTerms / sigmaPs + 0.5 * sigmaPs
        d1 = omega * hs
        d2 = omega * (hs - sigmaPs)
        nd1 = norm.cdf(d1)
        nd2 = norm.cdf(d2)
        zbos = omega * (paymentDateMktDiscounts * nd1 - strikes * optionMatMktDiscount * nd2)
        return np.sum(cks * zbos) * nominal * instrument.position
