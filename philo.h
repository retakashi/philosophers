/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:08:12 by reira             #+#    #+#             */
/*   Updated: 2023/08/23 20:43:02 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <assert.h>
# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE -1

typedef struct s_pdata
{
	int				pnum;
	int				die;
	int				eat;
	int				sleep;
	int				elimit;
	pthread_mutex_t	rforks;
	pthread_mutex_t	lforks;
	pthread_mutex_t	elock;
}					t_pdata;

#endif
