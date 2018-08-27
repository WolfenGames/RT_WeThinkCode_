/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 13:57:58 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/12 13:16:57 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

void		m4_dup(t_matrix src, t_matrix ret)
{
	int i;
	int j;

	j = -1;
	while (++j < 4)
	{
		i = -1;
		while (++i < 4)
			ret[i][j] = src[i][j];
	}
}

static void	det_work(t_matrix a, t_matrix b, double size, int c)
{
	int	i[4];

	i[2] = 0;
	i[3] = 0;
	i[0] = -1;
	while (++i[0] < size)
	{
		i[1] = -1;
		while (++i[1] < size)
		{
			b[i[0]][i[1]] = 0;
			if (i[0] != 0 && i[1] != c)
			{
				b[i[2]][i[3]] = a[i[0]][i[1]];
				if (i[3] < (size - 2))
					i[3]++;
				else
				{
					i[3] = 0;
					i[2]++;
				}
			}
		}
	}
}

double		determinant(t_matrix a, double size)
{
	double		s;
	double		ret;
	t_matrix	b;
	int			c;

	s = 1;
	ret = 0;
	if (size == 1)
		return (a[0][0]);
	c = -1;
	while (++c < size)
	{
		det_work(a, b, size, c);
		ret = ret + s * (a[0][c] * determinant(b, size - 1));
		s = -1 * s;
	}
	return (ret);
}

void		m4_invert(t_matrix src, t_matrix ret)
{
	t_matrix	a;

	m4_dup(src, a);
	cofactor(a, 4);
	m4_dup(a, ret);
}
