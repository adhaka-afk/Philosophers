/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:46:05 by adhaka            #+#    #+#             */
/*   Updated: 2023/10/30 23:00:46 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	a;
	int	sign;
	int	res;

	a = 0;
	sign = 1;
	res = 0;
	while (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			return (-1);
		a++;
	}
	while (str[a] != '\0' && (str[a] >= '0' && str[a] <= '9'))
	{
		res = (res * 10) + (str[a] - '0');
		a++;
	}
	return (res * sign);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;
	u_int64_t		t;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	t = (u_int64_t)tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	return (t);
}

void	ft_sleep(uint64_t st)
{
	uint64_t	t;

	t = get_time();
	while (get_time() - t < st)
		usleep(st);
}

void	initialize_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		exit(EXIT_FAILURE);
}

void	handle_error(const char *error_msg)
{
	perror(error_msg);
	exit(1);
}
