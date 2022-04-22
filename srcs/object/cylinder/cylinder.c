/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:46:31 by bahn              #+#    #+#             */
/*   Updated: 2022/04/22 23:33:11 by jaeyu            ###   ########.fr       */
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

t_vec3		get_cy_normal(t_cylinder *cy, t_hit_record *rec)
{
	t_vec3		tmp;
	t_vec3		normal;

	tmp = vsub(rec->p, cy->coord);
	normal = vunit(vsub(tmp, (vmul_t(vdot(cy->dir, tmp), cy->dir))));
	return (normal);
}

t_bool		hit_cylinder_surface(t_cylinder *cy, t_ray *r, t_hit_record *rec)
{
/*
	t_vec3		oc;
	
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		root;
	
	oc = vsub(r->orig, cy->coord); // 카메라 원점에서 원기둥의 중심점까지의 방향 벡터


	a = vlength2(vcross(r->dir, cy->dir));
	half_b = vdot(vcross(r->dir, cy->dir), vcross(oc, cy->dir));
	c = vlength2(vcross(oc, cy->dir)) - pow(cy->diameter / 2, 2.0);
	discriminant = pow(half_b, 2.0) - a * c;


	t_vec3		var_hc;
	t_vec3		var_h;
	t_vec3		var_w;
	t_vec3		var_v;

	var_hc = vsub(cy->coord_top, cy->coord_bot);
	var_h = vunit(var_hc);
	var_w = vsub(r->orig, cy->coord_bot);
	var_v = r->dir;

	a = vlength2(var_v) - pow(vdot(var_v, var_h), 2.0);
	half_b = (vdot(var_v, var_w) - (vdot(var_v, var_h) * vdot(var_w, var_h)));
	c = vlength2(var_w) - pow(vdot(var_w, var_h), 2.0) - pow(cy->diameter / 2, 2.0);
	discriminant = pow(half_b, 2.0) - a * c;

	if (discriminant < 0) // 실근이 없는 경우. 광선과 원기둥은 부딪히지 않음.
		return (FALSE);

	root = (-half_b - sqrt(discriminant)) / a; // 작은 근
	if (root < rec->tmin || root > rec->tmax) // 작은 근이 거리 범위 안에 존재하는 값인지 검사.
	{
		root = (-half_b + sqrt(discriminant)) / a; // 큰 근
		if (root < rec->tmin || root > rec->tmax)  // 큰 근이 거리 범위 안에 존재하는 값인지 검사.
			return (FALSE); // 작은 근, 큰 근 모두 거리 범위 안에 존재하지 않다면 광선과 원기둥은 부딪히지 않음
	}
	
	// 광선의 방향 벡터와 원기둥 교점 방향 벡터를 내적하여 값이 0이라면 광선과 원기둥은 평행한 상태이다.
	// 평행한 상태라면 원기둥의 윗면과 아랫면 모두 보이지 않는 장면을 의미한다.
	// 교점이 발견되고 원기둥이 무한대가 아닌 경우 원기둥 축의 교차 투영은 윗면/아랫면 지점 사이에 교점이 존재해야한다.
	// 따라서 교점이 원기둥의 높이 범위 안에 있는 지점이어야한다.
	
	// if (vdot(vsub(ray_at(r, root), cy->coord_top), cy->dir) > 0)
	if (vdot(vsub(ray_at(r, root), cy->coord_bot), cy->dir) > cy->height)
		return (FALSE);
	if (vdot(vsub(ray_at(r, root), cy->coord_bot), cy->dir) < 0)
		return (FALSE);
	
	// t_hit_record 구조체에 실근과 교점 좌표 및 교점에서의 법선벡터를 저장한다.
	// set_face_normal 함수를 통해 앞면/뒷면 판단.
	// RGB 벡터 albedo에 0 ~ 1 범위의 원기둥 오브젝트의 RGB 색상 값 대입
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	// rec->normal = vunit(vsub(rec->p, vsum(vmul_t(vdot(cy->dir, vsub(rec->p, cy->coord)), cy->dir), cy->coord)));
	//rec->normal = vunit(vsub(vsub(rec->p, cy->coord), vmul_t(vdot(cy->dir, vsub(rec->p, cy->coord)), cy->dir)));
	rec->normal = get_cy_normal(cy, rec);
	set_face_normal(r, rec); // 교점 법선 벡터와 광선의 방향 벡터는 항상 반대방향이어야한다.
	return (TRUE);
*/
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
	
	a = vlength2(v) - pow(vdot(v, h), 2);
	b = 2 * (vdot(v, w) - (vdot(v, h) * vdot(w, h)));
	c = vlength2(w) - pow(vdot(w, h), 2) -  pow(cy->diameter / 2, 2);
	
	discriminant = pow(b, 2) - (4 * a * c);	
	if (discriminant < 0)
		return (FALSE);
	root = (-b - sqrt(discriminant)) / (2 * a);
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-b + sqrt(discriminant)) / (2 * a);
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
	rec->normal = vunit(vsub(vsub(rec->p, cy->coord), vmul_t(vdot(cy->dir, vsub(rec->p, cy->coord)), cy->dir)));
	rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
	set_face_normal(r, rec);
	return (TRUE);
}

t_bool		hit_cylinder_circle(t_cylinder *cy, t_ray *r, t_hit_record *rec, t_point3 circle_center)
{
	double	denom; // Denominator : 분모. 판별식의 분모
	double	numer; // Numerator : 분자. 판별식의 분자
	double	t; // 평면 방정식 결과 값
	
	denom = vdot(r->dir, cy->dir); // 광선 단위 벡터와 평면의 방향 벡터 내적 연산
	if (denom == 0)
		return (FALSE);
	numer = vdot(vsub(circle_center, r->orig), cy->dir);
	t = numer / denom;
	if (vlength(vsub(ray_at(r, t), circle_center)) <= cy->diameter / 2.0)
	{
		if (t > rec->tmin && t < rec->tmax)
		{
			if (t < rec->t)
			{	
				rec->t = t;
				rec->p = ray_at(r, t);
				rec->normal = cy->dir; // 교점의 법선 벡터 : 평면의 방향 벡터의 역벡터
				// rec->normal = vmul_t(-1, cy->dir); // 교점의 법선 벡터 : 평면의 방향 벡터의 역벡터
				rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
				set_face_normal(r, rec);
			}
			return (TRUE);
		}
	}
	return (FALSE);
}