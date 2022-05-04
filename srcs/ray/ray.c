/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:17:31 by bahn              #+#    #+#             */
/*   Updated: 2022/05/05 00:59:47 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_init(t_point3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.orig = origin;
	ray.dir = direction;
	return (ray);
}

t_point3	ray_at(t_ray *r, double t)
{
	return (vsum(r->orig, vmul_t(t, r->dir)));
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	ray.dir = vsum(cam->lower_left_corner, vmul_t(u, cam->horizontal));
	ray.dir = vsum(ray.dir, vmul_t(v, cam->vertical));
	ray.dir = vsub(ray.dir, cam->orig);
	ray.dir = vunit(ray.dir);
	return (ray);
}

t_color3	ray_color(t_scene *scene)
{
	if (scene->objects != NULL && scene->objects->type >= 0 && \
								scene->objects->element != NULL)
	{
		scene->rec.tmin = EPSILON;
		scene->rec.tmax = INFINITY;
		if (hit(scene->objects, &scene->ray, &scene->rec) == TRUE)
			return (phong_lighting(scene));
	}
	return (skyview_by_ray(&scene->ray));
}
