/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:26:24 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/27 17:08:50 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static void	del_win(t_renderer *ren, t_list **list)
{
	t_win	*win;
	t_list	*freed;

	(void)ren;
	freed = *list;
	win = (t_win*)freed->content;
	mlx_destroy_window(ren->mlx, win->win);
	*list = freed->next;
	free(win);
	free(freed);
}

static void	close_wins(t_renderer *ren)
{
	t_list	*cur;
	t_win	*fof;

	while (ren->win && !((t_win*)ren->win->content)->id)
		del_win(ren, &ren->win);
	if (!(cur = ren->win))
		die("\x1b[33mAll windows Closed\x1b[0m");
	while (cur && cur->next)
	{
		fof = (t_win*)(cur->next)->content;
		if (!fof->id)
			del_win(ren, &(cur->next));
		cur = cur->next;
	}
}

void		update(t_renderer *ren)
{
	close_wins(ren);
}

int			close_win(t_win *win)
{
	win->id = 0;
	return (1);
}

int			clear_win(t_renderer *ren, int id)
{
	t_win	*win;

	win = find_win(ren, id);
	if (!win)
		return (0);
	mlx_clear_window(ren->mlx, win->win);
	return (1);
}
