/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 17:11:13 by ibotha            #+#    #+#             */
/*   Updated: 2018/08/28 18:56:34 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# define LIG ((t_lig*)cur->content)
# define OBJ ((t_obj*)cur->content)
# define CAM ((t_cam*)cur->content)

void	get_col(t_ray *ray, t_env *env, t_col c);

int		sphere_intersect(t_ray *ray, t_obj *obj);
void	sphere_getnorm(t_vec norm, t_vec point, t_obj *obj);

#endif