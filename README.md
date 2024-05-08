# Philosophers


## Description:

This repository contains the implementation of the classic dining philosophers problem in C. The problem involves a group of philosophers sitting at a round table, eating, thinking, and sleeping. The goal is to design a solution that prevents deadlocks and starvation.
## Project Structure

. philo.c: Main program file containing the entry point and logic.

. check_argcvs.c: Argument validation functions.

. fork_and_philo.c: Functions for initializing philosophers and forks.

. routine.c: Functions for the main philosopher routines.

. utils.c: Utility functions.

. philo.h: Header file containing function prototypes and data structures.

## Implementation Details

. Each philosopher is implemented as a thread.

. Mutexes are used to protect access to forks to prevent deadlocks.

. The program ensures that philosophers don't starve by tracking their eating times.

## Compilation

To compile the project, simply run 'make':

```bash
make
```
## Usage 
. Execute the program with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
. number_of_philosophers: The number of philosophers and forks on the table.

. time_to_die: Time in milliseconds before a philosopher dies if they haven't eaten.

. time_to_eat: Time in milliseconds for a philosopher to eat.

. time_to_sleep: Time in milliseconds for a philosopher to sleep.

. number_of_times_each_philosopher_must_eat (optional): The number of times each philosopher must eat before the simulation stops.

## Termination

The simulation stops when:

. A philosopher dies.

. All philosophers have eaten the specified number of times.
## 🚀 Next Project

[MiniShell](https://github.com/adhaka-afk/MINISHELL)

## ⏳ Previous Project

[Push_swap](https://github.com/adhaka-afk/PUSH_SWAP)

