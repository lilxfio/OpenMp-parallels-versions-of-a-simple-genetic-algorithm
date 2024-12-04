#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "shared_population.h"
#include "independent_population.h"
#include "exchange_population.h"
#include "calculate_speedup.h"

// Ορίζουμε τη μεταβλητή target ΜΟΝΟ ΕΔΩ
//const char target[STRING_LENGTH + 1] = "AAAAA";  // target είναι το string που προσπαθούμε να βρούμε

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s [1|2|3]\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[1]);



    // Ορίζουμε τους αριθμούς νημάτων για 1, 2, 4, και τον μέγιστο
    int threads_1 = 1;
    int threads_2 = 2;
    int threads_4 = 4;
    int threads_max = omp_get_num_procs();

    double serial = measure_time(mode,threads_1);
    
    double parallel_2 = measure_time(mode,threads_2);
    calculate_speedup(serial,parallel_2,mode,threads_2);

    double parallel_4 = measure_time(mode,threads_4);
    calculate_speedup(serial,parallel_4,mode,threads_4);

    double parallel_max = measure_time(mode,threads_max); 
    calculate_speedup(serial,parallel_max,mode,threads_max);  
   
    
}
