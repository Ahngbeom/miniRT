/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:24:03 by bahn              #+#    #+#             */
/*   Updated: 2022/04/27 12:58:03 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color3	diffuse_calculator(t_vec3 light_dir, t_color3 light_color, t_vec3 rec_normal)
{
	double		kd;
	
	kd = fmax(vdot(rec_normal, vunit(light_dir)), 0.0);
	return (vmul_t(kd, vmul_t(1.0 / 255.0, light_color)));
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	// v : 광원에서 교점으로 향하는 벡터
	// n : 교점의 법선 벡터
	// v - 2(v * n) * n
	return (vsub(v, vmul_t(vdot(v, n) * 2, n)));
}

t_color3	specular_calculator(t_vec3 ray_dir, t_vec3 light_dir, t_color3 light_color, t_vec3 rec_normal)
{
	t_vec3		view_dir; 		// 교점에서 카메라 원점으로 향하는 벡터
	t_vec3		reflect_dir;	// 교점의 법선 벡터를 기준으로 light_dir을 대칭시킨 벡터
	double		ksn; 			// 오브젝트의 반짝거리는 정도
	double		ks; 			// 정반사광 강도
	double		spec; 			// 카메라->교점 정규화 방향 벡터와 반사광 법선 벡터의 cosθ을 구한 후 cosθ ^ ksn 적용
	
	view_dir = vunit(vmul_t(-1.0, ray_dir)); // 카메라 원점에서 교점으로 향하는 벡터를 반전시킨 후 정규화
	reflect_dir = reflect(vmul_t(-1.0, vunit(light_dir)), rec_normal); // 반사광 벡터 계산
	ksn = 128; // Shininess Value
	ks = 0.2; // Specular Strength
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn); // cosθ ^ ksn. 물체의 하이라이팅 범위 적용
	return (vmul_t(spec, vmul_t(ks, vmul_t(1.0 / 255.0, light_color)))); // spec * ks * light_color. 정반사광 강도 적용
}

t_color3	get_point_light(t_scene *scene, t_light *light)
{
	t_vec3		light_dir;
	t_color3	diffuse;
	t_color3	specular;
	double		brightness;

	light_dir = vsub(light->orig, scene->rec.p);

	if (shadow_checker(scene->objects, light_dir, scene->rec))
		return (color_init(0, 0, 0));

	// Diffuse
	diffuse = diffuse_calculator(light_dir, light->light_color, scene->rec.normal);
	
	// Specular
	specular = specular_calculator(scene->ray.dir, light_dir, light->light_color, scene->rec.normal);
	
	// Brightness
	brightness = light->bright_ratio * LUMEN;
	return (vmul_t(brightness, vsum(vsum(diffuse, scene->ambient.color), specular)));
}