/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/08/31 23:35:30 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_status(void *arg_data)
{
	t_p_data	*p_data;

	p_data = (t_p_data *)arg_data;
	while (1)
	{
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

void	*loop_philos(void *arg_data)
{
	t_p_data	*p_data;

	p_data = (t_p_data *)arg_data;
	pthread_create(&p_data->monitor, NULL, &monitor_status, p_data);
	while (1)
	{
		if (p_data->cmn_data->died !=0
			|| p_data->cmn_data->finished !=0)
			break ;
		if (take_fork(p_data) != 0)
			return ((void *)FAILURE);
	}
	pthread_join(p_data->monitor, NULL);
	return ((void *)SUCCESS);
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
	cmn_data.start = gettimeofday_ms();
	while (++i < cmn_data.total)
	{
		if (pthread_create(&cmn_data.p_thread[i], NULL, &loop_philos,
				&cmn_data.p_data[i]) != 0)
			return (print_err("failed to pthread_create\n"));
	}
	i = -1;
	while (++i < cmn_data.total)
	{
		if (pthread_join(cmn_data.p_thread[i], NULL) != 0)
			return (print_err("failed to pthread_join\n"));
	}
	return (SUCCESS);
}
