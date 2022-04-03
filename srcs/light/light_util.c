/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:24:03 by bahn              #+#    #+#             */
/*   Updated: 2022/04/03 15:58:50 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vsub(v, vmul_t(vdot(v, n) * 2, n)));
}

static t_color3	diffuse_calculator(t_vec3 light_dir, t_color3 light_color, t_vec3 rec_normal)
{
	double		kd; // Diffuse 강도
	
	// light_dir과 rec_normal은 단위벡터이기 때문에 두 단위 벡터의 내적 연산의 결과는 cosθ가 된다.
	// 사이각 θ가 0~90도 일때, cosθ 값은 1 ~ 0이므로,
	// cosθ는 θ값이 90도일 때 0, θ가 둔각이 되면 음수. 음수일 경우 0.0으로 대체.
	kd = fmax(vdot(rec_normal, light_dir), 0.0);
	
	// diffuse의 강도와 빛의 양을 곱해주면 교점에 도달한 빛 의양을 계산할 수 있다.
	return (vmul_t(kd, vmul_t(1.0 / 255.0, light_color)));
}

static t_color3	specular_calculator(t_vec3 ray_dir, t_vec3 light_dir, t_color3 light_color, t_vec3 rec_normal)
{
	t_vec3		view_dir; 		// 교점에서 카메라 원점으로 향하는 벡터
	t_vec3		reflect_dir;	// 교점의 법선 벡터를 기준으로 light_dir을 대칭시킨 벡터
	double		ksn; 			// 오브젝트의 반짝거리는 정도
	double		ks; 			// 정반사광 강도
	double		spec; 			// specular
	
	view_dir = vunit(vmul_t(-1.0, ray_dir));
	reflect_dir = reflect(vmul_t(-1.0, light_dir), rec_normal);
	ksn = 2; // Shininess Value
	ks = 0.5; // Specular Strength
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	return (vmul_t(spec, vmul_t(ks, vmul_t(1.0 / 255.0, light_color))));
}

t_color3	get_point_light(t_scene *scene, t_light *light)
{
	t_vec3		light_dir; // 교점에 출발하여 광원을 향하는 정규화 벡터
	t_color3	diffuse;
	t_color3	specular;

	// Bright
	double		brightness;

	// Shadow
	double		light_len;
	t_ray		light_ray;

	// Light Direction
	light_dir = vunit(vsub(scene->light.orig, scene->rec.p));

	// Shadow
	light_len = vlength(vsub(scene->light.orig, scene->rec.p));
	light_ray = ray_init(vsum(scene->rec.p, vmul_t(EPSILON, scene->rec.normal)), light_dir);
	if (in_shadow(scene->objects, light_ray, light_len))
		return (color_init(0, 0, 0));

	// Diffuse
	diffuse = diffuse_calculator(light_dir, light->light_color, scene->rec.normal);

	// Specular
	specular = specular_calculator(scene->ray.dir, light_dir, light->light_color, scene->rec.normal);
	
	// Brightness
	brightness = light->bright_ratio * LUMEN;
	return (vmul_t(brightness, vsum(vsum(diffuse, scene->ambient.color), specular)));
}