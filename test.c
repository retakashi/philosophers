/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/08/30 22:40:37 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include<string.h>
#define SUCCESS 0
#define FAILURE -1

typedef struct s_p_data
{
	int				i;
	struct s_data	*data;
	int				eat_cnt;
	time_t			last_eat;
	bool			died;
	bool			fin;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_p_data;

typedef struct s_data
{
	int				total;
	time_t			die_time;
	time_t			eat_time;
	time_t			sleep_time;
	int				until_eat;
	struct s_p_data	*p_data;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	pthread_t		*philos;
}					t_data;

void	set_forks(t_data *data, int i)
{
	if (i < data->total - 1)
	{
		data->p_data->r_fork = &data->forks[i];
		data->p_data->l_fork = &data->forks[0];
	}
	else
	{
		data->p_data->r_fork = &data->forks[i];
		data->p_data->l_fork = &data->forks[i + 1];
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	pthread_mutex_init(data->lock, NULL);
	i = 0;
	while (i < data->total)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

int	init_p_data(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(pthread_t) * (data->total));
	if (data->philos == NULL)
		return (FAILURE);
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->total));
	if (data->forks == NULL)
		return (FAILURE);
	data->p_data = malloc(sizeof(t_p_data) * (data->total));
	if (data->p_data == NULL)
		return (FAILURE);
	init_mutex(data);
	i = -1;
	while (++i < data->total)
	{
		data->p_data[i].i = i;
		data->p_data[i].died = false;
		data->p_data[i].eat_cnt = 0;
		data->p_data[i].fin = false;
		data->p_data[i].last_eat = 0;
		set_forks(data, i);
	}
	return (SUCCESS);
}

int	set_argv(t_data *data, char **argv)
{
	int	total;

	total = atoi(argv[1]);
	if (total < 0)
		return (printf("invalid argv[1]\n"));
	data->die_time = (time_t)atoi(argv[2]);
	if (data->die_time < 0)
		return (printf("invalid argv[2]\n"));
	data->eat_time = (time_t)atoi(argv[3]);
	if (data->eat_time < 0)
		return (printf("invalid argv[3]\n"));
	data->sleep_time = (time_t)atoi(argv[4]);
	if (data->sleep_time < 0)
		return (printf("invalid argv[4]\n"));
	if (argv[5] != NULL)
	{
		data->until_eat = atoi(argv[5]);
		if (data->until_eat < 0)
			return (printf("invalid argv[5]\n"));
	}
	else
		data->until_eat = -1;
	data->total = total;
	return (SUCCESS);
}


int	main(int argc, char **argv)
{
	t_data		data;
	
	if (argc == 5 || argc == 6)
	{
		if (set_argv(&data, argv) == FAILURE)
			return (FAILURE);
		init_p_data(&data);
	}
	printf("data %d\n",data.until_eat);
	printf("p %d\n",data.p_data[3].i);
}
