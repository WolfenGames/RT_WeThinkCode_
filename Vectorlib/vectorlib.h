/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 17:34:57 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/16 16:46:22 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORLIB_H
# define VECTORLIB_H

# define FILLVEC(V, X, Y, Z, W) (V[0] = X, V[1] = Y, V[2] = Z, V[3] = W)
# define VEC3_IS(V) (V[0] || V[1] || V[2])
# define VEC4_IS(V) (V[0] || V[1] || V[2] || V[3])
# include <math.h>
# include "libft.h"

typedef double	t_matrix[4][4];
typedef double	t_vec[4];
typedef double	t_tex[3];
typedef	struct	s_ray
{
	t_vec	dir;
	t_vec	org;
	double	len;
	double	intersects[2];
}				t_ray;

double			dot(t_vec a, t_vec b);
double			length(t_vec v);
double			find_angle(t_vec a, t_vec b);
double			v_sum(t_vec	vec);
double			determinant(t_matrix a, double size);
double			fresnel(t_vec inc, t_vec norm, double index);

double			*refract(t_vec inc, t_vec norm, double index, t_vec ret);
double			*v_multi(t_vec a, double b, t_vec ret);
double			*v_sub(t_vec a, t_vec b, t_vec ret);
double			*v_add(t_vec a, t_vec b, t_vec ret);
double			*v_mult(t_vec a, t_vec b, t_vec ret);
double			*v_div(t_vec a, t_vec b, t_vec ret);
double			*v_cross(t_vec a, t_vec b, t_vec ret);
double			*transformvec(const t_matrix m, t_vec v, t_vec ret);
double			*transformw(const t_matrix m, t_vec v, t_vec ret);
double			*transform(const t_matrix m, t_vec v, t_vec ret);
double			*reflect(t_vec inc, t_vec norm, t_vec ret);

void			normalize(t_vec v);
void			vec_from_str(t_vec ret, char *str);
void			fill_m_rot_v(double a, t_vec axis, t_matrix m);
void			m3_mult(const t_matrix a, const t_matrix b, t_matrix ret);
void			m4_mult(const t_matrix a, const t_matrix b, t_matrix ret);
void			fill_m_rot_z(t_matrix m, double th);
void			fill_m_rot_x(t_matrix m, double th);
void			fill_m_rot_y(t_matrix m, double th);
void			vec_dup(t_vec src, t_vec dest);
void			v_rot_e(t_vec rot, t_vec vec, t_vec ret);
void			fill_m_transform(t_matrix m, t_vec trans);
void			m4_invert(t_matrix src, t_matrix ret);
void			cofactor(t_matrix a, double size);
void			transpose(t_matrix a, t_matrix fac, double size);
void			m4_dup(t_matrix src, t_matrix ret);

int				quad(t_vec val, double t[2]);

#endif
