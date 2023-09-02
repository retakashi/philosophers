/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:47:57 by reira             #+#    #+#             */
/*   Updated: 2023/09/03 00:06:38 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_philo(t_p_data *p_data)
{
	pthread_mutex_unlock(p_data->r_fork);
	pthread_mutex_unlock(p_data->l_fork);
	print_status(p_data, SLEEP);
	ft_sleep(p_data, p_data->cmn_data->sleep_time);
	print_status(p_data, THINK);
}

void	eat(t_p_data *p_data)
{
	pthread_mutex_lock(&p_data->cmn_data->cmn_lock);
	p_data->last_eat = gettimeofday_ms();
	pthread_mutex_unlock(&p_data->cmn_data->cmn_lock);
	print_status(p_data, EAT);
	ft_sleep(p_data, p_data->cmn_data->eat_time);
	pthread_mutex_lock(&p_data->cmn_data->cmn_lock);
	p_data->eat_cnt++;
	if (p_data->eat_cnt == p_data->cmn_data->until_eat)
		p_data->cmn_data->fin_cnt++;
	pthread_mutex_unlock(&p_data->cmn_data->cmn_lock);
	sleep_philo(p_data);
}

int	take_fork(t_p_data *p_data)
{
	if (p_data->i % 2 == 1)
	{
		pthread_mutex_lock(p_data->r_fork);
		print_status(p_data, TAKE);
		if (p_data->r_fork == p_data->l_fork)
		{
			pthread_mutex_unlock(p_data->r_fork);
			return (FAILURE);
		}
		pthread_mutex_lock(p_data->l_fork);
		print_status(p_data, TAKE);
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(p_data->l_fork);
		print_status(p_data, TAKE);
		usleep(100);
		pthread_mutex_lock(p_data->r_fork);
		print_status(p_data, TAKE);
	}
	if (p_data->cmn_data->until_eat == 0 || p_data->cmn_data->eat_time == 0)
	{
		pthread_mutex_unlock(p_data->r_fork);
		pthread_mutex_unlock(p_data->l_fork);
		return (FAILURE);
	}
	eat(p_data);
	return (SUCCESS);
}

void	*loop_philos(void *arg_data)
{
	t_p_data	*p_data;

	p_data = (t_p_data *)arg_data;
	if (p_data->cmn_data->total % 2 == 1)
	{
		ft_sleep(p_data, p_data->cmn_data->eat_time / p_data->cmn_data->total
			* p_data->i);
	}
	while (1)
	{
		pthread_mutex_lock(&p_data->cmn_data->cmn_lock);
		if (p_data->cmn_data->died != 0 || p_data->cmn_data->finished != 0)
		{
			pthread_mutex_unlock(&p_data->cmn_data->cmn_lock);
			break ;
		}
		pthread_mutex_unlock(&p_data->cmn_data->cmn_lock);
		if (take_fork(p_data) == FAILURE)
			break ;
	}
	return ((void *)SUCCESS);
}
