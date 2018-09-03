/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 17:11:13 by ibotha            #+#    #+#             */
/*   Updated: 2018/09/03 13:07:01 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# define LIG ((t_lig*)cur->content)
# define OBJ ((t_obj*)cur->content)
# define CAM ((t_cam*)cur->content)

void	get_col(t_ray *ray, t_env *env, t_col c);
void	get_surface_col(t_obj *obj, t_col c, t_vec point, t_env *env);

void	sphere_surface_col(t_obj *obj, t_col c, t_vec point, t_env *env);
int		sphere_intersect(t_ray *ray, t_obj *obj);
void	sphere_getnorm(t_vec norm, t_vec point, t_obj *obj);

void	cone_surface_col(t_obj *ob, t_col c, t_vec point, t_env *env);
int		cone_intersect(t_ray *ray, t_obj *obj);
void	cone_getnorm(t_vec norm, t_vec point, t_obj *obj);

#endif