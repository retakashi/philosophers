/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:31:41 by reira             #+#    #+#             */
/*   Updated: 2023/08/31 16:02:54 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_err(char *str)
{
	printf("%s\n", str);
	return (FAILURE);
}

void	print_str(t_p_data *p_data, int flg)
{
	time_t	pr_time;

	pthread_mutex_lock(&p_data->cmn_data->died_lock);
	pthread_mutex_lock(&p_data->cmn_data->fin_lock);
	pr_time = get_millisecond() - p_data->cmn_data->start;
	if (p_data->cmn_data->finished == false)
	{
		if (flg == TAKE)
			printf("%ld %d has taken a fork\n", pr_time, p_data->i);
		else if (flg == EAT)
			printf("%ld %d is eating\n", pr_time, p_data->i);
		else if (flg == SLEEP)
			printf("%ld %d is sleeping\n", pr_time, p_data->i);
		else if (flg == THINK)
			printf("%ld %d is thinking\n", pr_time, p_data->i);
	}
	if (p_data->cmn_data->died == true && p_data->cmn_data->finished == false)
	{
		printf("%ld %d died\n", pr_time, p_data->i);
		p_data->cmn_data->finished = true;
	}
	pthread_mutex_unlock(&p_data->cmn_data->fin_lock);
	pthread_mutex_unlock(&p_data->cmn_data->died_lock);
}
