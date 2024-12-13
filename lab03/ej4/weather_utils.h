#ifndef weather_utils
#define weather_utils

//#include <stdbool.h>
#include "weather.h"
#include "array_helpers.h"


int temp_min_hist(WeatherTable a);
/*
1. Obtiene la menor temperatura mínima histórica registrada en la ciudad de Córdoba
según los datos del arreglo.
*/

void temp_max_xano(WeatherTable a, int output[YEARS]);
/*
2. Registra para cada año entre 1980 y 2016 la mayor temperatura máxima
registrada durante ese año.
*/

void mes_max_xano(WeatherTable a, int output[YEARS]);
/*
3. Registra para cada año entre 1980 y 2016 el mes de ese año en
que se registró la mayor cantidad mensual de precipitaciones.
*/

#endif