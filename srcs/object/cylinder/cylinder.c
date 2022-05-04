/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:43:01 by bahn              #+#    #+#             */
/*   Updated: 2022/05/04 16:08:04 by jseol            ###   ########.fr       */
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
	cy->dir = normal;
	cy->diameter = 14.2;
	cy->height = 21.42;
	return (cy);
}

static t_vec3		cylinder_normal(t_cylinder *cy, t_hit_record *rec)
{
	t_vec3	tmp;
	t_vec3	normal;

	tmp = vsub(rec->p, cy->coord);
	normal = vunit(vsub(tmp, vmul_t(vdot(cy->dir, tmp), cy->dir)));
	return (normal);
}

t_bool		hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	double		t;
	double		t_disk_top;
	double		t_disk_bot;

	t = hit_cylinder_surface(cy, ray, rec);
	t_disk_top = hit_cylinder_disk(cy, ray, rec, TRUE);
	t_disk_bot = hit_cylinder_disk(cy, ray, rec, FALSE);
	if (t == INFINITY && t_disk_top == INFINITY && t_disk_bot == INFINITY)
		return (FALSE);
	if (t < t_disk_top && t < t_disk_bot)
	{
		rec->t = t;
		rec->p = ray_at(ray, rec->t);
		rec->normal = cylinder_normal(cy, rec);
		set_face_normal(ray, rec);
	}
	else
	{
		if (t_disk_top < t_disk_bot)
			rec->t = t_disk_top;
		else
			rec->t = t_disk_bot;
		rec->p = ray_at(ray, rec->t);
		rec->normal = cy->dir;
		set_face_normal(ray, rec);
	}
	// if (rec->t < INFINITY)
	// {
	// 	printf("%f\n", rec->t);
	// }
	return (TRUE);
}

double		hit_cylinder_surface(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	// double		a;
	// double		half_b;
	// double		c;
	// double		d;
	// double		t;

	// a = vlength2(vcross(ray->dir, cy->dir));
	// half_b = vdot(vcross(ray->dir, cy->dir), vcross(vsub(ray->orig, cy->coord_bot), cy->dir));
	// c = vlength2(vcross(vsub(ray->orig, cy->coord_bot), cy->dir)) - pow(cy->diameter / 2, 2);
	// d = half_b * half_b - a * c;
	// if (d < 0)
	// 	return (INFINITY);
	// t = (-half_b - sqrt(d)) / a;
	// if (t < rec->tmin || t > rec->tmax)
	// {
	// 	t = (-half_b + sqrt(d)) / a;
	// 	if (t < rec->tmin || t > rec->tmax)
	// 		return (INFINITY);
	// }
	// if (vdot(vsub(ray_at(ray, t), cy->coord_bot), vsub(cy->coord_top, cy->coord_bot)) < 0)
	// 	return (INFINITY);
	// if (vdot(vsub(ray_at(ray, t), cy->coord_bot), vsub(cy->coord_top, cy->coord_bot)) > vlength2(vsub(cy->coord_top, cy->coord_bot)))
	// 	return (INFINITY);
	// return (t);

	t_vec3	h;
	t_vec3	w;
	t_vec3	v;

	double	a;
	double	b;
	double	c;
	double	discriminant;

	double	root;

	h = vunit(vsub(cy->coord_top, cy->coord_bot));
	w = vsub(ray->orig, cy->coord_bot);
	v = ray->dir;

	a = vlength2(v) - pow(vdot(v, h), 2.0);
	b = 2.0 * (vdot(v, w) - (vdot(v, h) * vdot(w, h)));
	c = vlength2(w) - pow(vdot(w, h), 2.0) -  pow(cy->diameter / 2.0, 2.0);

	discriminant = pow(b, 2.0) - (4.0 * a * c);
	if (discriminant < 0)
		return (INFINITY);
	root = (-b - sqrt(discriminant)) / (2.0 * a);
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-b + sqrt(discriminant)) / (2.0 * a);
		if (root < rec->tmin || root > rec->tmax)
			return (INFINITY);
	}
	if (vdot(vsub(ray_at(ray, root), cy->coord_bot), vsub(cy->coord_top, cy->coord_bot)) < 0)
		return (INFINITY);
	if (vdot(vsub(ray_at(ray, root), cy->coord_bot), vsub(cy->coord_top, cy->coord_bot)) > vlength2(vsub(cy->coord_top, cy->coord_bot)))
		return (INFINITY);
	return (root);
}

double		hit_cylinder_disk(t_cylinder *cy, t_ray *ray, t_hit_record *rec, t_bool is_top)
{
	t_point3	p;
	t_point3	p0;
	double		denominator;
	t_vec3		r0_p0;
	double		t;

	if (is_top == TRUE)
		p0 = cy->coord_top;
	else
		p0 = cy->coord_bot;
	denominator = vdot(cy->dir, ray->dir);
	if (fabs(denominator) < EPSILON)
		return (INFINITY);
	r0_p0 = vsub(p0, ray->orig);
	t = vdot(r0_p0, cy->dir) / denominator;
	if ((t < rec->tmin || t > rec->tmax))
		return (INFINITY);
	p = ray_at(ray, t);
	if (vlength2(vsub(p, p0)) > pow(cy->diameter / 2, 2))
		return (INFINITY);
	return (t);
}

t_bool		interfere_cylinder(t_cylinder *cy, t_ray *ray, double limit)
{
	t_hit_record	rec;
	double			r_t;
	double			c_t;

	rec.tmin = EPSILON;
	rec.tmax = limit;
	r_t = hit_cylinder_surface(cy, ray, &rec);
	c_t = hit_cylinder_disk(cy, ray, &rec, TRUE);
	if (r_t == INFINITY && c_t == INFINITY)
		return (FALSE);
	return (TRUE);
}
