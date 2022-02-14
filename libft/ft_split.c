/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 08:47:33 by mannouao          #+#    #+#             */
/*   Updated: 2022/01/31 17:13:03 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

static char	*word(char const *s, char c)
{
	int		len_word;
	char	*str;
	int		i;

	i = 0;
	len_word = ft_len_word(s, c);
	str = (char *)malloc(sizeof(char) * (len_word + 1));
	if (str == NULL)
		return (0);
	while (len_word > i)
	{
		str[i] = *s;
		s++;
		i++;
	}
	str[i] = 0;
	return (str);
}

static int	ft_c_words(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s && *s == c)
			s++;
		if (*s && *s != c)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

int	free_tab(char **strings, int i)
{
	if (strings[i] == NULL)
	{
		while (i >= 0)
		{
			free(strings[i]);
			i--;
		}
		free(strings);
		return (1);
	}
	else
		return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		c_words;
	int		i;

	i = 0;
	c_words = ft_c_words(s, c);
	strings = (char **)malloc(sizeof(char *) * (c_words + 1));
	if (!strings)
		return (0);
	while (*s)
	{
		if (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			strings[i] = word(s, c);
			if (free_tab(strings, i))
				return (0);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	strings[i] = 0;
	return (strings);
}
