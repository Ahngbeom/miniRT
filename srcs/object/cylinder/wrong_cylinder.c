/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:46:31 by bahn              #+#    #+#             */
/*   Updated: 2022/04/28 15:53:27 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_bool		hit_cylinder_surface(t_cylinder *cy, t_ray *r, t_hit_record *rec)
{
	t_vec3	h;
	t_vec3	w;
	t_vec3	v;
	
	double	a;
	double	b;
	double	c;
	double	discriminant;
	
	double	root;
	
	h = vunit(vsub(cy->coord_top, cy->coord_bot));
	w = vsub(r->orig, cy->coord_bot);
	v = r->dir;
	
	a = vlength2(v) - pow(vdot(v, h), 2.0);
	b = 2.0 * (vdot(v, w) - (vdot(v, h) * vdot(w, h)));
	c = vlength2(w) - pow(vdot(w, h), 2.0) -  pow(cy->diameter / 2.0, 2.0);
	
	discriminant = pow(b, 2.0) - (4.0 * a * c);	
	if (discriminant < 0)
		return (FALSE);
	root = (-b - sqrt(discriminant)) / (2.0 * a);
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-b + sqrt(discriminant)) / (2.0 * a);
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}

	// if (vdot(vsub(ray_at(r, root), cy->coord_top), cy->dir) > 0)
	// 	return (FALSE);
	// if (vdot(vsub(ray_at(r, root), cy->coord_bot), cy->dir) < 0)
	// 	return (FALSE);

	if (vdot(vsub(ray_at(r, root), cy->coord_bot), vsub(cy->coord_top, cy->coord_bot)) < 0)
		return (FALSE);
	if (vdot(vsub(ray_at(r, root), cy->coord_bot), vsub(cy->coord_top, cy->coord_bot)) > vlength2(vsub(cy->coord_top, cy->coord_bot)))
		return (FALSE);

	// if (vlength(vsub(ray_at(r, root), cy->coord)) > sqrt(pow(cy->diameter / 2, 2) + pow(cy->height / 2, 2)))
	// 	return (FALSE);
	rec->t = root;
	rec->p = ray_at(r, root);
	// rec->normal = vunit(vsub(vsub(rec->p, cy->coord), vmul_t(vdot(cy->dir, vsub(rec->p, cy->coord)), cy->dir)));
	rec->normal = vunit(vsub(vsub(rec->p, cy->coord_bot), vmul_t(vdot(h, vsub(rec->p, cy->coord_bot)), h)));
	// if (cy->dir.x != 0)
	// 	rec->normal = vunit(vsub(rec->p, point_init(rec->p.x, cy->coord_bot.y, cy->coord_bot.z)));
	// if (cy->dir.y != 0)
	// 	rec->normal = vunit(vsub(rec->p, point_init(cy->coord_bot.x, rec->p.y, cy->coord_bot.z)));
	// if (cy->dir.z != 0)
	// 	rec->normal = vunit(vsub(rec->p, point_init(cy->coord_bot.x, cy->coord_bot.y, rec->p.z)));
	// return (vunit(vsub(rec->p, c0)));
	// rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
	set_face_normal(r, rec);
	return (TRUE);
}

t_bool		hit_cylinder_circle(t_cylinder *cy, t_ray *r, t_hit_record *rec, t_point3 circle_center)
{
	double	denom; // Denominator : 분모. 판별식의 분모
	double	numer; // Numerator : 분자. 판별식의 분자
	double	t; // 평면 방정식 결과 값
	
	denom = vdot(r->dir, cy->dir); // 광선 단위 벡터와 평면의 방향 벡터 내적 연산
	if (fabs(denom) < EPSILON)
		return (FALSE);
	numer = vdot(vsub(circle_center, r->orig), cy->dir);
	t = numer / denom;
	if (t < rec->tmin || t > rec->tmax)
		return (FALSE);
	if (vlength2(vsub(ray_at(r, t), circle_center)) > pow(cy->diameter / 2.0, 2.0))
		return (FALSE);
	if (t < rec->t)
	{
		rec->t = t;
		rec->p = ray_at(r, rec->t);
		// rec->normal = vector_init(0.9, 0.9, 0.9); // 교점의 법선 벡터 : 평면의 방향 벡터의 역벡터
		rec->normal = cy->dir; // 교점의 법선 벡터 : 평면의 방향 벡터의 역벡터
		// rec->normal = vmul_t(-1, cy->dir); // 교/점의 법선 벡터 : 평면의 방향 벡터의 역벡터
		// rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
		set_face_normal(r, rec);
	}
	return (TRUE);
}