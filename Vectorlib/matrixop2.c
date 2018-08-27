/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixop2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 13:03:19 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/12 13:23:47 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectorlib.h"

static void	cal_co(t_matrix a, t_matrix b, double size, int dim[2])
{
	int	i[4];

	i[3] = 0;
	i[2] = 0;
	i[0] = -1;
	while (++i[0] < size)
	{
		i[1] = -1;
		while (++i[1] < size)
		{
			if (i[0] != dim[0] && i[1] != dim[1])
			{
				b[i[3]][i[2]] = a[i[0]][i[1]];
				if (i[2] < (size - 2))
					i[2]++;
				else
				{
					i[2] = 0;
					i[3]++;
				}
			}
		}
	}
}

void		cofactor(t_matrix a, double size)
{
	t_matrix	b;
	t_matrix	fac;
	int			dim[2];

	dim[0] = -1;
	while (++dim[0] < size)
	{
		dim[1] = -1;
		while (++dim[1] < size)
		{
			cal_co(a, b, size, dim);
			fac[dim[0]][dim[1]] = pow(-1, dim[0] + dim[1])
				* determinant(b, size - 1);
		}
	}
	transpose(a, fac, size);
}

void		transpose(t_matrix a, t_matrix fac, double size)
{
	int		i;
	int		j;
	double	d;

	i = -1;
	d = determinant(a, size);
	if (d != 0)
		while (++i < size)
		{
			j = -1;
			while (++j < size)
			{
				a[i][j] = fac[j][i] / d;
			}
		}
}
