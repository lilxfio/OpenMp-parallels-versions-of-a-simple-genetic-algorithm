#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include "independent_population.h"

double independent_population(int num_thread)
 {
    clock_t start, end;
    double cpu_time_used;
    srand(time(NULL));
    // Σειριακή εκτέλεση
    start = clock();
    // Δημιουργία δυναμικής μνήμης για το πληθυσμό και fitness εκτός του parallel region
    char *local_population = malloc((POPULATION_SIZE / num_thread) * (STRING_LENGTH + 1) * sizeof(char));
    int *local_fitness = malloc((POPULATION_SIZE / num_thread) * sizeof(int));

    // Αρχικοποίηση τοπικού πληθυσμού και fitness για κάθε νήμα
    #pragma omp parallel for num_threads(num_thread)
    for (int i = 0; i < POPULATION_SIZE / num_thread; i++) {
        create_random_individual(local_population + i * (STRING_LENGTH + 1));
    }

    // Εξέλιξη του πληθυσμού για κάθε γενιά
    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        // Υπολογισμός fitness για κάθε άτομο στον τοπικό πληθυσμό
        #pragma omp parallel for num_threads(num_thread)
        for (int i = 0; i < POPULATION_SIZE / num_thread; i++) {
            local_fitness[i] = calculate_fitness(local_population + i * (STRING_LENGTH + 1));
        }

        // Δημιουργία νέου τοπικού πληθυσμού μέσω crossover και mutation
        char *new_local_population = malloc((POPULATION_SIZE / num_thread) * (STRING_LENGTH + 1) * sizeof(char));
        #pragma omp parallel for num_threads(num_thread)
        for (int i = 0; i < POPULATION_SIZE / num_thread; i++) {
            int p1 = rand() % (POPULATION_SIZE / num_thread);
            int p2 = rand() % (POPULATION_SIZE / num_thread);
            crossover(local_population + p1 * (STRING_LENGTH + 1), local_population + p2 * (STRING_LENGTH + 1), new_local_population + i * (STRING_LENGTH + 1));
            mutate(new_local_population + i * (STRING_LENGTH + 1));
        }
        
        // Αντιγραφή του νέου πληθυσμού στον παλιό πληθυσμό
        memcpy(local_population, new_local_population, (POPULATION_SIZE / num_thread) * (STRING_LENGTH + 1) * sizeof(char));

        // Απελευθέρωση της μνήμης για τον νέο τοπικό πληθυσμό
        free(new_local_population);
    }

    // Απελευθέρωση της μνήμης για το τοπικό πληθυσμό και fitness
    free(local_population);
    free(local_fitness);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}
