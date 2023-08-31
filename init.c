/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:27:23 by reira             #+#    #+#             */
/*   Updated: 2023/09/01 01:08:13 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_cmn_data *data, int i)
{
	if (i == data->total - 1)
	{
		data->p_data[i].r_fork = &data->forks[i];
		data->p_data[i].l_fork = &data->forks[0];
	}
	else
	{
		data->p_data[i].r_fork = &data->forks[i];
		data->p_data[i].l_fork = &data->forks[i + 1];
	}
}

void	init_mutex(t_cmn_data *cmn_data)
{
	int	i;

	i = 0;
	while (i < cmn_data->total)
	{
		pthread_mutex_init(&cmn_data->forks[i], NULL);
		i++;
	}
}

int	init_p_data(t_cmn_data *cmn_data)
{
	int	i;

	cmn_data->p_data = malloc(sizeof(t_p_data) * (cmn_data->total));
	if (cmn_data->p_data == NULL)
		return (print_err("failed to malloc p_data\n"));
	i = 0;
	while (i < cmn_data->total)
	{
		cmn_data->p_data[i].i = i;
		cmn_data->p_data[i].eat_cnt = 0;
		cmn_data->p_data[i].last_eat = 0;
		set_forks(cmn_data, i);
		cmn_data->p_data[i].cmn_data = cmn_data;
		pthread_mutex_init(&cmn_data->p_data[i].last_eat_lock, NULL);
		i++;
	}
	return (SUCCESS);
}

int	set_argv(t_cmn_data *data, char **argv)
{
	int	total;

	total = ft_atoi(argv[1]);
	if (total < 0)
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
	if (argv[5] != NULL)
	{
		data->until_eat = ft_atoi(argv[5]);
		if (data->until_eat < 0)
			return (print_err("invalid argv[5]\n"));
	}
	else
		data->until_eat = -1;
	data->total = total;
	return (SUCCESS);
}

int	init_data(t_cmn_data *cmn_data, char **argv)
{
	if (set_argv(cmn_data, argv) == FAILURE)
		return (FAILURE);
	cmn_data->died = 0;
	cmn_data->finished = 0;
	cmn_data->fin_cnt = 0;
	cmn_data->p_thread = malloc(sizeof(pthread_t) * (cmn_data->total));
	if (cmn_data->p_thread == NULL)
		return (print_err("failed to malloc p_thread\n"));
	cmn_data->forks = malloc(sizeof(pthread_mutex_t) * (cmn_data->total));
	if (cmn_data->forks == NULL)
		return (print_err("failed to malloc forks\n"));
	init_mutex(cmn_data);
	if (init_p_data(cmn_data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
