/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:01:05 by reira             #+#    #+#             */
/*   Updated: 2023/08/28 23:38:16 by reira            ###   ########.fr       */
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

