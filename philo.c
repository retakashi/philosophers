/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/09/01 18:45:58 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_loop_philos(t_p_data *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->cmn_data->total)
	{
		if (pthread_create(&p_data->cmn_data->p_thread[i], NULL, &loop_philos,
				&p_data[i]) != 0)
			return (print_err("failed to pthread_create\n"));
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_cmn_data	cmn_data;
	int			i;

	if (init_data(&cmn_data, argc, argv) == FAILURE)
		return (FAILURE);
	cmn_data.start = gettimeofday_ms();
	if (start_loop_philos(cmn_data.p_data) == FAILURE)
		return (FAILURE);
	i = -1;
	while (++i < cmn_data.total)
	{
		if (pthread_join(cmn_data.p_thread[i], NULL) != 0)
			return (print_err("failed to pthread_join\n"));
	}
	return (SUCCESS);
}
