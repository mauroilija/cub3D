/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:17:52 by abita             #+#    #+#             */
/*   Updated: 2026/04/24 21:15:19 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

static void	var(unsigned char **d, unsigned char **s,
	void *dest, const void *src)
{
	*d = (unsigned char *) dest;
	*s = (unsigned char *) src;
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	var(&d, &s, dest, src);
	if (d == s || n == 0)
		return (dest);
	if (d < s)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (d > s)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (dest);
}
/*
int	main()
{
	char buffer[] = "hello, world!";

	ft_memmove(buffer + 7, buffer, 6);
	printf("After: %s\n", buffer);
	return (0);
}*/
