#include "weather_utils.h"

/*
1. Obtiene la menor temperatura mínima histórica registrada en la ciudad de Córdoba
según los datos del arreglo.
*/
int temp_min_hist(WeatherTable a){
    int min_temp = a[0][0][0]._min_temp;
    for (unsigned int y = 0; y < YEARS; y++)
    {
        for (unsigned int m = 0; m < MONTHS; m++)
        {
            for (unsigned int d = 0; d < DAYS; d++)
            {
                if (min_temp > a[y][m][d]._min_temp)
                {
                    min_temp = a[y][m][d]._min_temp;
                }
            }
        }
    }
    return min_temp;
}

/*
2. Registra para cada año entre 1980 y 2016 la mayor temperatura máxima
registrada durante ese año.
*/
void temp_max_xano(WeatherTable a, int output[YEARS]){
    int *p = NULL;
    int temp_max;
    for (unsigned int y = 0; y < YEARS; y++) {
        temp_max = a[y][0][0]._max_temp;
        for (unsigned int m = 0; m < MONTHS; m++)
        {
            for (unsigned int d = 0; d < DAYS; d++)
            {
                if (temp_max > a[y][m][d]._max_temp)
                {
                    temp_max = a[y][m][d]._max_temp;
                }
            } 
        }
        p = &output[y];
        *p = temp_max; // la mayor temperatura máxima del año 'y' + 1980
    }
}


/*
3. Registra para cada año entre 1980 y 2016 el mes de ese año en
que se registró la mayor cantidad mensual de precipitaciones.
*/
void mes_max_xano(WeatherTable a, int output[YEARS]){
    int *p = NULL;
    unsigned int mes_prec_max;
    int prec_max = 0;
    int prec;
    for (unsigned int y = 0; y < YEARS; y++) 
    {
        prec_max = a[y][0][0]._rainfall;
        for (unsigned int m = 0; m < MONTHS; m++)
        {   
            prec = 0;
            for (unsigned int d = 0; d < DAYS; d++)
            {
                prec = prec + a[y][m][d]._rainfall;
            } 
            if (prec_max < prec)
            {
                mes_prec_max = m;
                prec_max = prec;
            }
        }
        p = &output[y];
        *p = mes_prec_max; 
    }
}

