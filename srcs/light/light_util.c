/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:24:03 by bahn              #+#    #+#             */
/*   Updated: 2022/04/25 16:00:06 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color3	diffuse_calculator(t_vec3 light_dir, t_color3 light_color, t_vec3 rec_normal)
{
	double		kd; // Diffuse 강도
	
	// light_dir과 rec_normal은 단위벡터이기 때문에 두 단위 벡터의 내적 연산의 결과는 cosθ가 된다.
	// 사이각 θ가 0~90도 일때, cosθ 값은 1 ~ 0이므로,
	// cosθ는 θ값이 90도일 때 0, θ가 둔각이 되면 음수. 음수일 경우 0.0으로 대체.
	kd = fmax(vdot(rec_normal, vunit(light_dir)), 0.0);
	// if (kd == 0.0)
	// 	kd = EPSILON;
		// return (color_init(1, 1, 1));
	// printf("Record Normal : %f, %f, %f\n", rec_normal.x, rec_normal.y, rec_normal.z);
	// printf("Light Direction : %f, %f, %f\n", light_dir.x, light_dir.y, light_dir.z);
	// diffuse의 강도와 빛의 양을 곱해주면 교점에 도달한 빛의 양을 계산할 수 있다.
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

t_color3	get_point_light(t_scene *scene)
{
	t_vec3		light_dir;
	t_color3	diffuse;
	t_color3	specular;
	double		brightness;

	// Light Direction
	light_dir = vsub(scene->light.orig, scene->rec.p); // 교점과 광원까지의 거리

	// Shadow
	if (shadow_checker(scene->objects, light_dir, scene->rec))
		return (color_init(0, 0, 0));

	// Diffuse
	// diffuse = color_init(0.336313, 0.940952, 0.336313);
	// diffuse = color_init(1, 1, 1);
	// diffuse = color_init(0.5, 0.5, 0.5);
	diffuse = diffuse_calculator(light_dir, scene->light.light_color, scene->rec.normal);
	// printf("Diffuse : %f, %f, %f\n", diffuse.x, diffuse.y, diffuse.z);
	
	// Specular
	// specular = color_init(0, 0, 0);
	specular = specular_calculator(scene->ray.dir, light_dir, scene->light.light_color, scene->rec.normal);
	
	// Brightness
	brightness = scene->light.bright_ratio * LUMEN;
	return (vmul_t(brightness, vsum(vsum(diffuse, scene->ambient.color), specular)));
}