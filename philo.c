/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/08/31 13:22:10 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_status(void *arg_data)
{
	t_p_data	*p_data;

	p_data = (t_p_data *)arg_data;
	while (1)
	{
		if (is_died(p_data) == true)
		{
			print_str(p_data, DIE);
			break ;
		}
		else if (is_finished(p_data) == true)
		{
			break ;
		}
	}
	return (p_data);
}

void	*loop_philos(void *arg_data)
{
	t_p_data	*p_data;

	p_data = (t_p_data *)arg_data;
	pthread_create(&p_data->monitor, NULL, &monitor_status, p_data);
	while (1)
	{
		pthread_mutex_lock(&p_data->cmn_data->died_lock);
		pthread_mutex_lock(&p_data->cmn_data->fin_lock);
		if (p_data->cmn_data->died == true
			|| p_data->cmn_data->finished == true)
		{
			pthread_mutex_unlock(&p_data->cmn_data->died_lock);
			pthread_mutex_unlock(&p_data->cmn_data->fin_lock);
			break ;
		}
		pthread_mutex_unlock(&p_data->cmn_data->died_lock);
		pthread_mutex_unlock(&p_data->cmn_data->fin_lock);
		take_fork(p_data);
		print_str(p_data, THINK);
	}
	pthread_join(p_data->monitor, NULL);
	return (p_data);
}

int	main(int argc, char **argv)
{
	t_cmn_data	cmn_data;
	int			i;

	if (argc == 5 || argc == 6)
	{
		if (init_data(&cmn_data, argv) == FAILURE)
			return (FAILURE);
	}
	else
		return (print_err("too few or too many arguments\n"));
	i = -1;
	cmn_data.start = get_millisecond();
	while (++i < cmn_data.total)
		pthread_create(&cmn_data.p_thread[i], NULL, &loop_philos,
			&cmn_data.p_data[i]);
	i = -1;
	while (++i < cmn_data.total)
		pthread_join(cmn_data.p_thread[i], NULL);
	return (0);
}
