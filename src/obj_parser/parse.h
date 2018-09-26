/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:42:00 by jwolf             #+#    #+#             */
/*   Updated: 2018/09/26 15:14:42 by jwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "rt.h"

void	face_from_str(char *str, int vert[3], int off[3]);
void	to_face(char *str, t_obj *obj, int *index, int off[3]);
void	assign_vertexpoints(t_vec vec, t_vec *ret);
void	assign_texturecoord(t_vec vec, t_tex *ret);
void	parse_info(t_list *lst, t_obj *obj, char *name, int off[3]);
void	parse_list(t_list *lst, t_env *env);
int		recurr_count(char *str, char delim);
void	assign_mem(t_obj *new);
int		malloc_obj_info(t_list **lst, t_obj *new);
char	*object_name_zone(t_list *lst);
t_obj	*the_good_search_name(t_scene *scene, char *name);

#endif
