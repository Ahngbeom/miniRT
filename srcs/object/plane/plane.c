/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:17:09 by bahn              #+#    #+#             */
/*   Updated: 2022/03/30 19:27:59 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane		*plane_init(t_point3 orig, t_vec3 normal)
{
	t_plane	*plane;

	plane = ft_calloc(sizeof(t_plane), 1);
	if (plane == NULL)
		return (NULL);
	plane->orig = orig;
	plane->normal = normal;
	return (plane);
}

t_bool		hit_plane(t_object *world, t_ray *r, t_hit_record *rec)
{
	t_plane	*plane;
	double	denom;
	double	t;
	
	plane = world->element;
	denom = vdot(plane->normal, r->dir);
	if (denom > 1e-6)
		return (FALSE);
	// printf("denom : %f\n", denom);
	t = vdot(vsub(plane->orig, r->orig), plane->normal) / denom;
	// printf("t : %f\n", t);
	if (t > rec->tmin && t < rec->tmax)
	{
		rec->t = t;
		rec->p = ray_at(r, t);
		
		// if (vdot(r->dir, plane->normal) > 0)
			// plane->normal = vmul_t(-1, plane->normal);
		// rec->normal = plane->normal;
		
		set_face_normal(r, rec);

		return (TRUE);
	}
	return (FALSE);
}

t_bool	intersect_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	double	denom;
	double	nom;
	double	t;

	denom = vdot(plane->normal, ray->dir);
	nom = vdot(vsub(ray->orig, plane->orig), plane->normal);
	if (denom > 1e-6)
	{
		t = -nom / denom;
		if (t > 0.0001 && t < rec->tmax)
		{
			rec->t = t;
			rec->normal = plane->normal;
			rec->p = ray_at(ray, t);
			rec->p = vsum(rec->p, vmul_t(0.0001, rec->normal));
			return (TRUE);
		}
	}
	return (FALSE);
}

