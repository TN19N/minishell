/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:19:10 by mannouao          #+#    #+#             */
/*   Updated: 2021/11/06 08:05:05 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *countent)
{
	t_list	*root;

	root = malloc(sizeof(t_list));
	if (root == NULL)
		return (NULL);
	root->content = countent;
	root->next = NULL;
	return (root);
}
