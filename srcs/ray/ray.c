/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:17:31 by bahn              #+#    #+#             */
/*   Updated: 2022/03/30 19:28:49 by bahn             ###   ########.fr       */
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

t_point3	ray_at(t_ray *r, double t) // 광선의 원점부터 방향 벡터만큼 떨어진 점 반환
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

t_color 	ray_color(t_object *world, t_ray *ray)
{
	double			t;
	t_hit_record	rec;

	if (world != NULL && world->element != NULL && world->type >= 0)
	{
		rec.tmin = 0; // 오브젝트와 카메라 간 거리 최솟값
		rec.tmax = INFINITY; // 오브젝트와 카메라 간 거리 최댓값
		rec.front_face = 0; // 오브젝트 교점 위치(앞면 / 뒷면) 판단
		if (hit(world, ray, &rec) == TRUE)
		{
			return (vmul_t(0.5, vsum(rec.normal, world->color)));
		}
	}
	// 광선의 방향 단위 벡터 y축을 통해 색상 결정
	t = 0.5 * (ray->dir.y + 1.0);

	// ((1 - t) * 흰색) + (t * 하늘색)
	return (vsum(vmul_t(1.0 - t, vector_init(1.0, 1.0, 1.0)), vmul_t(t, vector_init(0.5, 0.7, 1.0))));
}

// t_color 	ray_color(int type, void *obj, t_ray *r) // 광선이 최종적으로 얻게 된 픽셀의 색상 값 반환. 색상 결정
// {
//     double			t;
// 	t_vec3			normal;
// 	t_hit_record	rec;

// 	if (type >= 0 && obj != NULL)
// 	{
// 		rec.tmin = 0;
// 		rec.tmax = INFINITY;
// 		rec.front_face = 0;
// 		if (type == SPHERE)// && ((t_sphere*)obj)->hit_func(obj, r))
// 		{
// 			// t = ((t_sphere*)obj)->hit_func(obj, r);
// 			// t = hit_sphere_record(obj, r, &rec);
// 			if (hit_sphere_record(obj, r, &rec) > 0)
// 			{
// 				// 정규화된 구 표면에서의 법선 벡터
// 				normal = vunit(vsub(ray_at(r, rec.t), ((t_sphere*)obj)->center));
				
// 				return (vmul_t(0.5, color_init(normal.x + 1, normal.y + 1, normal.z + 1)));
// 				// return (color_init(0, 1, 0));
// 			}
// 		}
// 		else if (type == PLANE && ((t_plane*)obj)->hit_func(obj, r))
// 			return (color_init(1, 0, 0));
// 	}
// 	// 광선의 방향 단위 벡터 y축을 통해 색상 결정
// 	t = 0.5 * (r->dir.y + 1.0);

// 	// ((1 - t) * 흰색) + (t * 하늘색)
// 	return (vsum(vmul_t(1.0 - t, vector_init(1.0, 1.0, 1.0)), vmul_t(t, vector_init(0.5, 0.7, 1.0))));
// }