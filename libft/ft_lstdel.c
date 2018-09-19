/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 11:42:33 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/19 15:52:30 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*n_lst;
	t_list	*temp;

	n_lst = *alst;
	while (n_lst)
	{
		if (*del)
			(*del)(n_lst->content, n_lst->content_size);
		temp = n_lst->next;
		free(n_lst);
		n_lst = temp;
	}
	*alst = NULL;
}
