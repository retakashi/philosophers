/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:08:12 by reira             #+#    #+#             */
/*   Updated: 2023/08/30 22:42:47 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <assert.h>
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE -1

typedef struct s_p_data
{
	int					i;
	pthread_t			monitor;
	struct s_cmn_data	*cmn_data;
	int					eat_cnt;
	time_t				last_eat;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		p_lock;
}						t_p_data;

typedef struct s_cmn_data
{
	int					total;
	time_t				die_time;
	time_t				eat_time;
	time_t				sleep_time;
	time_t				start;
	int					until_eat;
	bool				died;
	int					fin_cnt;
	struct s_p_data		*p_data;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_t			*p_thread;
}						t_cmn_data;

// error.c
int						put_error(char *str);
// ft_atoi.c
int						ft_atoi(const char *str);
// init.c
int						init_data(t_cmn_data *data, char **argv);
// utils.c
time_t					get_millisecond(void);
time_t					ft_usleep(time_t arg_time);
#endif
