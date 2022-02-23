/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:48:42 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/23 11:08:09 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_len_num(int a)
{
	int				i;
	unsigned int	x;

	i = 0;
	if (a < 0)
	{
		i++;
		x = a * -1;
	}
	else
		x = a;
	while (x >= 10)
	{
		i++;
		x /= 10;
	}
	i++;
	return (i);
}

static void	ft_putnum(char *str, unsigned int x, int len_num)
{
	str[len_num] = 0;
	len_num--;
	if (x == 0)
		str[len_num] = '0';
	while (len_num >= 0 && x != 0)
	{
		*(str + len_num) = ((x % 10) + '0');
		x /= 10;
		len_num--;
	}
}

char	*ft_itoa(int a)
{
	unsigned int	x;
	int				len_num;
	char			*str;

	len_num = ft_len_num(a);
	str = malloc(sizeof(char) * (len_num + 1));
	if (str == NULL)
		return (0);
	if (a < 0)
	{
		str[0] = '-';
		x = -a;
	}
	else
		x = a;
	ft_putnum(str, x, len_num);
	return (str);
}
