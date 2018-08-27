/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:18:19 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/12 13:28:37 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

void	vec_from_str(t_vec ret, char *str)
{
	while (*str == ' ' || *str == '\t')
		++str;
	ret[0] = ft_atod(str);
	while (!(*str == ' ' || *str == '\t'))
		++str;
	while (*str == ' ' || *str == '\t')
		++str;
	ret[1] = ft_atod(str);
	while (!(*str == ' ' || *str == '\t'))
		++str;
	while (*str == ' ' || *str == '\t')
		++str;
	ret[2] = ft_atod(str);
}

double	v_sum(t_vec vec)
{
	return (vec[0] + vec[1] + vec[2]);
}

void	v_rot_e(t_vec rot, t_vec vec, t_vec ret)
{
	t_matrix	temp;
	t_matrix	temp2;
	t_vec		tempvec;

	ft_bzero(&temp, sizeof(temp));
	ft_bzero(&temp2, sizeof(t_matrix));
	fill_m_rot_x(temp2, (rot[1] * M_PI) / 180.f);
	fill_m_rot_y(temp, (rot[0] * M_PI) / 180.f);
	m4_mult(temp2, temp, temp2);
	transformvec(temp2, vec, tempvec);
	fill_m_rot_v((rot[2] * M_PI) / 180.0f, tempvec, temp);
	m4_mult(temp2, temp, temp2);
	transformvec(temp2, vec, ret);
}

void	fill_m_transform(t_matrix m, t_vec trans)
{
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[1][1] = 1;
	m[1][0] = 0;
	m[1][2] = 0;
	m[2][2] = 1;
	m[2][1] = 0;
	m[2][0] = 0;
	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 0;
	m[3][3] = 1;
	m[3][0] = trans[0];
	m[3][1] = trans[1];
	m[3][2] = trans[2];
}
