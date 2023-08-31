/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:46:48 by reira             #+#    #+#             */
/*   Updated: 2023/08/31 13:08:17 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_died(t_p_data *p_data)
{
	time_t	current;

    current=get_millisecond();
	pthread_mutex_lock(&p_data->last_eat_lock);
	pthread_mutex_lock(&p_data->cmn_data->died_lock);
	current -= p_data->last_eat;
	if (p_data->last_eat != 0 && current >= p_data->cmn_data->die_time)
	{
		p_data->cmn_data->died = true;
		pthread_mutex_unlock(&p_data->last_eat_lock);
		pthread_mutex_unlock(&p_data->cmn_data->died_lock);
		return (true);
	}
	pthread_mutex_unlock(&p_data->last_eat_lock);
	pthread_mutex_unlock(&p_data->cmn_data->died_lock);
	return (false);
}

bool	is_finished(t_p_data *p_data)
{
	pthread_mutex_lock(&p_data->cmn_data->fin_lock);
	if (p_data->cmn_data->fin_cnt == p_data->cmn_data->until_eat)
	{
        p_data->cmn_data->finished=true;
		pthread_mutex_unlock(&p_data->cmn_data->fin_lock);
		return (true);
	}
	pthread_mutex_unlock(&p_data->cmn_data->fin_lock);
	return (false);
}
