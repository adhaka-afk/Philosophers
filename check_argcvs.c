/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argcvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:32:25 by adhaka            #+#    #+#             */
/*   Updated: 2023/10/30 17:32:59 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argcvs(int argc, char **argv)
{
	if (check_argc(argc) == 0)
		return (0);
	if (check_argv(argv) == 0)
		return (0);
	return (1);
}

int	check_argc(int argc)
{
	if (argc < 5)
	{
		printf("Error : Atleast 4 arguments required, in this order- <number_of_philosophers> \
			<time_to_die> <time_to_eat> <time_to_sleep> \
			<[number_of_times_each_philosopher_must_eat]>\n");
		return (0);
	}
	if (argc > 6)
	{
		printf("Error : Atmost 5 arguments allowed, in this order- <number_of_philosophers> \
			<time_to_die> <time_to_eat> <time_to_sleep> \
			<[number_of_times_each_philosopher_must_eat]>\n");
		return (0);
	}
	return (1);
}

int	check_argv(char **argv)
{
	if (ft_atoi(argv[1]) == 0)
	{
		printf("Error : Can't have 0 philos my guy\n");
		return (0);
	}
	if ((ft_atoi(argv[1]) == -1) || (ft_atoi(argv[2]) == -1) \
		|| (ft_atoi(argv[3]) == -1) || (ft_atoi(argv[4]) == -1))
	{
		printf("Error : provide +ve args only\n");
		return (0);
	}
	if (argv[5])
	{
		if (ft_atoi(argv[5]) == -1)
		{
			printf("Error : provide +ve args only\n");
			return (0);
		}
	}
	return (1);
}
