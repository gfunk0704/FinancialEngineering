
from bisect import bisect_left
from datetime import date
from math import exp, sqrt
from typing import Any
import numpy as np
from scipy.stats import norm

from pricingengine.model.interestrate.deterministicinterestratecurve.deterministicinterestratecurve import DeterministicInterestRateCurve
from pricingengine.model.interestrate.stochastic.affinemodel import (
    AffineModel, 
    AffineModelConditionalZCBAdjuster,
    OneFactorModelConditionalDensity
)
from pricingengine.time.daycounter.daycounter import DayCounter
from .genericdeterministicshiftextension import GenericDeterministicShiftExtension

GaussianModelParameter = float | list[tuple[date, float]]

class GaussianModel(AffineModel[GaussianModelParameter, float]):
    '''
        x(0) = 0 \n

        dx(t) = a x dt + \\sigma(t) dW^\\mathbb{Q}(t)
    '''
    def __init__(self, 
                 dayCounter: DayCounter,
                 referenceDate: date) -> None:
        super().__init__(dayCounter,
                         referenceDate,
                         0.0)

    @classmethod
    def parameterNames(cls) -> list[float]:
        return ["a", "sigma"]

    @property
    def a(self) -> float:
        return self.parameters["a"]
    
    @property
    def sigma(self) -> list[tuple[date, float]]:
        return self.parameters["sigma"]
    
    @property
    def nFactor(self) -> int:
        return 1
    
    def conditionalZCBAdjuster(self, 
                                 startDate: date, 
                                 endDate: date,
                                 precomputedParamters: dict[str, Any] | None = None) -> AffineModelConditionalZCBAdjuster:
        return GaussianModelConditionalZCBAdjuster(self, startDate, endDate, precomputedParamters)

    def Sigma(self, endDate: date) -> float:
        '''
            計算 Sigma_dd(0, t), t是endDate的年化時間
        '''
        # yearFraction(d) = [horizon , d]之間的年化時間
        yearFraction = self.yearFraction
        endTime = yearFraction(endDate)
        a = self.a
        sigma = self.sigma
        endIndex = bisect_left(sigma, endDate, key=lambda pt: pt[0])
        targetSigmas = sigma[:(endIndex + 1)]
        bigIDates = [step[0] for step in targetSigmas]
        bigIDates[-1] = endDate
        bigSigmaSigmas = np.array([step[1] for step in targetSigmas])
        bigSigmaSigmas *= bigSigmaSigmas
        bigITimes = [yearFraction(d) for d in bigIDates]
        bigITimes.insert(0, 0.0)
        expTerm = np.exp(2 * a * np.array(bigITimes))
        expTerm2Diff = np.diff(expTerm)
        return float(np.sum(bigSigmaSigmas * expTerm2Diff) / \
                     (2.0 * a)) * exp(-2 * a * endTime)


class HullWhite(GenericDeterministicShiftExtension[GaussianModelParameter, float]):
    '''
    我們用 Brigo and Mercurio (2001) 的方式描繪 Hull-White 動態過程。

    Reference:\n
    Brigo, Damiano, and Fabio Mercurio. "A deterministic–shift extension of analytically–tractable and time–homogeneous short–rate models." Finance and Stochastics 5.3 (2001): 369-387.
    '''

    def __init__(self,
                 marketRateCurve: DeterministicInterestRateCurve) -> None:
        super().__init__(marketRateCurve, GaussianModel(marketRateCurve.dayCounter, marketRateCurve.referenceDate))


class GaussianModelConditionalDensity(OneFactorModelConditionalDensity):
    def __init__(self, 
                 affineModel: GaussianModel, 
                 startDate: date, 
                 endDate: date, 
                 stateVar: float) -> None:
        super().__init__(affineModel, startDate, endDate, stateVar)
        a = affineModel.a
        startTime = self.startTime
        endTime = self.endTime
        timePeriod = endTime - startTime
        B_DERIV = exp(-a * timePeriod)
        B = (1 - B_DERIV) / a
        SIGMA_0 = affineModel.Sigma(startDate)
        self.__mu = B_DERIV * (stateVar + B * SIGMA_0)
        self.__stdDev = sqrt(affineModel.Sigma(endDate) - B_DERIV * B_DERIV * SIGMA_0)
        
    @property
    def mu(self) -> float:
        return self.__mu
    
    @property
    def stdDev(self) -> float:
        return self.__stdDev

    def pdf(self, x: np.ndarray) -> np.ndarray:
        return norm.pdf(x, loc=self.__mu, scale=self.__stdDev)
    
    def cdf(self, x: np.ndarray) -> np.ndarray:
        return norm.cdf(x, loc=self.__mu, scale=self.__stdDev)
    

class GaussianModelConditionalZCBAdjuster(AffineModelConditionalZCBAdjuster[GaussianModelParameter, float]):
    def __init__(self, 
                 affineModel: GaussianModel, 
                 startDate: date, 
                 endDate: date,
                 precomputedParamters: dict[str, Any] | None = None) -> None:
        super().__init__(affineModel, startDate, endDate)
        a = affineModel.a
        twoA = 2 * a
        startTime = self.startTime
        endTime = self.endTime
        timePeriod = endTime - startTime
        B = (1 - exp(-a * timePeriod)) / a
        self.__B = B

        if startDate == affineModel.referenceDate:
            self.__muSecTerm = 0
        else:
            if precomputedParamters is None: 
                sigma = affineModel.sigma
                dayCounter = self.affineModel.dayCounter
                startIndex = bisect_left(sigma, startDate, key=lambda pt: pt[0])
                bigIEndIndex = startIndex + 1
                targetSigma = sigma[:bigIEndIndex]
                targetDates = [step[0] for step in targetSigma]
                targetDates[-1] = startDate
                referenceDate = affineModel.referenceDate
                taus = [dayCounter(referenceDate, d) for d  in targetDates]
                taus.insert(0, 0.0)
                taus = np.array(taus)
                sigmaValues = np.array([step[1] for step in targetSigma])
                sigmaSqrSeries = sigmaValues * sigmaValues
                bigSigmaScalar = exp(-twoA * startTime) / twoA
                expTermSeries = np.exp(a * taus)
                expTermSqrSeries = expTermSeries * expTermSeries
                expTermSqrDiffs = np.diff(expTermSqrSeries)
                SIGMA = bigSigmaScalar * np.sum(sigmaSqrSeries * expTermSqrDiffs)
                bigIFirstTermScalar = exp(-a * startTime) / (a * a)
                bigISecondTermScalar = bigSigmaScalar / a
                I = bigIFirstTermScalar * np.sum(sigmaSqrSeries * np.diff(expTermSeries)) - \
                        bigISecondTermScalar * np.sum(sigmaSqrSeries * expTermSqrDiffs)
                precomputedParamters = {"SIGMA": SIGMA, "I": I}
            self.__I = precomputedParamters["I"]
            self.__muSecTerm = 0.5 * B * B * precomputedParamters["SIGMA"]
            self.__precomputedParamters = precomputedParamters
           
    @property
    def precomputedParamters(self) -> dict[date, dict[str, Any]]:
        return self.__precomputedParamters

    def __call__(self, stateVar: float | np.ndarray) -> np.ndarray:
        mu = self.__B * (stateVar + self.__I) + self.__muSecTerm
        return np.exp(-mu)
            


    

        
    
    


    

    

    
