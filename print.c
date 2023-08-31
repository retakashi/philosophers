/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:31:41 by reira             #+#    #+#             */
/*   Updated: 2023/09/01 01:12:07 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_err(char *str)
{
	printf("%s\n", str);
	return (FAILURE);
}

void	print_status(t_p_data *p_data, int flg)
{
	time_t	pr_time;

	if (p_data->cmn_data->died == 0 && p_data->cmn_data->finished == 0)
	{
		pr_time = gettimeofday_ms() - p_data->cmn_data->start;
		if (flg == TAKE)
			printf("%ld %d has taken a fork\n", pr_time, p_data->i);
		else if (flg == EAT)
			printf("%ld %d is eating\n", pr_time, p_data->i);
		else if (flg == SLEEP)
			printf("%ld %d is sleeping\n", pr_time, p_data->i);
		else if (flg == THINK)
			printf("%ld %d is thinking\n", pr_time, p_data->i);
	}
	else if (p_data->cmn_data->died != 0 && p_data->cmn_data->finished == 0)
	{
		pr_time = gettimeofday_ms() - p_data->cmn_data->start;
		printf("%ld %d died\n", pr_time, p_data->i);
		atomic_exchange(&p_data->cmn_data->finished, &p_data->cmn_data->finished
			+ 1);
	}
}
