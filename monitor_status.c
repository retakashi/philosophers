/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:46:48 by reira             #+#    #+#             */
/*   Updated: 2023/09/01 21:38:14 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_died(t_p_data *p_data)
{
	time_t	time_left;

	pthread_mutex_lock(&p_data->cmn_data->cmn_lock);
	time_left = p_data->cmn_data->die_time - (gettimeofday_ms()
			- p_data->last_eat);
	pthread_mutex_unlock(&p_data->cmn_data->cmn_lock);
	if (time_left <= 0)
	{
		pthread_mutex_lock(&p_data->cmn_data->cmn_lock);
		p_data->cmn_data->died = true;
		pthread_mutex_unlock(&p_data->cmn_data->cmn_lock);
		return (TRUE);
	}
	return (FALSE);
}

int	is_finished(t_p_data *p_data)
{
	pthread_mutex_lock(&p_data->cmn_data->cmn_lock);
	if (p_data->cmn_data->fin_cnt == p_data->cmn_data->total)
	{
		p_data->cmn_data->finished = true;
		pthread_mutex_unlock(&p_data->cmn_data->cmn_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&p_data->cmn_data->cmn_lock);
	return (FALSE);
}

void	*monitor_status(void *arg_data)
{
	t_p_data	*p_data;

	p_data = (t_p_data *)arg_data;
	while (1)
	{
		usleep(2000);
		if (is_died(p_data) == FAILURE || is_finished(p_data) == FAILURE)
			return ((void *)FAILURE);
		if (is_died(p_data) == TRUE)
		{
			print_status(p_data, DIE);
			break ;
		}
		else if (is_finished(p_data) == TRUE)
			break ;
	}
	return ((void *)SUCCESS);
}
