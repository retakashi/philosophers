/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:46:48 by reira             #+#    #+#             */
/*   Updated: 2023/09/01 01:10:57 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_died(t_p_data *p_data)
{
	time_t	current;

	current = gettimeofday_ms();
	if (pthread_mutex_lock(&p_data->last_eat_lock) != 0)
		return (print_err("failed to pthread_mutex_lock\n"));
	current -= p_data->last_eat;
	if (pthread_mutex_unlock(&p_data->last_eat_lock) != 0)
		return (print_err("failed to pthread_mutex_unlock\n"));
	if (p_data->last_eat != 0 && current > p_data->cmn_data->die_time)
	{
        atomic_exchange(&p_data->cmn_data->died, &p_data->cmn_data->died+1);
		return (TRUE);
	}
	return (FALSE);
}

int	is_finished(t_p_data *p_data)
{
	if (p_data->cmn_data->fin_cnt == p_data->cmn_data->until_eat)
	{
		atomic_exchange(&p_data->cmn_data->finished, &p_data->cmn_data->finished+1);
		return (TRUE);
	}
	return (FALSE);
}
