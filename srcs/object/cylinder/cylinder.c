/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:43:01 by bahn              #+#    #+#             */
/*   Updated: 2022/05/10 00:53:51 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	cylinder_normal(t_cylinder *cy, t_hit_record *rec)
{
	t_vec3	tmp;
	t_vec3	normal;

	tmp = vsub(rec->p, cy->coord);
	normal = vunit(vsub(tmp, vmul_t(vdot(cy->dir, tmp), cy->dir)));
	return (normal);
}

t_bool	hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	double		t;
	double		t_disk_top;
	double		t_disk_bot;

	t = hit_cylinder_surface(cy, ray, rec);
	t_disk_top = hit_cylinder_disk(cy, ray, rec, cy->coord_top);
	t_disk_bot = hit_cylinder_disk(cy, ray, rec, cy->coord_bot);
	if (t == INFINITY && t_disk_top == INFINITY && t_disk_bot == INFINITY)
		return (FALSE);
	if (t < t_disk_top && t < t_disk_bot)
	{
		rec->t = t;
		rec->p = ray_at(ray, rec->t);
		rec->normal = cylinder_normal(cy, rec);
		set_face_normal(ray, rec);
		return (TRUE);
	}
	if (t_disk_top < t_disk_bot)
		rec->t = t_disk_top;
	else
		rec->t = t_disk_bot;
	rec->p = ray_at(ray, rec->t);
	rec->normal = cy->dir;
	set_face_normal(ray, rec);
	return (TRUE);
}

static double	cylinder_discriminant(t_cylinder *cy, t_ray *ray, \
										double *a, double *b)
{
	t_vec3	h;
	t_vec3	w;
	t_vec3	v;
	double	c;

	h = vunit(vsub(cy->coord_top, cy->coord_bot));
	w = vsub(ray->orig, cy->coord_bot);
	v = ray->dir;
	*a = vlength2(v) - pow(vdot(v, h), 2.0);
	*b = 2.0 * (vdot(v, w) - (vdot(v, h) * vdot(w, h)));
	c = vlength2(w) - pow(vdot(w, h), 2.0) - pow(cy->diameter / 2.0, 2.0);
	return (pow((*b), 2.0) - (4.0 * (*a) * c));
}

double	hit_cylinder_surface(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	double	a;
	double	b;
	double	discriminant;
	double	root;

	discriminant = cylinder_discriminant(cy, ray, &a, &b);
	if (discriminant < 0)
		return (INFINITY);
	root = (-b - sqrt(discriminant)) / (2.0 * a);
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-b + sqrt(discriminant)) / (2.0 * a);
		if (root < rec->tmin || root > rec->tmax)
			return (INFINITY);
	}
	if (vdot(vsub(ray_at(ray, root), cy->coord_bot), \
			vsub(cy->coord_top, cy->coord_bot)) < 0)
		return (INFINITY);
	if (vdot(vsub(ray_at(ray, root), cy->coord_bot), \
			vsub(cy->coord_top, cy->coord_bot)) \
			> vlength2(vsub(cy->coord_top, cy->coord_bot)))
		return (INFINITY);
	return (root);
}

double	hit_cylinder_disk(t_cylinder *cy, t_ray *ray, \
							t_hit_record *rec, t_point3 disk_coord)
{
	double		denom;
	double		numer;
	double		t;

	denom = vdot(cy->dir, ray->dir);
	if (fabs(denom) < EPSILON)
		return (INFINITY);
	numer = vdot(vsub(disk_coord, ray->orig), cy->dir);
	t = numer / denom;
	if (t < rec->tmin || t > rec->tmax)
		return (INFINITY);
	if (vlength2(vsub(ray_at(ray, t), disk_coord)) > pow(cy->diameter / 2, 2))
		return (INFINITY);
	return (t);
}
