/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/08/28 23:38:04 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#define SUCCESS 0
#define FAILURE -1
#define PHILOS 4
#define DELAY 5000
#define FOOD 50

pthread_mutex_t	forks[PHILOS];
typedef struct s_data
{
	int			i;
	int			total;
	int			eat_cnt;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			until_eat;
	int			died;
}				t_data;

time_t	get_millisecond(void)
{
	time_t			ans;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ans = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ans);
}

time_t	ft_usleep(time_t arg_time)
{
	time_t	current;
	time_t	ret;

	current = get_millisecond();
	ret = current;
	while (ret < current + arg_time)
	{
		usleep(arg_time / 10);
		ret = get_millisecond();
	}
	return (ret);
}

void	put_fork(t_data *pdata)
{
	if (pdata->i % 2 == 0)
	{
		pthread_mutex_unlock(&forks[pdata->i]);
		if (pdata->i == pdata->total - 1)
			pthread_mutex_unlock(&forks[0]);
		else
			pthread_mutex_unlock(&forks[pdata->i + 1]);
	}
	else
	{
		if (pdata->i == pdata->total - 1)
			pthread_mutex_unlock(&forks[0]);
		else
			pthread_mutex_unlock(&forks[pdata->i + 1]);
		pthread_mutex_unlock(&forks[pdata->i]);
	}
}

void	sleep_philo(t_data *pdata, time_t start)
{
	printf("%ld %d is sleeping\n", ft_usleep((time_t)pdata->sleep_time) - start,
		pdata->i);
}

void	eat(t_data *pdata, time_t start)
{
	printf("%ld %d is eating\n", ft_usleep((time_t)pdata->eat_time) - start,
		pdata->i);
	pdata->eat_cnt++;
	put_fork(pdata);
}

void	take_fork(t_data *pdata, time_t start)
{
	if (pdata->i % 2 == 0)
	{
		pthread_mutex_lock(&forks[pdata->i]);
		if (pdata->i == pdata->total - 1)
			pthread_mutex_lock(&forks[0]);
		else
			pthread_mutex_lock(&forks[pdata->i + 1]);
	}
	else
	{
		if (pdata->i == pdata->total - 1)
			pthread_mutex_lock(&forks[0]);
		else
			pthread_mutex_lock(&forks[pdata->i + 1]);
		pthread_mutex_lock(&forks[pdata->i]);
	}
	printf("%ld %d has taken a fork\n", ft_usleep(0) - start, pdata->i);
	eat(pdata, start);
}

void	*func(void *data)
{
	t_data	*pdata;
	time_t	start;

	pdata = (t_data *)data;
	start = get_millisecond();
	while (check_philo_status())
	{
		take_fork(pdata, start);
		sleep_philo(pdata, start);
		printf("%ld %d is thinking\n", ft_usleep(0)-start, pdata->i);
	}
	return (pdata);
}

int	pdata_init(t_data **pdata, pthread_t **philos, char **argv)
{
	int	i;
	int	total;

	i = 0;
	total = atoi(argv[1]);
	if (total == -1)
		return (printf("invalid argv\n"));
	*philos = malloc(sizeof(pthread_t) * total);
	if (*philos == NULL)
		return (printf("faile to malloc philos\n"));
	*pdata = malloc(sizeof(t_data) * total);
	if (*pdata == NULL)
		return (printf("faile to malloc pdata\n"));
	while (i < total)
	{
		(*pdata)[i].i = i;
		(*pdata)[i].eat_cnt = 0;
		(*pdata)[i].total = total;
		(*pdata)[i].die_time = atoi(argv[2]);
		(*pdata)[i].eat_time = atoi(argv[3]);
		(*pdata)[i].sleep_time = atoi(argv[4]);
		if (argv[5] != NULL)
			(*pdata)[i].until_eat = atoi(argv[5]);
		else
			(*pdata)[i].until_eat = 0;
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	pthread_t	*philos;
	t_data		*pdata;
	int			i;

	if (argc == 5 || argc == 6)
		pdata_init(&pdata, &philos, argv);
	else
		return (printf("too few or too many arguments\n"));
	i = 0;
	while (i < pdata->total)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < pdata->total)
	{
		pthread_create(&philos[i], NULL, func, &pdata[i]);
		i++;
	}
	i = 0;
	while (i < pdata->total)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	return (0);
}
