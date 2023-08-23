/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/08/23 23:50:43 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define PHILOS 4
#define DELAY 5000
#define FOOD 50

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

pthread_mutex_t	forks[PHILOS];
typedef struct s_data
{
	int			i;
	int			cnt;
}				t_data;

time_t	ft_get_time(time_t start)
{
	time_t			ans;
	struct timeval	tv;

	usleep(100 * 1000);
	gettimeofday(&tv, NULL);
	ans = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	ans = ans - start;
	return (ans);
}

void	*func(void *data)
{
	t_data			*pdata;
	struct timeval	tv;
	time_t			start;

	pdata = (t_data *)data;
	gettimeofday(&tv, NULL);
	start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	while (1)
	{
		if (pdata->i % 2 == 0)
		{
			pthread_mutex_lock(&forks[pdata->i]);
			if (pdata->i < PHILOS - 1)
				pthread_mutex_lock(&forks[pdata->i + 1]);
			else
				pthread_mutex_lock(&forks[0]);
		}
		else
		{
			pthread_mutex_lock(&forks[pdata->i + 1]);
			pthread_mutex_lock(&forks[pdata->i]);
		}
		pdata->cnt++;
		printf("philos %d %ld eating cnt %d\n", pdata->i, ft_get_time(start),
			pdata->cnt);
		if (pdata->i % 2 == 0)
		{
			pthread_mutex_unlock(&forks[pdata->i]);
			if (pdata->i < PHILOS - 1)
				pthread_mutex_unlock(&forks[pdata->i + 1]);
			else
				pthread_mutex_unlock(&forks[0]);
		}
		else
		{
			pthread_mutex_unlock(&forks[pdata->i + 1]);
			pthread_mutex_unlock(&forks[pdata->i]);
		}
		printf("philos %d %ld thinking\n", pdata->i, ft_get_time(start));
		printf("philos %d %ld sleeping\n", pdata->i, ft_get_time(start));
	}
	return (pdata);
}

int	main(void)
{
	pthread_t	philos[PHILOS];
	t_data		pdata[PHILOS];
	int			i;

	i = 0;
	while (i < PHILOS)
	{
		pthread_mutex_init(&forks[i], NULL);
		pdata[i].i = i;
		pdata[i].cnt = 0;
		i++;
	}
	i = 0;
	while (i < PHILOS)
	{
		pthread_create(&philos[i], NULL, func, &pdata[i]);
		i++;
	}
	i = 0;
	while (i < PHILOS)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	return (0);
}
