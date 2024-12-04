#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include "shared_population.h"

double shared_population(int num_thread)
{    
    clock_t start, end;
    double cpu_time_used;
    srand(time(NULL));
    
    start = clock();

    
    char population[POPULATION_SIZE][STRING_LENGTH + 1];
    int fitness[POPULATION_SIZE];

   
    for (int i = 0; i < POPULATION_SIZE; i++) {
        create_random_individual(population[i]);
    }

  
    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        
        
        #pragma omp parallel for num_threads(num_thread)
        for (int i = 0; i < POPULATION_SIZE; i++) {
            fitness[i] = calculate_fitness(population[i]);
        }

        
        char new_population[POPULATION_SIZE][STRING_LENGTH + 1];

        #pragma omp parallel for num_threads(num_thread)
        for (int i = 0; i < POPULATION_SIZE; i++) {
            unsigned int seed = i + generation; 
            int p1 = rand_r(&seed) % POPULATION_SIZE;
            int p2 = rand_r(&seed) % POPULATION_SIZE;
            crossover(population[p1], population[p2], new_population[i]);
            mutate(new_population[i]);
        }

        
        memcpy(population, new_population, sizeof(population));
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}
