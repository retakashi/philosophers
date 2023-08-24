/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 21:01:24 by rtakashi          #+#    #+#             */
/*   Updated: 2023/08/24 22:34:41 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	int fd = open("temp.txt", O_WRONLY);
// 	int fd2 = open("output.txt", O_WRONLY);
// 	ft_putchar_fd('a', 2);
// ft_putchar_fd('c', fd);
// ft_putchar_fd('o', 1);
// ft_putchar_fd('e', 2);
// printf("stdout %d", STDOUT_FILENO);
// printf("stdout %d", STDERR_FILENO);
// printf("stdin  %d", STDIN_FILENO);
// printf("fd : %d, fd2 :%d", fd, fd2);
// 	return (0);
// }
