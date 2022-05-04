/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:06:17 by bahn              #+#    #+#             */
/*   Updated: 2022/05/04 18:35:43 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	hit(t_object *objects, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	tmp_rec;

	tmp_rec = *rec;
	hit_anything = FALSE;
	while (objects != NULL)
	{
		if (hit_object(objects, ray, &tmp_rec) == TRUE)
		{
			hit_anything = TRUE;
			tmp_rec.albedo = vmul_t(1.0 / 255.0, objects->color);
			*rec = tmp_rec;
			tmp_rec.tmax = tmp_rec.t;
		}
		objects = objects->next;
	}
	return (hit_anything);
}

t_bool	hit_object(t_object *objects, t_ray *ray, t_hit_record *rec)
{
	int	hit_result;

	hit_result = FALSE;
	if (objects->type == PLANE)
		hit_result = hit_plane(objects->element, ray, rec);
	else if (objects->type == SPHERE)
		hit_result = hit_sphere(objects->element, ray, rec);
	else if (objects->type == CYLINDER)
		hit_result = hit_cylinder(objects->element, ray, rec);
	return (hit_result);
}
