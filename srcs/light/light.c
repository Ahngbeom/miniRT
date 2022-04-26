/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:54:22 by bahn              #+#    #+#             */
/*   Updated: 2022/04/26 22:20:54 by bahn             ###   ########.fr       */
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
	t_color3	light_color; // 빛의 양, 정도를 저장하기 위한 변수

	scene->ambient.color = vmul_t(scene->ambient.ratio, vmul_t(1.0 / 255.0, scene->ambient.color));
	light_color = color_init(0, 0, 0); // 광원이 없을 경우, 빛의 양은 0
	// light_color = get_point_light(scene); // diffuse, specular 계산

	// printf("Albedo : %f, %f, %f\n", scene->rec.albedo.x, scene->rec.albedo.y, scene->rec.albedo.z);
	// printf("Ambient Color : %f, %f, %f\n", scene->ambient.color.x, scene->ambient.color.y, scene->ambient.color.z);
	// printf("Light Color : %f, %f, %f\n", light_color.x, light_color.y, light_color.z);

	light_color = vsum(light_color, scene->ambient.color);

	
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
	
	light_color = color_init(0, 0, 0);
	lights = scene->lights;
	while (lights)
	{
		light = lights->content;
		light_dir = vsub(light->orig, scene->rec.p);
		
		kd = fmax(vdot(vunit(scene->rec.normal), vunit(light_dir)), 0.0);
		diffuse = vmul_t(kd, vdiv(light->light_color, 255));
		light_color = vsum(light_color, diffuse);
		(void)diffuse;
		(void)kd;
		
		light_color = vsum(light_color, vdiv(vmul_t(scene->ambient.ratio, scene->ambient.color), 255));
		lights = lights->next;
	}
	return (vmin(vmul(light_color, scene->rec.albedo), color_init(1, 1, 1)));
}
