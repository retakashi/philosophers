/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:47:57 by reira             #+#    #+#             */
/*   Updated: 2023/09/01 00:24:30 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_philo(t_p_data *p_data)
{
	if (p_data->i % 2 == 0)
	{
		if (pthread_mutex_unlock(p_data->r_fork) != 0)
			return (print_err("failed to pthread_mutex_unlock\n"));
		if (pthread_mutex_unlock(p_data->l_fork) != 0)
			return (print_err("failed to pthread_mutex_unlock\n"));
	}
	else
	{
		if (pthread_mutex_unlock(p_data->l_fork) != 0)
			return (print_err("failed to pthread_mutex_unlock\n"));
		if (pthread_mutex_unlock(p_data->r_fork) != 0)
			return (print_err("failed to pthread_mutex_unlock\n"));
	}
	print_status(p_data, SLEEP);
	ft_usleep(p_data->cmn_data->sleep_time);
	print_status(p_data, THINK);
	return (SUCCESS);
}

int	eat(t_p_data *p_data)
{
	if (pthread_mutex_lock(&p_data->last_eat_lock) != 0)
		return (print_err("failed to pthread_mutex_lock\n"));
	p_data->last_eat = gettimeofday_ms();
	if (pthread_mutex_unlock(&p_data->last_eat_lock) != 0)
		return (print_err("failed to pthread_mutex_unlock\n"));
	print_status(p_data, EAT);
	ft_usleep(p_data->cmn_data->eat_time);
	p_data->eat_cnt++;
	if (p_data->eat_cnt == p_data->cmn_data->until_eat)
		p_data->cmn_data->fin_cnt++;	
	if (sleep_philo(p_data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	take_fork(t_p_data *p_data)
{
	if (p_data->i % 2 == 0)
	{
		if (pthread_mutex_lock(p_data->r_fork) != 0)
			return (print_err("failed to pthread_mutex_lock\n"));
		print_status(p_data, TAKE);
		if (pthread_mutex_lock(p_data->l_fork) != 0)
			return (print_err("failed to pthread_mutex_lock\n"));
		print_status(p_data, TAKE);
	}
	else
	{
		usleep(100);
		if (pthread_mutex_lock(p_data->l_fork) != 0)
			return (print_err("failed to pthread_mutex_lock\n"));
		print_status(p_data, TAKE);
		usleep(100);
		if (pthread_mutex_lock(p_data->r_fork) != 0)
			return (print_err("failed to pthread_mutex_lock\n"));
		print_status(p_data, TAKE);
	}
	if (eat(p_data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
