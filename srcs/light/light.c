/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:54:22 by bahn              #+#    #+#             */
/*   Updated: 2022/05/05 11:39:48 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*light_init(t_point3 light_origin, t_color3 light_color, \
												double bright_ratio)
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
	t_light		*light;
	t_color3	light_color;
	t_vec3		light_dir;

	light_color = color_init(0, 0, 0);
	lights = scene->lights;
	while (lights)
	{
		light = lights->content;
		light_dir = vunit(vsub(light->orig, scene->rec.p));
		if (shadow_checker(scene->objects, vsub(light->orig, scene->rec.p), \
				scene->rec))
			light_color = vsum(light_color, color_init(0, 0, 0));
		else
		{
			light_color = vsum(light_color, \
		diffuse_calculator(light_dir, light->light_color, scene->rec.normal));
			light_color = vmul_t(light->bright_ratio * LUMEN, light_color);
		}
		lights = lights->next;
	}
	light_color = vsum(light_color, \
				vdiv(vmul_t(scene->ambient.ratio, scene->ambient.color), 255));
	return (vmin(vmul(light_color, scene->rec.albedo), color_init(1, 1, 1)));
}
