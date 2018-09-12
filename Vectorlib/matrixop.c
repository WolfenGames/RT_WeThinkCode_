/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 09:55:02 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/12 10:07:44 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

void	m4_mult(const t_matrix a, const t_matrix b, t_matrix ret)
{
	int		i;
	int		j;
	double	temp[4][4];

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			temp[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j]
				+ a[i][2] * b[2][j] + a[i][3] * b[3][j];
	}
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			ret[i][j] = temp[i][j];
	}
}

void	m3_mult(const t_matrix a, const t_matrix b, t_matrix ret)
{
	int		i;
	int		j;
	double	temp[3][3];

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			temp[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j]
				+ a[i][2] * b[2][j];
	}
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			ret[i][j] = temp[i][j];
	}
}

double	*transform(const t_matrix m, t_vec v, t_vec ret)
{
	t_vec temp;

	temp[0] = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + m[3][0];
	temp[1] = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + m[3][1];
	temp[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + m[3][2];
	ret[0] = temp[0];
	ret[1] = temp[1];
	ret[2] = temp[2];
	return (ret);
}

double	*transformw(const t_matrix m, t_vec v, t_vec ret)
{
	t_vec	temp;
	double	w;

	temp[0] = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + m[3][0];
	temp[1] = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + m[3][1];
	temp[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + m[3][2];
	w = v[0] * m[0][3] + v[1] * m[1][3] + v[2] * m[2][3] + m[3][3];
	if (w != 1 && w != 0)
	{
		temp[0] /= w;
		temp[1] /= w;
		temp[2] /= w;
	}
	ret[0] = temp[0];
	ret[1] = temp[1];
	ret[2] = temp[2];
	return (ret);
}

double	*transformvec(const t_matrix m, t_vec v, t_vec ret)
{
	t_vec temp;

	temp[0] = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0];
	temp[1] = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1];
	temp[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2];
	ret[0] = temp[0];
	ret[1] = temp[1];
	ret[2] = temp[2];
	return (ret);
}
