// common.h
#ifndef COMMON_H
#define COMMON_H

#define POPULATION_SIZE 1000
#define STRING_LENGTH 12
#define MAX_GENERATIONS 8000
#define MUTATION_RATE 0.2

extern const char target[STRING_LENGTH + 1];  

char random_char();
int calculate_fitness(const char *individual);
void create_random_individual(char *individual);
void mutate(char *individual);
void crossover(const char *parent1, const char *parent2, char *offspring);

#endif
