// common.h
#ifndef COMMON_H
#define COMMON_H

#define POPULATION_SIZE 100
#define STRING_LENGTH 5
#define MAX_GENERATIONS 1000
#define MUTATION_RATE 0.1

// Δηλώνουμε την μεταβλητή target ως extern
extern const char target[STRING_LENGTH + 1];  // target πρέπει να είναι εξωτερική (extern)

char random_char();
int calculate_fitness(const char *individual);
void create_random_individual(char *individual);
void mutate(char *individual);
void crossover(const char *parent1, const char *parent2, char *offspring);

#endif
