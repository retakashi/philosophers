/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:47:57 by reira             #+#    #+#             */
/*   Updated: 2023/08/31 13:00:13 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_philo(t_p_data *p_data)
{
	if (p_data->i % 2 == 0)
	{
		pthread_mutex_unlock(p_data->r_fork);
		pthread_mutex_unlock(p_data->l_fork);
	}
	else
	{
		pthread_mutex_unlock(p_data->l_fork);
		pthread_mutex_unlock(p_data->r_fork);
	}
	print_str(p_data, SLEEP);
	ft_usleep(p_data->cmn_data->sleep_time);
}

void	eat(t_p_data *p_data)
{
	pthread_mutex_lock(&p_data->last_eat_lock);
	p_data->last_eat = get_millisecond();
	pthread_mutex_unlock(&p_data->last_eat_lock);
	print_str(p_data, EAT);
	ft_usleep(p_data->cmn_data->eat_time);
	p_data->eat_cnt++;
	pthread_mutex_lock(&p_data->cmn_data->fin_lock);
	if (p_data->eat_cnt == p_data->cmn_data->until_eat)
		p_data->cmn_data->fin_cnt++;
	pthread_mutex_unlock(&p_data->cmn_data->fin_lock);
	sleep_philo(p_data);
}

void	take_fork(t_p_data *p_data)
{
	if (p_data->i % 2 == 0)
	{
		pthread_mutex_lock(p_data->r_fork);
		print_str(p_data, TAKE);
		pthread_mutex_lock(p_data->l_fork);
		print_str(p_data, TAKE);
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(p_data->l_fork);
		print_str(p_data, TAKE);
		usleep(100);
		pthread_mutex_lock(p_data->r_fork);
		print_str(p_data, TAKE);
	}
	eat(p_data);
}
