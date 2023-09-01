/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:08:12 by reira             #+#    #+#             */
/*   Updated: 2023/09/02 00:23:10 by reira            ###   ########.fr       */
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
	struct s_cmn_data	*cmn_data;
	int					eat_cnt;
	time_t				last_eat;
	int					until_eat;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
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
	bool				finished;
	int					fin_cnt;
	struct s_p_data		*p_data;
	pthread_mutex_t		*forks;
	pthread_mutex_t		cmn_lock;
	pthread_t			*p_thread;
	pthread_t			*monitor;
}						t_cmn_data;

// ft_atoi.c
int						ft_atoi(const char *str);
// init.c
int						init_data(t_cmn_data *data);
// is_valid_argv.c
int						is_valid_argv(t_cmn_data *data, int argc, char **argv);
// loop_philos.c
void					sleep_philo(t_p_data *p_data);
void					eat(t_p_data *p_data);
int						take_fork(t_p_data *p_data);
void					*loop_philos(void *arg_data);
// monitor_status.c
int						is_died(t_p_data *p_data);
int						is_finished(t_p_data *p_data);
void					*monitor_status(void *arg_data);
// utils.c
time_t					gettimeofday_ms(void);
void					ft_usleep(time_t arg_time);
// print.c
int						print_err(char *str);
void					print_status(t_p_data *p_data, int flg);
#endif
