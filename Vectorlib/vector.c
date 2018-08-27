/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 14:51:33 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/12 13:28:00 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

double	dot(t_vec a, t_vec b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

double	*v_cross(t_vec a, t_vec b, t_vec ret)
{
	t_vec temp;

	temp[0] = a[1] * b[2] - a[2] * b[1];
	temp[1] = a[2] * b[0] - a[0] * b[2];
	temp[2] = a[0] * b[1] - a[1] * b[0];
	ret[0] = temp[0];
	ret[1] = temp[1];
	ret[2] = temp[2];
	return (ret);
}

double	length(t_vec v)
{
	return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

void	normalize(t_vec v)
{
	double l;

	l = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	if (l > 0)
	{
		l = 1 / sqrt(l);
		v[0] *= l;
		v[1] *= l;
		v[2] *= l;
	}
}

void	fill_m_rot_v(double a, t_vec u, t_matrix m)
{
	double	cosa;
	double	sina;

	sina = sin(a);
	cosa = cos(a);
	normalize(u);
	m[0][0] = cosa + (u[0] * u[0]) * (1 - cosa);
	m[1][0] = (u[0] * u[1]) * (1 - cosa) - (u[2] * sina);
	m[2][0] = (u[2] * u[0]) * (1 - cosa) + (u[1] * sina);
	m[0][1] = (u[0] * u[1]) * (1 - cosa) + (u[2] * sina);
	m[1][1] = cosa + (u[1] * u[1]) * (1 - cosa);
	m[2][1] = (u[1] * u[2]) * (1 - cosa) - (u[0] * sina);
	m[0][2] = (u[2] * u[0]) * (1 - cosa) - (u[1] * sina);
	m[1][2] = (u[2] * u[1]) * (1 - cosa) + (u[0] * sina);
	m[2][2] = cosa + (u[2] * u[2]) * (1 - cosa);
	m[3][3] = 1;
}
