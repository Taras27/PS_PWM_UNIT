/*
 * filter.c
 *
 *  Created on: 1 серп. 2022 р.
 *      Author: Taras
 */


#include "filter.h"


uint32_t FILTER_GetValue( unsigned int com )
{
         static unsigned int iLastData; // Последнее значение
         unsigned int iData; // На этот раз вычисленное значение
         float dPower = 0.1; // Коэффициент фильтра
         iData = (com * dPower) + (1-dPower) * iLastData; // расчет
         iLastData = iData; // сохраняем эти данные
         return iData; // Вернуть данные
}
