/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:22:49 by mannouao          #+#    #+#             */
/*   Updated: 2021/11/13 22:01:23 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	size;

	size = 0;
	while (*s)
	{
		size++;
		s++;
	}
	if (*s == '\0' && c == 0)
		return ((char *)s);
	s--;
	while (size > 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
		size--;
	}
	return (0);
}
