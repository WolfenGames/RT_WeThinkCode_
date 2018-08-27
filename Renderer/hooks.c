/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 16:36:45 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/17 15:30:54 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

int		key_add(int keycode, t_win *win)
{
	win->keys[keycode] = 1;
	return (keycode);
}

int		key_remove(int keycode, t_renderer *ren)
{
	t_list *tmp;

	tmp = ren->win;
	while (tmp)
	{
		((t_win*)tmp->content)->keys[keycode] = 0;
		tmp = tmp->next;
	}
	return (keycode);
}

int	mouse_up(int x, int y, t_win *win)
{
	win->mouse.x = x;
	win->mouse.y = y;
	return (0);
}

int	mouse_add(int button, int x, int y, t_win *win)
{
	if (button == 1)
		win->mouse.left = 1;
	if (button == 2)
		win->mouse.right = 1;
	return (x + y);
}

int	mouse_remove(int button, int x, int y, t_win *win)
{
	if (button == 1)
		win->mouse.left = 0;
	if (button == 2)
		win->mouse.right = 0;
	return (x + y);
}
