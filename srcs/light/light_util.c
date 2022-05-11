/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:24:03 by bahn              #+#    #+#             */
/*   Updated: 2022/05/05 11:37:48 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color3	diffuse_calculator(t_vec3 light_dir, t_color3 light_color, \
									t_vec3 rec_normal)
{
	double		kd;

	kd = fmax(vdot(rec_normal, vunit(light_dir)), 0.0);
	return (vmul_t(kd, vmul_t(1.0 / 255.0, light_color)));
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vsub(v, vmul_t(vdot(v, n) * 2, n)));
}

t_color3	specular_calculator(t_vec3 ray_dir, t_vec3 light_dir, \
									t_color3 light_color, t_vec3 rec_normal)
{
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		ksn;
	double		ks;
	double		spec;

	view_dir = vunit(vmul_t(-1.0, ray_dir));
	reflect_dir = reflect(vmul_t(-1.0, vunit(light_dir)), rec_normal);
	ksn = 128;
	ks = 0.2;
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	return (vmul_t(spec, vmul_t(ks, vmul_t(1.0 / 255.0, light_color))));
}

t_color3	get_point_light(t_scene *scene, t_light *light)
{
	t_vec3		light_dir;
	t_color3	diffuse;
	t_color3	specular;
	t_color3	ambient;
	double		brightness;

	light_dir = vsub(light->orig, scene->rec.p);
	if (shadow_checker(scene->objects, light_dir, scene->rec))
		return (color_init(0, 0, 0));
	diffuse = diffuse_calculator(light_dir, light->light_color, \
									scene->rec.normal);
	specular = specular_calculator(scene->ray.dir, light_dir, \
									light->light_color, scene->rec.normal);
	ambient = vmul_t(scene->ambient.ratio, vdiv(scene->ambient.color, 255));
	brightness = light->bright_ratio * LUMEN;
	return (vmul_t(brightness, \
				vsum(vsum(diffuse, ambient), specular)));
}
