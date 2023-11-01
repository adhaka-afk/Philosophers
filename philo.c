/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:45:59 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/01 23:34:56 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exec(t_data *data)
{
	int		a;
	t_philo	*philos;

	philos = (t_philo *)(data->philos);
	a = -1;
	while (++a < data->nb_philo)
		if (pthread_create(&(philos[a].thread), NULL, \
			&philosopher_routine, &philos[a]) != 0)
			return (-1);
	verify(philos, data);
	a = -1;
	while (++a < data->nb_philo)
		if (pthread_join(philos[a].thread, NULL) != 0)
			return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;
	t_fork	*forks;
	int		run;

	if (check_argcvs(argc, argv) == 1)
		fill_ev(&data, argc, argv);
	else
		handle_error("wrong args");
	forks = put_forks(data.nb_philo);
	if (!forks)
		handle_error("fork malloc faliure");
	data.forks = forks;
	philos = put_philos(&data);
	if (!philos)
		handle_error("philo malloc faliure");
	data.philos = philos;
	run = exec(&data);
	if (run != 0)
		handle_error("runtime error");
	free_all(&data, philos);
	return (EXIT_SUCCESS);
}

void	free_all(t_data *data, t_philo *philos)
{
	int	a;

	a = 0;
	while (a < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->forks[a].fork));
		a++;
	}
	pthread_mutex_destroy(&(data->g_mutex));
	pthread_mutex_destroy(&(data->m_mutex));
	free(data->forks);
	free(philos);
}
