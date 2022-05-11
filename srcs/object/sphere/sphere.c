/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:34:04 by bahn              #+#    #+#             */
/*   Updated: 2022/05/10 13:57:59 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sphere_hit_recorder(t_sphere *sp, t_ray *ray, \
								t_hit_record *rec, double t)
{
	rec->t = t;
	rec->p = ray_at(ray, rec->t);
	rec->normal = vunit(vsub(rec->p, sp->center));
	set_face_normal(ray, rec);
}

t_bool	hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		root;

	a = vlength2(ray->dir);
	half_b = vdot(vsub(ray->orig, sp->center), ray->dir);
	c = vlength2(vsub(ray->orig, sp->center)) - pow(sp->radius, 2.0);
	discriminant = pow(half_b, 2.0) - (a * c);
	if (discriminant < 0)
		return (FALSE);
	root = (-half_b - sqrt(discriminant)) / a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	sphere_hit_recorder(sp, ray, rec, root);
	return (TRUE);
}
