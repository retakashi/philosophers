/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/08/25 00:39:59 by reira            ###   ########.fr       */
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
	int			die;
	int			eat;
	int			sleep;
	int			until_eat;
	int			died;
}				t_data;

time_t	ft_get_time(time_t start, int arg_time)
{
	time_t			ans;
	struct timeval	tv;

	usleep((useconds_t)arg_time * 1000);
	gettimeofday(&tv, NULL);
	ans = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	ans = ans - start;
	return (ans);
}

void	take_fork_eat(t_data *pdata, time_t start)
{
	int right_fork = pdata->i;
    int left_fork = (pdata->i + 1) % pdata->total;

	pthread_mutex_lock(&forks[right_fork]);
    pthread_mutex_lock(&forks[left_fork]);
	printf("%ld %d has taken a fork\n", ft_get_time(start, 0), pdata->i);
	printf("%ld %d is eating\n", ft_get_time(start, pdata->eat), pdata->i);
	pdata->eat_cnt++;
	pthread_mutex_unlock(&forks[right_fork]);
    pthread_mutex_unlock(&forks[left_fork]);
}

void	put_fork_sleep(t_data *pdata, time_t start)
{
	printf("%ld %d is sleeping\n", ft_get_time(start, pdata->sleep), pdata->i);
}

void	*func(void *data)
{
	t_data			*pdata;
	struct timeval	tv;
	time_t			start;
	int				i;

	pdata = (t_data *)data;
	gettimeofday(&tv, NULL);
	start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	i = 0;
	while (i < pdata->total)
	{
		take_fork_eat(pdata, start);
		put_fork_sleep(pdata, start);
		printf("%ld %d is thinking\n", ft_get_time(start, 0), pdata->i);
		i++;
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
		return (write(STDERR_FILENO, "invalid argv\n",
				strlen("invalid argv\n")));
	*philos = malloc(sizeof(pthread_t) * total);
	if (*philos == NULL)
		return (write(STDERR_FILENO, "faile to malloc philos\n",
				strlen("faile to malloc philos\n")));
	*pdata = malloc(sizeof(t_data) * total);
	if (*pdata == NULL)
		return (write(STDERR_FILENO, "faile to malloc pdata\n",
				strlen("faile to malloc pdata\n")));
	while (i < total)
	{
		(*pdata)[i].i = i;
		(*pdata)[i].eat_cnt = 0;
		(*pdata)[i].total = total;
		(*pdata)[i].die = atoi(argv[2]);
		(*pdata)[i].eat = atoi(argv[3]);
		(*pdata)[i].sleep = atoi(argv[4]);
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
		return (write(STDERR_FILENO, "too few or too many arguments\n",
				strlen("too few or too many arguments\n")));
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
