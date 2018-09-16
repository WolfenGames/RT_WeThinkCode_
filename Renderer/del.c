/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 16:23:29 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/16 15:20:35 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static void	delete_img(t_renderer *ren, t_list *del)
{
	if (!del)
		return ;
	mlx_destroy_image(ren->mlx, ((t_img*)del->content)->img);
	free(del->content);
	free(del);
}

void		del_img(t_renderer *ren, int iid)
{
	t_list	*del;
	t_list	*cur;

	if (!ren->img)
		return ;
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

static void	del_imgs(t_renderer *ren)
{
	t_img	*img;

	while (ren->img)
	{
		img = (t_img*)ren->img->content;
		del_img(ren, img->id);
	}
}

static void	del_wins(t_renderer *ren)
{
	t_win	*win;
	t_list	*temp;

	while (ren->win)
	{
		win = (t_win*)ren->win->content;
		mlx_destroy_window(ren->mlx, win->win);
		free(ren->win->content);
		temp = ren->win;
		ren->win = ren->win->next;
		free(temp);
	}
}

void		del_renderer(t_renderer *ren)
{
	del_imgs(ren);
	del_wins(ren);
}
