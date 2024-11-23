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
    // Σειριακή εκτέλεση
    start = clock();

    // Δημιουργία πληθυσμού και fitness
    char population[POPULATION_SIZE][STRING_LENGTH + 1];
    int fitness[POPULATION_SIZE];

    // Αρχικοποίηση του πληθυσμού
    for (int i = 0; i < POPULATION_SIZE; i++) {
        create_random_individual(population[i]);
    }

    // Εξέλιξη του πληθυσμού για κάθε γενιά
    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        
        // Υπολογισμός fitness για κάθε άτομο στον πληθυσμό
        #pragma omp parallel for num_threads(num_thread)
        for (int i = 0; i < POPULATION_SIZE; i++) {
            fitness[i] = calculate_fitness(population[i]);
        }

        // Δημιουργία νέου πληθυσμού μέσω crossover και mutation
        char new_population[POPULATION_SIZE][STRING_LENGTH + 1];

        #pragma omp parallel for num_threads(num_thread)
        for (int i = 0; i < POPULATION_SIZE; i++) {
            unsigned int seed = i + generation; // Αποφυγή επαναλήψεων στην παραγωγή τυχαίων αριθμών
            int p1 = rand_r(&seed) % POPULATION_SIZE;
            int p2 = rand_r(&seed) % POPULATION_SIZE;
            crossover(population[p1], population[p2], new_population[i]);
            mutate(new_population[i]);
        }

        // Αντιγραφή του νέου πληθυσμού στον κύριο πληθυσμό
        memcpy(population, new_population, sizeof(population));
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}
