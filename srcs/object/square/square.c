/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:14:39 by bahn              #+#    #+#             */
/*   Updated: 2022/03/30 17:13:21 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_square	*square_init(t_point3 center, t_vec3 normal, double side_len)
{
	t_square	*sq;

	sq = ft_calloc(sizeof(t_square), 1);
	if (sq == NULL)
		return (NULL);
	sq->center = center;
	sq->normal = normal;
	sq->side_length = side_len;
	return (sq);
}

t_bool		hit_square(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_square	*sq;
	double		denom;
	double		nom;
	double		t;
	double		len;
	double		cosin;
	t_vec3		d;
	t_vec3		up;
	t_vec3		axis;
	
	sq = world->element;
	denom = vdot(sq->normal, ray->dir);
	nom = vdot(vsub(ray->orig, sq->center), sq->normal);

	if (denom == 0)
		return (FALSE);
	t = -nom / denom;
	d = vsub(ray_at(ray, t), sq->center);
	
	if (sq->normal.y != 0 && (sq->normal.x == 0 && sq->normal.z == 0))
		up = vector_init(0, 0, 1);
	else
		up = vector_init(0, 1, 0);
	axis = vcross(up, sq->normal);
	cosin = fabs(vdot(axis, d) / (vlength(axis) * vlength(d)));
	if (cosin < sqrt(2.0) / 2)
		cosin = cos((M_PI / 2) - acos(cosin));
	len = sq->side_length / cosin;
	// if (fabs(d.x) >= len || fabs(d.y) >= len || fabs(d.z) >= len)
	// 	return (FALSE);
	if (vlength(d) > len)
		return (FALSE);
	if (t >= 0)
	{
		rec->t = t;
		rec->normal = sq->normal;
		rec->p = ray_at(ray, t);
		rec->p = vsum(rec->p, vmul_t(0.0001, sq->normal));
		return (TRUE);
	}
	
	return (FALSE);
}