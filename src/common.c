#include <stdlib.h>
#include <string.h>
#include "common.h"

const char target[STRING_LENGTH + 1] = "AAAAA";  // target string

// Generate a random character
char random_char() {
    return 'A' + (rand() % 26);  // Random character between 'A' and 'Z'
}

// Calculate fitness by comparing to the target
int calculate_fitness(const char *individual) {
    int fitness = 0;
    for (int i = 0; i < STRING_LENGTH; i++) {
        if (individual[i] == target[i]) {
            fitness++;
        }
    }
    return fitness;
}

// Create a random individual
void create_random_individual(char *individual) {
    for (int i = 0; i < STRING_LENGTH; i++) {
        individual[i] = random_char();
    }
    individual[STRING_LENGTH] = '\0';  // Null-terminate the string
}

// Perform mutation
void mutate(char *individual) {
    for (int i = 0; i < STRING_LENGTH; i++) {
        if ((rand() / (float)RAND_MAX) < MUTATION_RATE) {
            individual[i] = random_char();
        }
    }
}

// Perform crossover between two parents
void crossover(const char *parent1, const char *parent2, char *offspring) {
    for (int i = 0; i < STRING_LENGTH; i++) {
        offspring[i] = (rand() % 2) ? parent1[i] : parent2[i];
    }
    offspring[STRING_LENGTH] = '\0';  // Null-terminate the string
}
