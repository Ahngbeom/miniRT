/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:54:22 by bahn              #+#    #+#             */
/*   Updated: 2022/03/31 14:56:37 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*light_init(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
	t_light	*light;

	light = ft_calloc(sizeof(t_light), 1);
	if (light == NULL)
		return (NULL);
	light->orig = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}

static t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vsub(v, vmul_t(vdot(v, n) * 2, n)));
}

static t_color3	point_light_get(t_scene *scene, t_light *light)
{
	// Diffuse
	t_color3	diffuse;
	t_vec3		light_dir;
	double		kd;

	// Specular
	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		spec;
	double		ksn;
	double		ks;

	// Bright
	double		brightness;

	// Shadow
	double		light_len;
	t_ray		light_ray;

	// Diffuse
	light_dir = vunit(vsub(scene->light.orig, scene->rec.p));
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	diffuse = vmul_t(kd, vmul_t(1.0 / 255.0, scene->light.light_color));

	// Shadow
	light_len = vlength(vsub(scene->light.orig, scene->rec.p));
	light_ray = ray_init(vsum(scene->rec.p, vmul_t(EPSILON, scene->rec.normal)), light_dir);
	if (in_shadow(scene->objects, light_ray, light_len))
		return (color_init(0, 0, 0));

	// Specular
	view_dir = vunit(vmul_t(-1.0, scene->ray.dir));
	reflect_dir = reflect(vmul_t(-1.0, light_dir), scene->rec.normal);
	ksn = 64;
	ks = 0.5;
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmul_t(spec, vmul_t(ks, light->light_color));

	// Brightness
	brightness = light->bright_ratio * LUMEN;
	
	return (vmul_t(brightness, vsum(vsum(diffuse, scene->ambient.color), specular)));
}

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;

	light_color = color_init(0, 0, 0);
	light_color = vsum(light_color, point_light_get(scene, &scene->light));

	scene->ambient.color = vmul_t(scene->ambient.ratio, vmul_t(1.0 / 255.0, scene->ambient.color));
	light_color = vsum(light_color, scene->ambient.color);

	// printf("Albedo : %f, %f, %f\n", scene->rec.albedo.x, scene->rec.albedo.y, scene->rec.albedo.z);
	// printf("Light Color : %f, %f, %f\n", light_color.x, light_color.y, light_color.z);
	// printf("%f, %f, %f\n", vmul(scene->rec.albedo, light_color).x, vmul(scene->rec.albedo, light_color).y, vmul(scene->rec.albedo, light_color).z);
	// sleep(1);
	return (vmin(vmul(scene->rec.albedo, light_color), color_init(1, 1, 1)));
}