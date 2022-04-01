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
	plane->coord = orig;
	plane->normal = normal;
	return (plane);
}

t_bool		hit_plane(t_object *objects, t_ray *r, t_hit_record *rec)
{
	t_plane	*plane;
	double	denom;
	double	t;
	
	plane = objects->element;
	denom = vdot(plane->normal, r->dir);
	if (denom > EPSILON)
		return (FALSE);
	t = vdot(vsub(plane->coord, r->orig), plane->normal) / denom;
	if (t > rec->tmin && t < rec->tmax)
	{
		rec->t = t;
		rec->p = ray_at(r, t);
		
		if (vdot(r->dir, plane->normal) > 0)
			plane->normal = vmul_t(-1, plane->normal);
		rec->normal = plane->normal;
		
		rec->albedo = vmul_t(1.0 / 255.0, objects->color);
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
	nom = vdot(vsub(ray->orig, plane->coord), plane->normal);
	printf("Plane Normal : %f, %f, %f\n", plane->normal.x, plane->normal.y, plane->normal.z);
	printf("Ray Direction : %f, %f, %f\n", ray->dir.x, ray->dir.y, ray->dir.z);
	printf("denom : %f\n\n", denom);

	printf("Ray Coodinates : %f, %f, %f\n", ray->orig.x, ray->orig.y, ray->orig.z);
	printf("Plane Coodinates : %f, %f, %f\n", plane->coord.x, plane->coord.y, plane->coord.z);
	printf("Plane Normal : %f, %f, %f\n", plane->normal.x, plane->normal.y, plane->normal.z);
	printf("nom : %f\n\n", nom);

	printf("t : %f\n\n", -nom / denom);
	printf("tmax : %f\n\n", rec->tmax);

	printf("EPSILON : %f\n\n", EPSILON);
	sleep(1);
	if (denom > EPSILON)
	{
		t = -nom / denom;
		if (t > EPSILON && t < rec->tmax)
		{
			// printf("Shadow.\n");
			rec->t = t;
			rec->normal = plane->normal;
			rec->p = ray_at(ray, t);
			rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
			rec->albedo = color_init(0, 0, 0);
			return (TRUE);
		}
	}
	return (FALSE);
}

t_bool	in_shadow(t_object *objects, t_ray ray, double light_length)
{
	t_hit_record rec;
	
	rec.tmin = 0;
	rec.tmax = light_length;
	if (hit(objects, &ray, &rec))
		return (TRUE);
	else
		return (FALSE);
}
