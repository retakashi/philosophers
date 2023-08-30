/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/08/30 22:58:27 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_philo(t_p_data *p_data)
{
	if (p_data->i % 2 == 0)
	{
		pthread_mutex_unlock(p_data->r_fork);
		pthread_mutex_unlock(p_data->l_fork);
	}
	else
	{
		pthread_mutex_unlock(p_data->l_fork);
		pthread_mutex_unlock(p_data->r_fork);
	}
	printf("%ld %d is sleeping\n", ft_usleep(p_data->cmn_data->sleep_time)
		- p_data->cmn_data->start, p_data->i);
}

void	eat(t_p_data *p_data)
{
	p_data->last_eat = get_millisecond();
	printf("%ld %d is eating\n", ft_usleep(p_data->cmn_data->eat_time)
		- p_data->cmn_data->start, p_data->i);
	p_data->eat_cnt++;
	sleep_philo(p_data);
}

void	take_fork(t_p_data *p_data)
{
	if (p_data->i % 2 == 0)
	{
		pthread_mutex_lock(p_data->r_fork);
		printf("%ld %d has taken a fork\n", ft_usleep(0)
			- p_data->cmn_data->start, p_data->i);
		pthread_mutex_lock(p_data->l_fork);
		printf("%ld %d has taken a fork\n", ft_usleep(0)
			- p_data->cmn_data->start, p_data->i);
	}
	else
	{
		pthread_mutex_lock(p_data->l_fork);
		printf("%ld %d has taken a fork\n", ft_usleep(0)
			- p_data->cmn_data->start, p_data->i);
		pthread_mutex_lock(p_data->r_fork);
		printf("%ld %d has taken a fork\n", ft_usleep(0)
			- p_data->cmn_data->start, p_data->i);
	}
	eat(p_data);
}

void	*monitor_status(void *arg_data)
{
	t_p_data	*p_data;
	time_t		current;

	p_data = (t_p_data *)arg_data;
	while (p_data->cmn_data->died == false)
	{
		// pthread_mutex_lock(&p_data->p_lock);
		current = get_millisecond();
		if (current - p_data->last_eat >= p_data->cmn_data->die_time)
		{
			pthread_mutex_lock(&p_data->cmn_data->lock);	
			p_data->cmn_data->died = true;
			printf("%ld %d died\n", current - p_data->cmn_data->start,p_data->i);
			pthread_mutex_unlock(&p_data->cmn_data->lock);
		}
		// pthread_mutex_unlock(&p_data->p_lock);
	}
	return (p_data);
}

void	*loop_philos(void *arg_data)
{
	t_p_data	*p_data;

	p_data = (t_p_data *)arg_data;
	pthread_create(&p_data->monitor, NULL, &monitor_status, p_data);
	while (p_data->cmn_data->died == false)
	{
		take_fork(p_data);
		printf("%ld %d is thinking\n", ft_usleep(0) - p_data->cmn_data->start,
			p_data->i);
	}
	pthread_join(p_data->monitor, NULL);
	return (p_data);
}

int	main(int argc, char **argv)
{
	t_cmn_data	cmn_data;
	int			i;

	if (argc == 5 || argc == 6)
	{
		if (init_data(&cmn_data, argv) == FAILURE)
			return (FAILURE);
	}
	else
		return (put_error("too few or too many arguments\n"));
	i = -1;
	while (++i < cmn_data.total)
		pthread_create(&cmn_data.p_thread[i], NULL, &loop_philos,
			&cmn_data.p_data[i]);
	i = -1;
	while (++i < cmn_data.total)
		pthread_join(cmn_data.p_thread[i], NULL);
	return (0);
}
