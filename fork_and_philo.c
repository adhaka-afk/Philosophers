/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:45:53 by adhaka            #+#    #+#             */
/*   Updated: 2023/10/29 22:56:40 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_ev(t_data *data, int argc, char **argv)
{
	struct timeval	t;

	data->nb_philo = ft_atoi(argv[1]);
	data->tt_die = (u_int64_t) ft_atoi(argv[2]);
	data->tt_eat = (u_int64_t) ft_atoi(argv[3]);
	data->tt_sleep = (u_int64_t) ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = INT_MAX;
	initialize_mutex(&data->g_mutex);
	initialize_mutex(&data->m_mutex);
	if (gettimeofday(&t, NULL) != 0)
		exit(EXIT_FAILURE);
	data->start = (u_int64_t)t.tv_sec * 1000 + (t.tv_usec / 1000);
	data->dead = 0;
}

t_fork	*put_forks(int nb)
{
	int		a;
	t_fork	*forks;

	a = 0;
	forks = malloc(sizeof(t_fork) * nb);
	if (!forks)
		return (NULL);
	while (a < nb)
	{
		initialize_mutex(&(forks[a].fork));
		forks[a].free_fork = 1;
		a++;
	}
	return (forks);
}

t_philo	*put_philos(t_data *data)
{
	int		a;
	t_philo	*philos;

	a = 0;
	philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philos)
		return (NULL);
	while (a < data->nb_philo)
	{
		philos[a].id = a + 1;
		philos[a].state = 1;
		philos[a].nb_meals = 0;
		philos[a].last_meal = data->start;
		philos[a].left_f = ob_fork(a, data, 1);
		philos[a].right_f = ob_fork(a, data, 0);
		philos[a].data = data;
		a++;
	}
	return (philos);
}

t_fork	*ob_fork(int a, t_data *data, int c)
{
	if (c == 0)
	{
		if (a == data->nb_philo - 1)
			return (&(data->forks[0]));
		else
			return (&(data->forks[a]));
	}
	else if (c == 1)
	{
		if (a == data->nb_philo - 1)
		{
			if (data->nb_philo == 1)
				return (NULL);
			else
				return (&(data->forks[a]));
		}
		else
			return (&(data->forks[a + 1]));
	}
	return (NULL);
}
