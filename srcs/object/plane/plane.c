/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:17:09 by bahn              #+#    #+#             */
/*   Updated: 2022/04/15 14:53:11 by bahn             ###   ########.fr       */
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

t_bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec, t_color3 color)
{
	double	denom; // Denominator : 분모. 판별식의 분모
	double	numer; // Numerator : 분자. 판별식의 분자
	double	t; // 평면 방정식 결과 값

	denom = vdot(ray->dir, plane->dir); // 광선 단위 벡터와 평면의 방향 벡터 내적 연산
	numer = vdot(vsub(ray->orig, plane->coord), plane->dir);
	numer = vdot(vsub(plane->coord, ray->orig), plane->dir);

	if (denom < EPSILON) // 분모가 음수라면 t는 양수.
	{
		t = numer / denom;
		if (t > EPSILON && t < rec->tmax)
		{
			rec->t = t;
			rec->normal = plane->dir;
			rec->p = ray_at(ray, t);
			rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
			rec->albedo = vmul_t(1.0 / 255.0, color);
			return (TRUE);
		}
	}
	return (FALSE);
}
