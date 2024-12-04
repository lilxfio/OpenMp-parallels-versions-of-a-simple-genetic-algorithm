#ifndef CALCULATE_SPEEDUP_H
#define CALCULATE_SPEEDUP_H

double measure_time(int mode, int threads);
void calculate_speedup(double serial_time,double parallel_time,int mode,int thread); 

#endif
