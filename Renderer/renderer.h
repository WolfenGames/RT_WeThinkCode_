/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:44:46 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/27 17:08:17 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include <mlx.h>
# include "libft.h"
# include <stdio.h>

# define ABS(C) (C < 0 ? -C : C)
# define DR(N) (change < 0 ? (-N) : N)
# define ALP(C) C[3]
# define RED(C) C[0]
# define GRN(C) C[1]
# define BLU(C) C[2]
# define FILLCOL(C, R, G, B, A) (C[0] = R, C[1] = G, C[2] = B, C[3] = A)

typedef int		t_xy[2];
typedef float	t_col[4];

typedef struct	s_mouse
{
	char			left;
	char			right;
	int				x;
	int				y;
}				t_mouse;

typedef struct	s_img
{
	int				id;
	void			*img;
	int				x;
	int				y;
	unsigned char	*dat;
	int				bpp;
	int				ll;
	int				end;
	int				h;
	int				w;
}				t_img;

typedef struct	s_win
{
	void			*win;
	int				w;
	int				h;
	int				id;
	char			keys[512];
	t_mouse			mouse;
}				t_win;

typedef struct	s_renderer
{
	void			*mlx;
	t_list			*win;
	t_win			*c_win;
	t_list			*img;
	t_img			*c_img;
}				t_renderer;

typedef	enum	s_key
{
	init = -1,
	esc = 53,
	up = 126,
	down = 125,
	left = 123,
	right = 124,
	plus = 69,
	minus = 78,
	home = 115,
	end = 119,
	np_4 = 86,
	np_6 = 88,
	np_8 = 91,
	np_2 = 84,
	shift = 257,
	key_r = 15,
	key_g = 5,
	key_b = 11,
	key_a = 0,
	ctrl = 256,
	key_q = 12,
	key_w = 13,
	key_s = 1,
	key_e = 14,
	space = 49
}				t_key;

int		key_add(int keycode, t_win *win);
int		key_remove(int keycode, t_renderer *ren);
int		mouse_up(int x, int y, t_win *win);
int		mouse_add(int button, int x, int y, t_win *win);
int		mouse_remove(int button, int x, int y, t_win *win);
int		close_win(t_win *win);

void	renderer_set(t_renderer *ren);
int		add_win(t_renderer *ren, const char *name, int x, int y);
int		add_img(t_renderer *ren, int w, int h);
int		add_img_xpm(t_renderer *ren, char *filename, int x, int y);
void	update(t_renderer *ren);

void	draw_line(t_xy a, t_xy b, t_col c, t_img *img);
void	put_pixel(int x, int y, t_col c, t_img *img);
void	draw_box(t_xy start, t_xy end, t_col c, t_img *img);

t_win	*select_win(t_renderer *ren, int id);
t_img	*select_img(t_renderer *ren, int id);
t_win	*find_win(t_renderer *ren, int id);
t_img	*find_img(t_renderer *ren, int id);

int		present_img(t_renderer *ren, int wid, int iid);
int		set_img_pos(t_renderer *ren, int id, int x, int y);
int		move_img(t_renderer *ren, int id, int x, int y);
int		clear_win(t_renderer *ren, int id);

float	*add_col(t_col a, t_col b, t_col ret);
float	*sc_col(t_col c, double s, t_col);
float	*get_img_col(int x, int y, t_img *img, t_col ret);

#endif
