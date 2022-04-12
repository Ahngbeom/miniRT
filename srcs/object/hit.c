/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:06:17 by bahn              #+#    #+#             */
/*   Updated: 2022/04/12 21:13:39 by bahn             ###   ########.fr       */
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
	{
		// hit_result = hit_plane(objects, ray, rec);
		hit_result = intersect_plane(objects->element, ray, rec, objects->color);
	}
	else if (objects->type == SPHERE)
		hit_result = hit_sphere(objects->element, ray, rec, objects->color);
	else if (objects->type == CYLINDER)
	{
		hit_result |= hit_cylinder_rectangle(objects->element, ray, rec, objects->color);
		hit_result |= hit_cylinder_circle(objects->element, ray, rec, objects->color);
	}
	// else if (objects->type == SQUARE)	
	// 	hit_result = hit_square(objects, ray, rec);
	return hit_result;
}
