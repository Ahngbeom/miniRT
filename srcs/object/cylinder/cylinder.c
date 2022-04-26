/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:46:31 by bahn              #+#    #+#             */
/*   Updated: 2022/04/26 22:07:04 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*cylinder_init(t_point3 orig, t_vec3 normal)
{
	t_cylinder	*cy;

	cy = ft_calloc(sizeof(t_plane), 1);
	if (cy == NULL)
		return (NULL);
	cy->coord = orig;
	cy->dir = normal;
	cy->diameter = 14.2;
	cy->height = 21.42;
	return (cy);
}

t_bool		hit_cylinder(t_cylinder *cy, t_ray *r, t_hit_record *rec)
{
	double		surface_t;
	double		circle_t;

	surface_t = hit_cylinder_surface(cy, r, rec);
	circle_t = hit_cylinder_circle(cy, r, rec);
	if (surface_t == INFINITY && circle_t == INFINITY)
		return (FALSE);
	if (surface_t < circle_t)
	{
		rec->t = surface_t;
		rec->p = ray_at(r, rec->t);
		rec->normal = vunit(vsub(rec->p, vsum(vmul_t(vdot(vunit(vsub(cy->coord_top, cy->coord_bot)), vsub(rec->p, cy->coord_bot)), vunit(vsub(cy->coord_top, cy->coord_bot))), cy->coord_bot)));
		set_face_normal(r, rec);
	}
	else
	{
		rec->t = circle_t;
		rec->p = ray_at(r, rec->t);
		rec->normal = cy->dir;
		set_face_normal(r, rec);
	}
	return (TRUE);
}

double		hit_cylinder_surface(t_cylinder *cy, t_ray *r, t_hit_record *rec)
{
	// t_vec3	oc;
	
	t_vec3	h;
	t_vec3	w;
	
	double	a;
	// double	half_b;
	double	b;
	double	c;
	double	discriminant;
	double	t;

	// oc = vsub(r->orig, cy->coord);
	// a = vlength2(vcross(r->dir, cy->dir));
	// half_b = vdot(vcross(r->dir, cy->dir), vcross(oc, cy->dir));
	// c = vlength2(vcross(oc, cy->dir)) - pow(cy->diameter / 2, 2);

	h = vunit(vsub(cy->coord_top, cy->coord_bot));
	w = vsub(r->orig, cy->coord_bot);
	
	a = vlength2(r->dir) - pow(vdot(r->dir, h), 2.0);
	b = 2.0 * (vdot(r->dir, w) - (vdot(r->dir, h) * vdot(w, h)));
	c = vlength2(w) - pow(vdot(w, h), 2.0) -  pow(cy->diameter / 2.0, 2.0);
	
	discriminant = pow(b, 2.0) - (4.0 * a * c);	
	if (discriminant < 0)
		return (INFINITY);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < rec->tmin || t > rec->tmax)
	{
		t = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t < rec->tmin || t > rec->tmax)
			return (INFINITY);
	}
	// if (vdot(h, vsub(ray_at(r, t), cy->coord_top)) > 0)
	// 	return (INFINITY);
	// if (vdot(h, vsub(ray_at(r, t), cy->coord_bot)) < 0)
	// 	return (INFINITY);

	if (vdot(vsub(ray_at(r, t), cy->coord_bot), vsub(cy->coord_top, cy->coord_bot)) < 0)
		return (INFINITY);
	if (vdot(vsub(ray_at(r, t), cy->coord_bot), vsub(cy->coord_top, cy->coord_bot)) > vlength2(vsub(cy->coord_top, cy->coord_bot)))
		return (INFINITY);
	return (t);
}

double		hit_cylinder_circle(t_cylinder *cy, t_ray *r, t_hit_record *rec)
{
	double	denom;
	t_vec3	oc;
	double	t_top;
	double	t_bottom;

	// 광선과 원기둥의 법선 벡터의 내적이 0. 즉, 평행이라면 광선은 윗면이나 아랫면과 교차하지않는다.
	// 광선과 원기둥의 사이각이 윗면과 아랫면의 t를 구하기 위한 분모로 활용된다.
	denom = vdot(r->dir, cy->dir);
	if (denom == 0)
		return (FALSE);
	
	oc = vsub(cy->coord_top, r->orig); // 광선의 원점에서 윗면 또는 아랫면의 중심점까지의 벡터
	t_top = vdot(oc, cy->dir) / denom; // 윗면 또는 아랫면의 t : oc와 원기둥의 법선 벡터의 내적 값을 denom으로 나눈다.
	
	// 광원에서부터 t 만큼 떨어진 지점이 윗면 또는 아랫면의 중심점과의 거리가 원기둥의 반지름보다 높을 경우 광선과 원기둥의 윗면 또는 아랫면은 교차하지 않는다.
	if (vlength2(vsub(ray_at(r, t_top), cy->coord_top)) > pow(cy->diameter / 2, 2))
		t_top = INFINITY;
		
	oc = vsub(cy->coord_bot, r->orig); // 광선의 원점에서 윗면 또는 아랫면의 중심점까지의 벡터
	t_bottom = vdot(oc, cy->dir) / denom; // 윗면 또는 아랫면의 t : oc와 원기둥의 법선 벡터의 내적 값을 denom으로 나눈다.
	
	// 광원에서부터 t 만큼 떨어진 지점이 윗면 또는 아랫면의 중심점과의 거리가 원기둥의 반지름보다 높을 경우 광선과 원기둥의 윗면 또는 아랫면은 교차하지 않는다.
	if (vlength2(vsub(ray_at(r, t_bottom), cy->coord_bot)) > pow(cy->diameter / 2, 2))
		t_bottom = INFINITY;
	
	// 윗면 또는 아랫면의 t와 tmin, tmax를 비교하여 최소/최대 거리 범위에 속하는지 검사한다.
	if (t_top < rec->tmin || t_top > rec->tmax)
		t_top = INFINITY;
	if (t_bottom < rec->tmin || t_bottom > rec->tmax)
		t_top = INFINITY;
	
	if (t_top < t_bottom) // 가장 작은 근 대입
		return (t_top);
	else
		return (t_bottom);
}

t_bool		hit_cylinder_surface2(t_cylinder *cy, t_ray *r, t_hit_record *rec)
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
	// rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
	set_face_normal(r, rec);
	return (TRUE);
}

t_bool		hit_cylinder_circle2(t_cylinder *cy, t_ray *r, t_hit_record *rec, t_point3 circle_center)
{
	double	denom; // Denominator : 분모. 판별식의 분모
	double	numer; // Numerator : 분자. 판별식의 분자
	double	t; // 평면 방정식 결과 값
	
	denom = vdot(r->dir, cy->dir); // 광선 단위 벡터와 평면의 방향 벡터 내적 연산
	if (fabs(denom) < EPSILON)
		return (FALSE);
	numer = vdot(vsub(circle_center, r->orig), cy->dir);
	t = numer / denom;
	if (vlength2(vsub(ray_at(r, t), circle_center)) <= pow(cy->diameter / 2.0, 2.0))
	{
		if (t > rec->tmin && t < rec->tmax)
		{
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
	}
	return (FALSE);
}

t_bool		interfere_cylinder(t_cylinder *cy, t_ray *ray, double limit)
{
	t_hit_record	rec;
	double			r_t;
	double			c_t;

	rec.tmin = EPSILON;
	rec.tmax = limit;
	r_t = hit_cylinder_surface(cy, ray, &rec);
	c_t = hit_cylinder_circle(cy, ray, &rec);
	if (r_t == INFINITY && c_t == INFINITY)
		return (FALSE);
	return (TRUE);
}