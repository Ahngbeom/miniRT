/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:06:17 by bahn              #+#    #+#             */
/*   Updated: 2022/03/30 19:30:16 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	tmp_rec;

	tmp_rec = *rec;
	hit_anything = FALSE;
	while (world != NULL)
	{
		if (hit_object(world, ray, &tmp_rec) > 0)
		{
			hit_anything = TRUE;
			*rec = tmp_rec;
			tmp_rec.tmax = tmp_rec.t;
		}
		world = world->next;
	}
	return (hit_anything);
}

t_bool	hit_object(t_object *world, t_ray *ray, t_hit_record *rec)
{
	int	hit_result;

	hit_result = FALSE;
	if (world->type == SPHERE)
		hit_result = hit_sphere(world, ray, rec);
	else if (world->type == PLANE)
		// hit_result = hit_plane(world, ray, rec);
		hit_result = intersect_plane(plane_init(point_init(0, -5, -5), vector_init(0, 0, 1)), ray, rec);
	else if (world->type == CYLINDER)
		hit_result = hit_cylinder(world, ray, rec);
	else if (world->type == SQUARE)	
		hit_result = hit_square(world, ray, rec);
	return hit_result;
}
