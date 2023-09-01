/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/09/01 23:13:47 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philos(t_p_data *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->cmn_data->total)
	{
		if (pthread_create(&p_data->cmn_data->monitor[i], NULL, &monitor_status,
				&p_data[i]) != 0)
			return (print_err("failed to pthread_create monitor\n"));
		if (pthread_create(&p_data->cmn_data->p_thread[i], NULL, &loop_philos,
				&p_data[i]) != 0)
			return (print_err("failed to pthread_create p_thread\n"));
		i++;
	}
	return (SUCCESS);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }

int	end_philos(t_p_data *p_data)
{
	int	i;

	i = -1;
	while (++i < p_data->cmn_data->total)
	{
		if (pthread_join(p_data->cmn_data->monitor[i], NULL) != 0)
			return (print_err("failed to pthread_join\n"));
	}
	i = -1;
	while (++i < p_data->cmn_data->total)
	{
		if (pthread_join(p_data->cmn_data->p_thread[i], NULL) != 0)
			return (print_err("failed to pthread_join\n"));
	}
	return (SUCCESS);
}

void	free_all(t_cmn_data *data)
{
	if (data->forks != NULL)
		free(data->forks);
	if (data->p_thread != NULL)
		free(data->p_thread);
	if (data->monitor != NULL)
		free(data->monitor);
	if (data->p_data != NULL)
		free(data->p_data);
}

int	main(int argc, char **argv)
{
	t_cmn_data	cmn_data;

	if (init_data(&cmn_data, argc, argv) == FAILURE)
	{
		free_all(&cmn_data);
		return (FAILURE);
	}
	cmn_data.start = gettimeofday_ms();
	if (start_philos(cmn_data.p_data) == FAILURE)
	{
		free_all(&cmn_data);
		return (FAILURE);
	}
	if (end_philos(cmn_data.p_data) == FAILURE)
	{
		free_all(&cmn_data);
		return (FAILURE);
	}
	free_all(&cmn_data);
	return (SUCCESS);
}
