/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:28:45 by reira             #+#    #+#             */
/*   Updated: 2023/09/01 21:21:45 by reira            ###   ########.fr       */
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

void	ft_usleep(time_t arg_time)
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
