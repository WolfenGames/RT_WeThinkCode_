/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 13:17:54 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/25 13:38:11 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_win	*find_win(t_renderer *ren, int id)
{
	t_list	*cur;
	t_win	*wow;
	
	cur = ren->win;
	while (cur)
	{
		wow = (t_win*)cur->content;
		if (id == wow->id)
		{
			return (wow);
		}
		cur = cur->next;
	}
	return(NULL);
}

t_img	*find_img(t_renderer *ren, int id)
{
	t_list	*cur;
	t_img	*ioi;

	cur = ren->img;
	while (cur)
	{
		ioi = (t_img*)cur->content;
		if (id == ioi->id)
		{
			return (ioi);
		}
		cur = cur->next;
	}
	return (NULL);
}

t_win	*select_win(t_renderer *ren, int id)
{
	ren->c_win = find_win(ren, id);
	return (ren->c_win);
}

t_img	*select_img(t_renderer *ren, int id)
{
	ren->c_img = find_img(ren, id);
	return (ren->c_img);
}
