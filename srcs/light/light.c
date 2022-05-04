/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:54:22 by bahn              #+#    #+#             */
/*   Updated: 2022/05/04 16:07:43 by jseol            ###   ########.fr       */
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

t_color3	phong_lighting(t_scene *scene)
{
	t_list		*lights;
	t_color3	light_color; // 빛의 양, 정도를 저장하기 위한 변수

	light_color = color_init(0, 0, 0); // 광원이 없을 경우, 빛의 양은 0
	lights = scene->lights;
	while (lights)
	{
		light_color = vsum(light_color, get_point_light(scene, lights->content)); // diffuse, specular 계산
		lights = lights->next;
	}

	// printf("Albedo : %f, %f, %f\n", scene->rec.albedo.x, scene->rec.albedo.y, scene->rec.albedo.z);
	// printf("Ambient Color : %f, %f, %f\n", scene->ambient.color.x, scene->ambient.color.y, scene->ambient.color.z);
	// printf("Light Color : %f, %f, %f\n", light_color.x, light_color.y, light_color.z);

	light_color = vsum(light_color, vmul_t(scene->ambient.ratio, vdiv(scene->ambient.color, 255)));


	// printf("%f, %f, %f\n", vmul(scene->rec.albedo, light_color).x, vmul(scene->rec.albedo, light_color).y, vmul(scene->rec.albedo, light_color).z);
	// sleep(1);
	return (vmin(vmul(scene->rec.albedo, light_color), color_init(1, 1, 1)));
}

t_color3	phong_lighting2(t_scene *scene)
{
	t_list		*lights;
	t_light		*light;
	t_color3	light_color;
	t_vec3		light_dir;

	t_color3	diffuse;
	double		kd;

	// t_color3	specular;
	// t_vec3		view_dir;
	// t_vec3		reflect_dir;
	// double		spec;
	// double		ksn;
	// double		ks;

	double		brightness;

	light_color = color_init(0, 0, 0);
	lights = scene->lights;
	while (lights)
	{
		light = lights->content;
		light_dir = vsub(light->orig, scene->rec.p);
		if (shadow_checker(scene->objects, light_dir, scene->rec))
			light_color = vsum(light_color, color_init(0, 0, 0));
		else
		{
			kd = fmax(vdot(scene->rec.normal, vunit(light_dir)), 0.0);
			diffuse = vmul_t(kd, vdiv(light->light_color, 255));
			light_color = vsum(light_color, diffuse);

			// view_dir = vunit(vmul_t(-1.0, scene->ray.dir));
			// reflect_dir = reflect(vmul_t(-1.0, light_dir), scene->rec.normal);
			// ksn = 64;
			// ks = 0.5;
			// spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
			// specular = vmul_t(spec, vmul_t(ks, light->light_color));
			// light_color = vsum(light_color, specular);

			brightness = light->bright_ratio * LUMEN;
			light_color = vmul_t(brightness, light_color);
		}
		lights = lights->next;
	}
	light_color = vsum(light_color, vdiv(vmul_t(scene->ambient.ratio, scene->ambient.color), 255));
	return (vmin(vmul(light_color, scene->rec.albedo), color_init(1, 1, 1)));
}
