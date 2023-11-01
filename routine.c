/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:18:27 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/01 23:36:38 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_starvation(t_philo *philo)
{
	u_int64_t		current_time;
	struct timeval	dt;

	gettimeofday(&dt, NULL);
	current_time = get_time() - philo->last_meal;
	if (current_time > philo->data->tt_die)
	{
		if (philo->state != 0)
		{
			philo->state = 0;
			printf("%-8lld %d died\n", get_time()
				- philo->data->start, philo->id);
			return (0);
		}
	}
	return (1);
}

void	verify(t_philo *philos, t_data *data)
{
	int	a;

	while (!data->dead)
	{
		a = -1;
		while (++a < data->nb_philo)
		{
			pthread_mutex_lock(&(data->g_mutex));
			pthread_mutex_lock(&(data->m_mutex));
			if (get_time() - philos[a].last_meal > data->tt_die)
			{
				data->dead = 1;
				if (philos[a].nb_meals < data->nb_eat)
					printf("%-8lld %d died\n",
						get_time() - data->start, philos[a].id);
				pthread_mutex_unlock(&(data->g_mutex));
				pthread_mutex_unlock(&(data->m_mutex));
				exit(0);
			}
			pthread_mutex_unlock(&(data->g_mutex));
			pthread_mutex_unlock(&(data->m_mutex));
			ft_sleep(1);
		}
	}
}

int	dine(t_philo *bhojan)
{
	pthread_mutex_lock(&(bhojan->right_f->fork));
	print_action("has taken a fork", bhojan, 0);
	if (bhojan->left_f)
	{
		pthread_mutex_lock(&(bhojan->left_f->fork));
		print_action("has taken a fork", bhojan, 0);
		pthread_mutex_lock(&(bhojan->data->g_mutex));
		if (bhojan->data->dead)
		{
			pthread_mutex_unlock(&(bhojan->data->g_mutex));
			pthread_mutex_unlock(&(bhojan->right_f->fork));
			pthread_mutex_unlock(&(bhojan->left_f->fork));
			return (0);
		}
		print_action("is eating", bhojan, 1);
		bhojan->nb_meals++;
		pthread_mutex_unlock(&(bhojan->data->g_mutex));
		ft_sleep(bhojan->data->tt_eat);
	}
	pthread_mutex_unlock(&(bhojan->right_f->fork));
	if (bhojan->left_f)
		pthread_mutex_unlock(&(bhojan->left_f->fork));
	return (1);
}

void	*philosopher_routine(void *philosopher)
{
	t_philo	*philo;

	philo = philosopher;
	if (philo->id % 2 == 0)
		ft_sleep(philo->data->tt_eat / 2);
	while (philo->state && philo->nb_meals < philo->data->nb_eat)
	{
		if (!check_philosopher_starvation(philo))
			return (NULL);
		if (!dine(philo))
			return (NULL);
		if (philo->nb_meals == philo->data->nb_eat)
			return (NULL);
		print_action("is sleeping", philo, 0);
		ft_sleep(philo->data->tt_sleep);
		print_action("is thinking", philo, 0);
	}
	return (NULL);
}

void	print_action(char *msg, t_philo *philo, int val)
{
	struct timeval	t;
	uint64_t		dt;

	pthread_mutex_lock(&(philo->data->m_mutex));
	gettimeofday(&t, NULL);
	dt = get_time() - philo->data->start;
	if (val == 1)
		philo->last_meal = get_time();
	if (!philo->data->dead)
		printf("%-8lld %d %s\n", dt, philo->id, msg);
	pthread_mutex_unlock(&(philo->data->m_mutex));
}
