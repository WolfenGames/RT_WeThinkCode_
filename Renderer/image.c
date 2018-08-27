/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 09:11:31 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/27 17:09:47 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

int		add_img(t_renderer *ren, int w, int h)
{
	t_img	new;

	ft_bzero(&new, sizeof(t_img));
	if (!(new.img = mlx_new_image(ren->mlx, w, h)))
		return (0);
	new.dat = (unsigned char*)mlx_get_data_addr(new.img, &new.bpp,
		&new.ll, &new.end);
	new.bpp /= 8;
	new.w = w;
	new.h = h;
	new.id = 1;
	while (find_img(ren, new.id))
		new.id++;
	ft_lstadd(&ren->img, ft_lstnew(&new, sizeof(t_img)));
	ren->c_img = (t_img*)ren->img->content;
	return (new.id);
}

int		add_img_xpm(t_renderer *ren, char *filename, int x, int y)
{
	t_img	new;

	ft_bzero(&new, sizeof(t_img));
	if (!(new.img = mlx_xpm_file_to_image(ren->mlx, filename, &new.w, &new.h)))
		return (0);
	new.dat = (unsigned char*)mlx_get_data_addr(new.img, &new.bpp,
		&new.ll, &new.end);
	new.bpp /= 8;
	new.x = x;
	new.y = y;
	new.id = 1;
	while (find_img(ren, new.id))
		new.id++;
	ft_lstadd(&ren->img, ft_lstnew(&new, sizeof(t_img)));
	ren->c_img = (t_img*)ren->img->content;
	return (new.id);
}

int		present_img(t_renderer *ren, int wid, int iid)
{
	t_win	*win;
	t_img	*img;

	win = find_win(ren, wid);
	if (!win)
		return (0);
	img = find_img(ren, iid);
	if (!img)
		return (0);
	mlx_put_image_to_window(ren->mlx, win->win, img->img, img->x, img->y);
	return (1);
}

int		set_img_pos(t_renderer *ren, int id, int x, int y)
{
	t_img	*img;

	img = find_img(ren, id);
	if (!img)
		return (0);
	img->x = x;
	img->y = y;
	return (1);
}

int		move_img(t_renderer *ren, int id, int x, int y)
{
	t_img	*img;

	img = find_img(ren, id);
	if (!img)
		return (0);
	img->x += x;
	img->y += y;
	return (1);
}
