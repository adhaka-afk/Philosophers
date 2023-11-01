/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:46:02 by adhaka            #+#    #+#             */
/*   Updated: 2023/10/30 23:26:39 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				free_fork;
}	t_fork;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	t_fork			*forks;
	pthread_mutex_t	g_mutex;
	pthread_mutex_t	m_mutex;
	u_int64_t		tt_eat;
	u_int64_t		tt_sleep;
	u_int64_t		tt_die;
	u_int64_t		start;
	int				nb_philo;
	int				nb_eat;
	int				dead;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	t_fork		*left_f;
	t_fork		*right_f;
	int			id;
	int			state;
	int			nb_meals;
	u_int64_t	last_meal;
	pthread_t	thread;
	t_data		*data;
}	t_philo;

// arg check func.
int			check_argcvs(int argc, char **argv);
int			check_argc(int argc);
int			check_argv(char **argv);

// fork & philo func.
void		fill_ev(t_data *data, int argc, char **argv);
t_fork		*put_forks(int nb);
t_philo		*put_philos(t_data *data);
t_fork		*ob_fork(int a, t_data *data, int c);

// util func.
int			ft_atoi(const char *str);
u_int64_t	get_time(void);
void		ft_sleep(uint64_t st);
void		initialize_mutex(pthread_mutex_t *mutex);
void		handle_error(const char *error_msg);
void		free_all(t_data *data, t_philo *philos);

//routine func.
void		verify(t_philo *philos, t_data *data);
int			dine(t_philo *bhojan);
void		*philosopher_routine(void *philosopher);
void		print_action(char *msg, t_philo *philo, int val);
int			check_philosopher_starvation(t_philo *philo);
int			exec(t_data *data);

#endif
