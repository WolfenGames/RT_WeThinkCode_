/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 13:33:54 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/11 14:30:55 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

double	find_angle(t_vec a, t_vec b)
{
	double	alen2;
	double	blen2;
	double	clen2;

	clen2 = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	alen2 = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	blen2 = b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
	return (acos(clen2 / sqrt(alen2 * blen2)));
}

void	fill_m_rot_z(t_matrix m, double th)
{
	t_matrix a;

	ft_bzero(a, sizeof(a));
	m4_dup(a, m);
	m[0][0] = cos(th);
	m[1][0] = sin(th);
	m[0][1] = -m[1][0];
	m[1][1] = m[0][0];
	m[2][2] = 1;
	m[3][3] = 1;
}

void	fill_m_rot_x(t_matrix m, double th)
{
	t_matrix a;

	ft_bzero(a, sizeof(a));
	m4_dup(a, m);
	m[1][1] = cos(th);
	m[1][2] = sin(th);
	m[2][1] = -m[1][2];
	m[2][2] = m[1][1];
	m[0][0] = 1;
	m[3][3] = 1;
}

void	fill_m_rot_y(t_matrix m, double th)
{
	t_matrix a;

	ft_bzero(a, sizeof(a));
	m4_dup(a, m);
	m[0][0] = cos(th);
	m[0][2] = sin(th);
	m[2][0] = -m[0][2];
	m[2][2] = m[0][0];
	m[1][1] = 1;
	m[3][3] = 1;
}

double	*reflect(t_vec inc, t_vec norm, t_vec ret)
{
	t_vec	temp;
	double	d;

	d = dot(inc, norm);
	if (d > 0)
		return (NULL);
	v_multi(norm, d * 2, temp);
	v_sub(inc, temp, ret);
	return (ret);
}
