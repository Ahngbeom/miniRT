/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:46:31 by bahn              #+#    #+#             */
/*   Updated: 2022/03/30 14:01:42 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*cylinder_init(t_point3 orig, t_vec3 normal)
{
	t_cylinder	*cy;

	cy = ft_calloc(sizeof(t_plane), 1);
	if (cy == NULL)
		return (NULL);
	cy->coord = orig;
	cy->normal = normal;
	cy->diameter = 14.2;
	cy->height = 21.42;
	return (cy);
}

t_bool		hit_cylinder(t_object *world, t_ray *r, t_hit_record *rec)
{
	t_cylinder	*cy;
	double		denom;
	double		t;
	
	cy = world->element;
	denom = vdot(cy->normal, r->dir);
	if (denom > 1e-6)
		return (FALSE);
	// printf("denom : %f\n", denom);
	t = vdot(vsub(cy->coord, r->orig), cy->normal) / denom;
	// printf("t : %f\n", t);
	if (t > rec->tmin && t < rec->tmax)
	{
		rec->t = t;
		rec->p = ray_at(r, t);
		
		// if (vdot(r->dir, cy->normal) > 0)
			// cy->normal = vmul_t(-1, cy->normal);
		// rec->normal = cy->normal;
		
		set_face_normal(r, rec);

		return (TRUE);
	}
	return (FALSE);
}