/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:28:41 by rtakashi          #+#    #+#             */
/*   Updated: 2023/08/24 22:35:03 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// #include <string.h>
// #include<stdio.h>

// int	main(void)
// {
// 	char dst1[]="42tokyo";
// 	char dst2[]="42tokyo";
// 	printf("%zu\n", ft_strlen(dst1));
// 	printf("%zu\n", strlen(dst2));
// 	printf("%zu\n", ft_strlen(NULL));
// 	printf("%zu\n", strlen(NULL));
// 	return (0);
// }
