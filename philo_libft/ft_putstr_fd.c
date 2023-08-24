/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 22:06:24 by rtakashi          #+#    #+#             */
/*   Updated: 2023/08/24 22:34:55 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

// int	main(void)
// {
// 	char s[]="a";
// 	ft_putstr_fd(s,-1);
// 	return (0);
// }
