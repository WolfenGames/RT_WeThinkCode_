/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 16:23:29 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/05 16:43:50 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static void	delete_img(t_renderer *ren, t_list *del)
{
	mlx_destroy_image(ren->mlx, ((t_img*)del->content)->img);
	free(del->content);
	free(del);
}

void	del_img(t_renderer *ren, int iid)
{
	t_list	*del;
	t_list	*cur;

	if (((t_img*)ren->img->content)->id == iid)
	{
		del = ren->img;
		ren->img = ren->img->next;
	}
	else
	{
		cur = ren->img;
		while (cur && cur->next)
		{
			if (((t_img*)cur->next->content)->id == iid)
			{
				del = cur->next;
				cur->next = cur->next->next;
			}
			cur = cur->next;
		}
	}
	delete_img(ren, del);
}