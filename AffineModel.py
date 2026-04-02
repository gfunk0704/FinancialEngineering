from __future__ import annotations

import abc
from datetime import date
from typing import Any
import numpy as np

from ..deterministicinterestratecurve.deterministicinterestratecurve import DeterministicInterestRateCurve
from ...parametricmodel import ParametricModel
from ....time.daycounter.daycounter import DayCounter


class AffineModel[S, T](ParametricModel[S]):
    def __init__(self,
                 dayCounter: DayCounter,
                 referenceDate: date,
                 initialValue: T) -> None:
        super().__init__()
        self.__dayCounter = dayCounter
        self.__referenceDate = referenceDate
        self.__initialValue = initialValue

    @property
    def dayCounter(self) -> DayCounter:
        return self.__dayCounter

    @property
    def referenceDate(self) -> date:
        return self.__referenceDate

    @property
    def initialValue(self) -> list[float]:
        return self.__initialValue

    @property
    @abc.abstractmethod
    def nFactor(self) -> int:
        return NotImplemented
    
    def yearFraction(self, d: date) -> float:
        return self.dayCounter(self.referenceDate, d)
    
    @abc.abstractmethod
    def conditionalZCBAdjuster(self, 
                               startDate, 
                               endDate,
                               precomputedParamters: dict[str, Any] | None = None) -> AffineModelConditionalZCBAdjuster:
        return NotImplemented



class AffineModelConditionalObject[S, T](abc.ABC):
    def __init__(self,
                 affineModel: AffineModel[S, T],
                 startDate: date,
                 endDate: date) -> None:
        self.__affineModel = affineModel
        self.__startDate = startDate
        self.__endDate = endDate
        self.__startTime = affineModel.yearFraction(startDate)
        self.__endTime = affineModel.yearFraction(endDate)

    @property
    def affineModel(self) -> AffineModel:
        return self.__affineModel

    @property
    def startDate(self) -> date:
        return self.__startDate

    @property
    def endDate(self) -> date:
        return self.__endDate

    @property
    def startTime(self) -> float:
        return self.__startTime
    
    @property
    def endTime(self) -> float:
        return self.__endTime
    

class AffineModelConditionalZCBAdjuster[S, T](AffineModelConditionalObject[S, T]):
    @property
    @abc.abstractmethod
    def precomputedParamters(self) -> dict[str, Any]:
        return NotImplemented

    @abc.abstractmethod
    def __call__(self, 
                 stateVar: float | np.ndarray) -> np.ndarray:
        return NotImplemented
    

class OneFactorModelConditionalDensity[T](AffineModelConditionalObject[T, float]):
    def __init__(self, 
                 affineModel: AffineModel[T, float], 
                 startDate: date, 
                 endDate: date,
                 stateVar: float) -> None:
        assert affineModel.nFactor == 1, \
               "For OneFactorModelConditionalDensity, the number of factors must be 1"
        super().__init__(affineModel, startDate, endDate)
        self.__stateVar = stateVar

    @property
    def stateVar(self) -> float:
        return self.__stateVar

    @abc.abstractmethod
    def pdf(self, 
            x: np.ndarray) -> np.ndarray:
        return NotImplemented
    
    @abc.abstractmethod
    def cdf(self, 
            x: np.ndarray) -> np.ndarray:
        return NotImplemented

    
 
