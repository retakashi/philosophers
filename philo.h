/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:08:12 by reira             #+#    #+#             */
/*   Updated: 2023/09/01 02:04:43 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <assert.h>
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE -1
# define TAKE 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define FALSE 0
# define TRUE 1
// # define ATOMIC_INCREMENT(val) atomic_fetch_add(&(val), 1)
typedef struct s_p_data
{
	int					i;
	pthread_t			monitor;
	struct s_cmn_data	*cmn_data;
	int					eat_cnt;
	atomic_long			last_eat;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		last_eat_lock;
}						t_p_data;

typedef struct s_cmn_data
{
	int					total;
	time_t				die_time;
	time_t				eat_time;
	time_t				sleep_time;
	time_t				start;
	int					until_eat;
	atomic_int			died;
	atomic_int		finished;
	atomic_int			fin_cnt;
	struct s_p_data		*p_data;
	pthread_mutex_t		*forks;
	pthread_t			*p_thread;
}						t_cmn_data;

// ft_atoi.c
int						ft_atoi(const char *str);
// init.c
int						init_data(t_cmn_data *data, char **argv);
// loop_philos.c
int						sleep_philo(t_p_data *p_data);
int						eat(t_p_data *p_data);
int						take_fork(t_p_data *p_data);
// monitor_status.c
int						is_died(t_p_data *p_data);
int						is_finished(t_p_data *p_data);
// utils.c
time_t					gettimeofday_ms(void);
void					ft_usleep(time_t arg_time);
// print.c
int						print_err(char *str);
void					print_status(t_p_data *p_data, int flg);
#endif
