/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 13:30:23 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/25 18:22:15 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rt.h"
#include "parse.h"

/*
** Handles the normal texture loading
*/

static void	try_load_n_xpm(char *small, char *filename, t_env *env, t_obj *o)
{
	int		fd;

	if (ft_strstr(small, ".xpm") &&
		ft_strnequ(ft_strrchr(small, '.'), ".xpm", 4))
	{
		if ((fd = open(filename, O_RDONLY)) < 0)
			return ;
		close(fd);
		o->norm = add_img_xpm(REN, filename, 0, 0);
	}
}

static void	try_load_n_png(char *small, char *filename, t_env *env, t_obj *o)
{
	int		fd;

	if (ft_strstr(small, ".png") &&
		ft_strnequ(ft_strrchr(small, '.'), ".png", 4))
	{
		if ((fd = open(filename, O_RDONLY)) < 0)
			return ;
		close(fd);
		load_png(o, ft_strdup(filename), env, 1);
	}
}

void	assign_norm(t_obj *obj, t_obj *ref)
{
	if (ref)
		obj->norm = ref->norm;
}

void		set_n_tex(t_obj *o, char *filename, t_env *env)
{
	char	*small;

	small = ft_strmap(filename, char_lower);
	if (ft_strnequ(filename, "->", 2))
	{
		assign_norm(o, the_good_search_name(&env->scene, filename + 2));
		free(small);
		free(filename);
		return ;
	}
	try_load_n_png(small, filename, env, o);
	try_load_n_xpm(small, filename, env, o);
	free(small);
	free(filename);
}
