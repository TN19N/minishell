/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:06:30 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/23 11:09:17 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	len_back(const char *s1, const char *set)
{
	int	i;
	int	def;
	int	h;
	int	len;

	def = 0;
	len = ft_strlen(s1);
	while (len > 0)
	{
		i = 0;
		h = 0;
		while (set[i])
		{
			if (set[i] == s1[len - 1])
				h = 1;
			i++;
		}
		if (h == 1)
			def++;
		else
			break ;
		len--;
	}
	return (def);
}

static int	len_front(const char *s1, const char *set)
{
	int	i;
	int	def;
	int	h;

	def = 0;
	while (*s1)
	{
		i = 0;
		h = 0;
		while (set[i])
		{
			if (set[i] == *s1)
				h = 1;
			i++;
		}
		if (h == 1)
			def++;
		else
			break ;
		s1++;
	}
	return (def);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	int		len_f;
	int		len_b;
	int		len_t;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len_f = len_front(s1, set);
	len_b = len_back(s1, set);
	len_t = ft_strlen(s1) - (len_f + len_b);
	str = ft_substr(s1, len_f, len_t);
	return (str);
}
