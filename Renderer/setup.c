/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 14:45:53 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/16 16:20:20 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	renderer_set(t_renderer *ren)
{
	ft_bzero(ren, sizeof(t_renderer));
	if (!(ren->mlx = mlx_init()))
		die("\x1b[31mMLX Init Fail\x1b[0m");
}

t_win	*add_win(t_renderer *ren, const char *name, int x, int y)
{
	t_win	new;

	ft_bzero(&new, sizeof(t_win));
	if (!(new.win = mlx_new_window(ren->mlx, x, y, (char*)name)))
		return (0);
	new.id = 1;
	while (find_win(ren, new.id))
		new.id++;
	new.w = x;
	new.h = y;
	ft_lstadd(&ren->win, ft_lstnew(&new, sizeof(t_win)));
	ren->c_win = (t_win*)ren->win->content;
	mlx_hook(new.win, 2, 0L, key_add, ren->c_win);
	mlx_hook(new.win, 3, 0L, key_remove, ren);
	mlx_hook(new.win, 4, 0L, mouse_add, ren->c_win);
	mlx_hook(new.win, 5, 0L, mouse_remove, ren->c_win);
	mlx_hook(new.win, 6, 0L, mouse_up, ren->c_win);
	mlx_hook(new.win, 17, 0L, close_win, ren->c_win);
	return (ren->c_win);
}
