/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:17:09 by bahn              #+#    #+#             */
/*   Updated: 2022/04/22 21:10:34 by bahn             ###   ########.fr       */
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

t_bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	double	denom;
	double	numer;
	double	t;

	denom = vdot(ray->dir, plane->dir); // 광선 단위 벡터와 평면의 방향 벡터 내적 연산
	numer = vdot(vsub(plane->coord, ray->orig), plane->dir);
	t = numer / denom;
	if (t > rec->tmin && t < rec->tmax)
	{
		rec->t = t;
		rec->p = ray_at(ray, t);
		rec->normal = vmul_t(-1, plane->dir);
		return (TRUE);
	}
	return (FALSE);
}
