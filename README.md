
# Genetic Algorithm Parallel Implementation

This project implements a parallel genetic algorithm using OpenMP to optimize the evolution of a population towards a target string. The implementation explores three population management techniques: shared population, independent population, and exchange population.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Performance Analysis](#performance-analysis)
- [Dependencies](#dependencies)
- [Configuration](#configuration)
- [Contributors](#contributors)
- [License](#license)

## Introduction

The goal of this project is to explore different strategies for implementing a parallel genetic algorithm. The program evolves a population of individuals (strings) toward a predefined target string (`"AAAAA"`). It measures execution times for serial and parallel modes, evaluates speedups, and compares three different population management techniques:
1. **Shared Population:** The entire population is shared among threads.
2. **Independent Population:** Each thread evolves its subset of the population independently.
3. **Exchange Population:** Threads periodically exchange the best individuals from their populations.

## Features

- Parallel genetic algorithm using OpenMP.
- Three population management techniques for scalability:
  - Shared Population.
  - Independent Population.
  - Exchange Population.
- Fitness evaluation, crossover, and mutation operators.
- Configurable population size, mutation rate, and number of generations.
- Performance benchmarking and speedup calculations.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/genetic-algorithm-parallel.git
   cd genetic-algorithm-parallel
   ```
2. Compile the project:
   ```bash
   gcc -fopenmp -o genetic_algorithm main.c shared_population.c independent_population.c exchange_population.c common.c calculate_speedup.c
   ```

## Usage

Run the program with the desired mode of operation:
```bash
./genetic_algorithm [MODE]
```
- **MODE**:
  - `1`: Shared Population.
  - `2`: Independent Population.
  - `3`: Exchange Population.

### Example
```bash
./genetic_algorithm 1
```
The program benchmarks the execution time for serial and parallel implementations using 1, 2, 4, and maximum available threads.

## Implementation Details

### Key Functions
- **Fitness Evaluation:** Compares individuals to the target string.
- **Crossover:** Combines genetic material from two parents to produce offspring.
- **Mutation:** Randomly alters genes with a small probability.

### Modes of Population Management
1. **Shared Population:** Threads work on a common population with shared memory.
2. **Independent Population:** Each thread operates on its private subset of the population.
3. **Exchange Population:** Threads periodically exchange their best-performing individuals.

### Parallelization
OpenMP parallel regions are used for:
- Fitness computation.
- Crossover and mutation processes.

## Performance Analysis

The program measures execution times for each mode and calculates speedups:
- **Serial Execution Time:** Baseline performance with one thread.
- **Parallel Execution Time:** Performance with multiple threads.
- **Speedup:** Ratio of serial execution time to parallel execution time.

Results are printed for each mode and thread count.

## Dependencies

- GCC with OpenMP support.
- Standard C libraries (`stdlib.h`, `string.h`, `time.h`).

## Configuration

The following parameters can be adjusted in `common.h`:
- `POPULATION_SIZE`: Total number of individuals in the population (default: 100).
- `STRING_LENGTH`: Length of each individual's string (default: 5).
- `MAX_GENERATIONS`: Number of generations for evolution (default: 1000).
- `MUTATION_RATE`: Probability of mutation (default: 0.1).

## Contributors

- **Fiordi Toska** - Project Developer
- Contributions welcome! Feel free to submit a pull request or raise an issue.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
