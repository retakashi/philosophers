/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/08/13 00:45:33 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define PHILOS 5
#define DELAY 5000
#define FOOD 50

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data
{
	int				i;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	elock;
	pthread_mutex_t	lock;
}					t_data;

time_t	ft_get_time(void)
{
	time_t			ans;
	time_t			start;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	usleep(100 * 1000);
	gettimeofday(&tv, NULL);
	ans = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	ans = ans - start;
	return (ans);
}

void	*func(void *f)
{
	t_data	*data;
	time_t	ans;
	int		i;

	ans=ft_get_time();
	data = (t_data *)f;
	// pthread_mutex_lock(&data->lock);
	i=data->i;
	if (i % 2 == 0)
	{
		pthread_mutex_lock(data->r_fork);
		printf("%d take a r_fork %ld\n", i, ans);
		pthread_mutex_lock(data->l_fork);
		printf("%d take a l_fork %ld\n", i, ans);
	}
	else
	{
		pthread_mutex_lock(data->l_fork);
		printf("%d take a l_fork %ld\n", i, ans);
		pthread_mutex_lock(data->r_fork);
		printf("%d take a r_fork %ld\n", i, ans);
	}
	// ans = ft_get_time();
	pthread_mutex_lock(&data->elock);
	ans = ft_get_time();
	printf("%d eat %ld\n", i, ans);
	pthread_mutex_unlock(&data->elock);
	if (i % 2 != 0)
	{
		pthread_mutex_unlock(data->l_fork);
		pthread_mutex_unlock(data->r_fork);
	}
	else
	{
		pthread_mutex_unlock(data->r_fork);
		pthread_mutex_unlock(data->l_fork);
	}
	// pthread_mutex_unlock(&data->lock);
	return (NULL);
}

int	main(void)
{
	struct timeval	tv;
	t_data			data[4];
	pthread_t		t_arr[4];
	pthread_mutex_t	r_fork[4];
	pthread_mutex_t	l_fork[4];
	int				i;

	i = 0;
	while (i < 4)
	{
		pthread_mutex_init(&data[i].lock, NULL);
		pthread_mutex_init(&data[i].elock, NULL);
		pthread_mutex_init(&r_fork[i], NULL);
		pthread_mutex_init(&l_fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		data[i].i = i;
		if (i < 3)
			data[i].l_fork = &l_fork[i + 1];
		else
			data[i].l_fork = &l_fork[0];
		data[i].r_fork = &r_fork[i];
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_create(&t_arr[i], NULL, &func, &data[i]);
		i++;
	}
	for (int i = 0; i < 4; i++)
		pthread_join(t_arr[i], NULL);
	return (0);
}
