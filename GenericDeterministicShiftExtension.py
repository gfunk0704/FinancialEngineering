
from __future__ import annotations
from typing import Any

import numpy as np
from datetime import date

from pricingengine.model.interestrate.deterministicinterestratecurve.deterministicinterestratecurve import DeterministicInterestRateCurve
from pricingengine.model.interestrate.interestratecurve import InterestRateCurve
from pricingengine.model.interestrate.stochastic.affinemodel import (
    AffineModel, 
    AffineModelConditionalZCBAdjuster
)
from pricingengine.time.daycounter.daycounter import DayCounter



class GenericDeterministicShiftExtension[S, T]:
    def __init__(self,
                 marketRateCurve: DeterministicInterestRateCurve,
                 affineModel: AffineModel[S, T]) -> None:
        super().__init__()
        self.__marketRateCurve = marketRateCurve
        self.__affineModel = affineModel

    @property
    def marketRateCurve(self) -> DeterministicInterestRateCurve:
        return self.__marketRateCurve
    
    @property
    def affineModel(self) -> AffineModel[S, T]:
        return self.__affineModel
    
    def discount(self, d: date) -> float:
        return self.marketRateCurve.discount(d)
    

class PrecomputedConditionalDiscountFactor:
    def __init__(self,
                 model: GenericDeterministicShiftExtension,
                 startDate: date,
                 endDate: date,
                 precomputedParamters: dict[str, Any] | None = None) -> None:
        self.__model = model
        self.__startDate = startDate
        self.__endDate = endDate
        self.__affineModelZCBPAdjuster = model.affineModel.conditionalZCBAdjuster(startDate, endDate, precomputedParamters) 
        marketRateCurve = model.marketRateCurve
        self.__marketDiscount = marketRateCurve.discount(endDate) / marketRateCurve.discount(startDate)
       
    @property
    def precomputedParamters(self) -> dict[str, Any]:
        return self.__affineModelZCBPAdjuster.precomputedParamters

    @property
    def dayCounter(self) -> DayCounter:
        return self.__model.marketRateCurve.dayCounter
    
    @property
    def referenceDate(self) -> date:
        return self.__startDate

    @property
    def startDate(self) -> date:
        return self.__startDate
    
    @property
    def endDate(self) -> date:
        return self.__endDate

    @property
    def model(self) -> AffineModel:
        return self.__model

    @property
    def affineModelZCBAdjuster(self) -> AffineModelConditionalZCBAdjuster:
        return self.__affineModelZCBPAdjuster

    @property
    def marketDiscount(self) -> float:
        return self.__marketDiscount
    
    def __call__(self, 
                 stateVar: np.ndarray) -> float | np.ndarray:
        return self.__marketDiscount * self.__affineModelZCBPAdjuster(stateVar)
    

class PrecomputedConditionalDiscountCurve(InterestRateCurve):
    def __init__(self,
                 model: GenericDeterministicShiftExtension,
                 startDate: date) -> None:
        super().__init__()
        self.__model = model
        self.__startDate = startDate
        self.__precomputedDiscountFactor = {}
        self.__stateVariables = None
        self.__precomputedParameters = None

    @property
    def referenceDate(self) -> date:
        return self.__startDate
    
    @property
    def dayCounter(self) -> DayCounter:
        return self.__model.marketRateCurve.dayCounter

    @property
    def model(self) -> GenericDeterministicShiftExtension:
        return self.__model

    @property
    def startDate(self) -> date:
        return self.__startDate

    @property
    def precomputedDiscountFactor(self) -> dict[str, PrecomputedConditionalDiscountFactor]:
        return self.__precomputedDiscountFactor

    @property
    def stateVariables(self) -> dict[date, np.ndarray]:
        return self.__stateVariables

    def setStateVariables(self,
                          stateVariables: np.ndarray) -> PrecomputedConditionalDiscountCurve:
        self.__stateVariables = stateVariables
        return self
    
    def discount(self, d: date) -> float:
        if not (d in self.__precomputedDiscountFactor):
            discountFactor = PrecomputedConditionalDiscountFactor(self.model, self.startDate, d, self.__precomputedParameters)
            self.__precomputedDiscountFactor[d] = discountFactor
            self.__precomputedParameters = discountFactor.precomputedParamters
        return self.precomputedDiscountFactor[d](self.__stateVariables)


    
    
    


