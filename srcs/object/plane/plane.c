/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:17:09 by bahn              #+#    #+#             */
/*   Updated: 2022/05/05 11:51:43 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	double	denom;
	double	numer;
	double	t;

	denom = vdot(ray->dir, plane->dir);
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
