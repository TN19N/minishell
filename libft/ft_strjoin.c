/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:38:25 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/23 11:08:53 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	fill_str(char *ptr, int *len_1_2, const char *s1, const char *s2)
{
	while (len_1_2[0]-- > 0)
	{
		*ptr = *s1;
		s1++;
		ptr++;
	}
	while (len_1_2[1]-- > 0)
	{
		*ptr = *s2;
		s2++;
		ptr++;
	}
	*ptr = 0;
}

char	*ft_strjoin(const char *s1, char const *s2)
{
	int		len_1_2[2];
	int		len;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_1_2[0] = ft_strlen(s1);
	len_1_2[1] = ft_strlen(s2);
	len = len_1_2[0] + len_1_2[1];
	ptr = malloc((len + 1) * sizeof(*ptr));
	if (ptr == NULL)
		ft_error(NULL);
	fill_str(ptr, len_1_2, s1, s2);
	return (ptr);
}
