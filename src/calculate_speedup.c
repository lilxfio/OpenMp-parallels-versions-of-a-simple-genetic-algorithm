#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared_population.h"
#include "independent_population.h"
#include "exchange_population.h"
#include "calculate_speedup.h"


double measure_time(int mode, int threads)
{
    if (mode == 1) {
        return shared_population(threads);  // Measure parallel time for shared population
    } else if (mode == 2) {
        return independent_population(threads);  // Measure parallel time for independent population
    } else if (mode == 3) {
        return exchange_population(threads);  // Measure parallel time for exchange population
    }
    return 0;
}

void calculate_speedup(double serial_time,double parallel_time,int mode,int thread) 
{
    
        double speedup = serial_time / parallel_time;
        if(mode==1)
          printf("Shared_population in %d thread has time : %f \n",thread,speedup);
        else if( mode == 2)
          printf("Independent_population in %d thread has time : %f \n",thread,speedup);
        else 
          printf("Exchange_population in %d thread has time : %f \n",thread,speedup);  
}
