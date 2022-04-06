/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:17:09 by bahn              #+#    #+#             */
/*   Updated: 2022/04/06 17:03:40 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane		*plane_init(t_point3 orig, t_vec3 normal)
{
	t_plane	*plane;

	plane = ft_calloc(sizeof(t_plane), 1);
	if (plane == NULL)
		return (NULL);
	plane->coord = orig;
	plane->dir = normal;
	return (plane);
}

t_bool		hit_plane(t_object *objects, t_ray *ray, t_hit_record *rec)
{
	t_plane	*plane;
	double	numer;	// Numerator : 분자. 판별식의 분자
	double	denom;	// Denominator : 분모. 판별식의 분모
	double	root;	// 판별식 결과 값
	
	plane = objects->element;
	denom = vdot(plane->dir, ray->dir);
	numer = vdot(vsub(plane->coord, ray->orig), plane->dir);
	root = numer / denom;

	// printf("Plane Coodinates : %f, %f, %f\n", plane->coord.x, plane->coord.y, plane->coord.z);
	// printf("Plane Normal : %f, %f, %f\n", plane->normal.x, plane->normal.y, plane->normal.z);
	// printf("Ray Coodinates : %f, %f, %f\n", ray->orig.x, ray->orig.y, ray->orig.z);
	// printf("Ray Direction : %f, %f, %f\n", ray->dir.x, ray->dir.y, ray->dir.z);
	// printf("Denominator : %f\n", denom);
	// printf("Numerator : %f\n", numer);
	// printf("Root : %f\n\n", root);
	// printf("tmin : %f\n", rec->tmin);
	// printf("tmax : %f\n\n", rec->tmax);

	// if (denom > EPSILON)
	// 	return (FALSE);
	if (root < rec->tmin || root > rec->tmax)
		return (FALSE);

	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = plane->dir;
	
	// if (vdot(ray->dir, plane->normal) > 0)
	// 	rec->normal = vmul_t(-1, plane->normal);
	// else
		// rec->normal = plane->normal;
	
	rec->albedo = vmul_t(1.0 / 255.0, objects->color);
	return (TRUE);
}

t_bool	intersect_plane(t_object *objects, t_ray *ray, t_hit_record *rec)
{
	t_plane	*plane;
	double	denom; // Denominator : 분모. 판별식의 분모
	double	numer; // Numerator : 분자. 판별식의 분자
	double	t; // 평면 방정식 결과 값

	plane = objects->element;
	denom = vdot(ray->dir, plane->dir); // 광선 단위 벡터와 평면의 방향 벡터 내적 연산
	numer = vdot(vsub(ray->orig, plane->coord), plane->dir);

	// printf("Plane Normal : %f, %f, %f\n", plane->normal.x, plane->normal.y, plane->normal.z);
	// printf("Ray Direction : %f, %f, %f\n", ray->dir.x, ray->dir.y, ray->dir.z);
	// printf("denom : %f\n\n", denom);

	// printf("Ray Coodinates : %f, %f, %f\n", ray->orig.x, ray->orig.y, ray->orig.z);
	// printf("Plane Coodinates : %f, %f, %f\n", plane->coord.x, plane->coord.y, plane->coord.z);
	// printf("Plane Normal : %f, %f, %f\n", plane->normal.x, plane->normal.y, plane->normal.z);
	// printf("numer : %f\n\n", numer);

	// printf("t : %f\n\n", -numer / denom);
	// printf("tmin : %f\n\n", rec->tmin);
	// printf("tmax : %f\n\n", rec->tmax);

	// sleep(1);
	if (denom < EPSILON) // 분모가 음수라면 t는 양수.
	{
		t = -numer / denom;
		if (t > EPSILON && t < rec->tmax)
		{
			rec->t = t;
			rec->normal = plane->dir;
			rec->p = ray_at(ray, t);
			rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
			rec->albedo = vmul_t(1.0 / 255.0, objects->color);
			return (TRUE);
		}
	}
	return (FALSE);
}
