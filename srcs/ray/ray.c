/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:17:31 by bahn              #+#    #+#             */
/*   Updated: 2022/04/14 16:18:33 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray		ray_init(t_point3 origin, t_vec3 direction) // ray 정규화, 초기화
{
	t_ray	ray;
	
	ray.orig = origin;
	// ray.dir = direction;
	ray.dir = vunit(direction); // 단위 벡터
	return (ray);
}

t_point3	ray_at(t_ray *r, double t) // 광선의 원점부터 광선의 방향으로 t만큼 떨어진 점 반환
{
	return (vsum(r->orig, vmul_t(t, r->dir)));
}

t_ray		ray_primary(t_camera *cam, double u, double v) // 가장 처음 카메라에서 출발한 광선
{
	t_ray	ray;

	ray.orig = cam->orig;
	
	// lower_left_corner + (u * horizontal) + (v * vertical) - origin 의 단위 벡터
	ray.dir	= vunit(vsub(vsum(vsum(cam->lower_left_corner, vmul_t(u, cam->horizontal)), vmul_t(v, cam->vertical)), cam->orig));
	return (ray);
}

t_color3 	ray_color(t_scene *scene)
{
	double			t;

	if (scene->objects != NULL && scene->objects->type >= 0 && scene->objects->element != NULL)
	{
		scene->rec.tmin = EPSILON; // 오브젝트와 카메라 간 거리 최솟값
		scene->rec.tmax = INFINITY; // 오브젝트와 카메라 간 거리 최댓값
		scene->rec.front_face = 0; // 오브젝트와 카메라 간 거리 최댓값
		if (hit(scene->objects, &scene->ray, &scene->rec) == TRUE)
		{
			return (phong_lighting(scene));
		}
	}
	// 광선의 방향 단위 벡터 y축을 통해 색상 결정
	t = 0.5 * (scene->ray.dir.y + 1.0);

	// ((1 - t) * 흰색) + (t * 하늘색)
	return (vsum(vmul_t(1.0 - t, vector_init(1.0, 1.0, 1.0)), vmul_t(t, vector_init(0.5, 0.7, 1.0))));
}