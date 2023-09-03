/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:27:23 by reira             #+#    #+#             */
/*   Updated: 2023/09/03 13:15:47 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_cmn_data *data, int i)
{
	if (data->total == 1)
	{
		data->p_data[i].r_fork = &data->forks[0];
		data->p_data[i].l_fork = &data->forks[0];
	}
	else if (i == data->total - 1)
	{
		data->p_data[i].r_fork = &data->forks[0];
		data->p_data[i].l_fork = &data->forks[i];
	}
	else
	{
		data->p_data[i].r_fork = &data->forks[i + 1];
		data->p_data[i].l_fork = &data->forks[i];
	}
}

void	init_mutex(t_cmn_data *cmn_data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&cmn_data->cmn_lock, NULL);
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
		cmn_data->p_data[i].i = i + 1;
		cmn_data->p_data[i].eat_cnt = 0;
		cmn_data->p_data[i].last_eat = gettimeofday_ms();
		set_forks(cmn_data, i);
		cmn_data->p_data[i].cmn_data = cmn_data;
		i++;
	}
	return (SUCCESS);
}

int	init_data(t_cmn_data *cmn_data)
{
	cmn_data->died = false;
	cmn_data->finished = false;
	cmn_data->fin_cnt = 0;
	cmn_data->p_thread = malloc(sizeof(pthread_t) * (cmn_data->total));
	if (cmn_data->p_thread == NULL)
		return (print_err("failed to malloc p_thread\n"));
	cmn_data->monitor = malloc(sizeof(pthread_t) * (cmn_data->total));
	if (cmn_data->monitor == NULL)
		return (print_err("failed to malloc monitor\n"));
	cmn_data->forks = malloc(sizeof(pthread_mutex_t) * (cmn_data->total));
	if (cmn_data->forks == NULL)
		return (print_err("failed to malloc forks\n"));
	init_mutex(cmn_data);
	if (init_p_data(cmn_data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
