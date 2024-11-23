#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include "exchange_population.h"

double exchange_population(int num_thread) 
{   
    clock_t start, end;
    double cpu_time_used;
    srand(time(NULL));
    // Σειριακή εκτέλεση
    start = clock();

    // Δημιουργία τοπικού πληθυσμού και fitness
    char *local_population = malloc(POPULATION_SIZE / num_thread * (STRING_LENGTH + 1) * sizeof(char));
    int *local_fitness = malloc(POPULATION_SIZE / num_thread * sizeof(int));

    // Αρχικοποίηση τοπικού πληθυσμού με παράλληλη εκτέλεση
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
        char *new_local_population = malloc(POPULATION_SIZE / num_thread * (STRING_LENGTH + 1) * sizeof(char));
        
        #pragma omp parallel for num_threads(num_thread)
        for (int i = 0; i < POPULATION_SIZE / num_thread; i++) {
            int p1 = rand() % (POPULATION_SIZE / num_thread);
            int p2 = rand() % (POPULATION_SIZE / num_thread);
            crossover(local_population + p1 * (STRING_LENGTH + 1), local_population + p2 * (STRING_LENGTH + 1), new_local_population + i * (STRING_LENGTH + 1));
            mutate(new_local_population + i * (STRING_LENGTH + 1));
        }

        // Αντιγραφή του νέου πληθυσμού στον παλιό πληθυσμό
        memcpy(local_population, new_local_population, POPULATION_SIZE / num_thread * (STRING_LENGTH + 1) * sizeof(char));

        // Απελευθέρωση μνήμης για τον νέο τοπικό πληθυσμό
        free(new_local_population);

        // Ανταλλαγή πληθυσμού κάθε 20 γενιές
        if (generation % 20 == 0) {
            #pragma omp critical
            {
                int best_fitness = -1;
                int best_index = -1;

                // Βρείτε το καλύτερο άτομο από το τοπικό πληθυσμό του νηματος
                for (int i = 0; i < POPULATION_SIZE / num_thread; i++) {
                    if (local_fitness[i] > best_fitness) {
                        best_fitness = local_fitness[i];
                        best_index = i;
                    }
                }

                // Ανταλλαγή του καλύτερου ατόμου με το καλύτερο άτομο από το πληθυσμό άλλου νήματος
                if (num_thread > 1) {
                    int other_thread = (omp_get_thread_num() + 1) % num_thread;
                    int other_best_fitness = -1;
                    int other_best_index = -1;

                    // Βρείτε το καλύτερο άτομο από το άλλο νήμα
                    for (int i = 0; i < POPULATION_SIZE / num_thread; i++) {
                        if (local_fitness[i] > other_best_fitness) {
                            other_best_fitness = local_fitness[i];
                            other_best_index = i;
                        }
                    }

                    // Ανταλλαγή των καλύτερων ατόμων
                    char temp[STRING_LENGTH + 1];
                    strcpy(temp, local_population + best_index * (STRING_LENGTH + 1));
                    strcpy(local_population + best_index * (STRING_LENGTH + 1), local_population + other_best_index * (STRING_LENGTH + 1));
                    strcpy(local_population + other_best_index * (STRING_LENGTH + 1), temp);
                }
            }
        }
    }

    // Απελευθέρωση της μνήμης για το τοπικό πληθυσμό και fitness
    free(local_population);
    free(local_fitness);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}
