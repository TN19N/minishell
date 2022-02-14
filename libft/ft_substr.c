/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:14:20 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/13 13:15:43 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;
	size_t	s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		len = 0;
	if (len > (s_len - start))
		len = (s_len - start);
	ptr = malloc(sizeof(*ptr) * (len + 1));
	if (!ptr)
		ft_error(NULL);
	while (len-- > 0)
	{
		ptr[i] = *(s + start + i);
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
