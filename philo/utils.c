/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:28:45 by reira             #+#    #+#             */
/*   Updated: 2023/09/03 22:40:42 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	gettimeofday_ms(void)
{
	time_t			ans;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ans = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ans);
}

static void	ft_usleep(time_t arg_time)
{
	usleep(arg_time * 1000);
}

static void	ft_gettimeofday_sleep(time_t arg_time)
{
	time_t	current;
	time_t	ret;

	current = gettimeofday_ms();
	ret = current;
	while (ret < current + arg_time)
	{
		ret = gettimeofday_ms();
	}
}

//6人未満はusleepより正確に時間を測定した方が死なない
void	ft_sleep(t_p_data *p_data, time_t arg_time)
{
	if (p_data->cmn_data->total < 6)
		ft_gettimeofday_sleep(arg_time);
	else
		ft_usleep(arg_time);
}
