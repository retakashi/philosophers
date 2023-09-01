/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 00:19:53 by reira             #+#    #+#             */
/*   Updated: 2023/09/02 00:22:12 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_until_eat(t_cmn_data *data, char **argv)
{
	if (argv[5] != NULL)
	{
		data->until_eat = ft_atoi(argv[5]);
		if (data->until_eat < 0)
			return (print_err("invalid argv[5]\n"));
	}
	else
		data->until_eat = -1;
	return (SUCCESS);
}

int	is_valid_argv(t_cmn_data *data, int argc, char **argv)
{
	int	total;

	if (argc != 5 && argc != 6)
		return (print_err("too few or too many arguments\n"));
	total = ft_atoi(argv[1]);
	if (total <= 0)
		return (print_err("invalid argv[1]\n"));
	data->die_time = (time_t)ft_atoi(argv[2]);
	if (data->die_time < 0)
		return (print_err("invalid argv[2]\n"));
	data->eat_time = (time_t)ft_atoi(argv[3]);
	if (data->eat_time < 0)
		return (print_err("invalid argv[3]\n"));
	data->sleep_time = (time_t)ft_atoi(argv[4]);
	if (data->sleep_time < 0)
		return (print_err("invalid argv[4]\n"));
	data->total = total;
	return (is_valid_until_eat(data, argv));
}
