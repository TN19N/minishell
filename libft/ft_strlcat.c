/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:46:07 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/23 11:08:56 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	len;
	size_t	i;

	lendst = 0;
	lensrc = 0;
	i = 0;
	if (!dst && size == 0)
		return (ft_strlen(src));
	lendst = ft_strlen(dst);
	len = lendst;
	lensrc = ft_strlen(src);
	if (lendst >= size)
		return (lensrc + size);
	while (src[i] && len + 1 < size)
	{
		dst[len] = src[i];
		i++;
		len++;
	}
	dst[len] = 0;
	return (lendst + lensrc);
}
