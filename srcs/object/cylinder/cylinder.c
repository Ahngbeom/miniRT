/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:46:31 by bahn              #+#    #+#             */
/*   Updated: 2022/04/15 01:00:54 by bahn             ###   ########.fr       */
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

t_bool		hit_cylinder_surface(t_cylinder *cy, t_ray *r, t_hit_record *rec, t_color3 color)
{
	t_vec3		oc;
	
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		root;
	
	// 원기둥의 중심점에서 원기둥의 방향에 맞게 원기둥의 높이/2 만큼 더해주거나 빼주어 원기둥의 윗면/아랫면의 좌표를 구한다.
	cy->coord_top = vsum(cy->coord, vmul_t(cy->height / 2, cy->dir));
	cy->coord_bot = vsub(cy->coord, vmul_t(cy->height / 2, cy->dir));

	oc = vsub(r->orig, cy->coord); // 카메라 원점에서 원기둥의 중심점까지의 방향 벡터
	
	a = vlength2(r->dir) - pow(vdot(r->dir, cy->dir), 2.0);
	half_b = vdot(r->dir, oc) - (vdot(r->dir, cy->dir) * vdot(oc, cy->dir));
	c = vlength2(oc) - pow(vdot(oc, cy->dir), 2.0) - pow(cy->diameter / 2, 2.0);
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
	rec->normal = vunit(vsub(vsub(rec->p, cy->coord), vmul_t(vdot(cy->dir, vsub(rec->p, cy->coord)), cy->dir)));
	set_face_normal(r, rec);
	rec->albedo = vmul_t(1.0 / 255.0, color);

	// printf("rec->t: %f\n", rec->t);
	// printf("rec->p: %f, %f, %f\n", rec->p.x, rec->p.y, rec->p.z);
	// printf("rec->normal: %f, %f, %f\n", rec->normal.x, rec->normal.y, rec->normal.z);
	return (TRUE);
}

t_bool		hit_cylinder_circle(t_cylinder *cy, t_ray *r, t_hit_record *rec, t_color3 color)
{
	t_vec3	oc_top;
	t_vec3	oc_bot;
	double	denom;
	double	t_top;
	double	t_bot;

	denom = vdot(r->dir, cy->dir);
	if (denom == 0)
		return (FALSE);
	
	oc_top = vsub(cy->coord_top, r->orig);
	t_top = vdot(oc_top, cy->dir) / denom;
	
	if (vlength2(vsub(vsum(r->orig, vmul_t(t_top, r->dir)), cy->coord_top)) > pow(cy->diameter / 2, 2.0))
		t_top = INFINITY;
		
	oc_bot = vsub(cy->coord_bot, r->orig);
	t_bot = vdot(oc_bot, cy->dir) / denom;
	
	if (vlength2(vsub(vsum(r->orig, vmul_t(t_bot, r->dir)), cy->coord_bot)) > pow(cy->diameter / 2, 2.0))
		t_bot = INFINITY;

	if (t_top < rec->tmin || t_top > rec->tmax)
		t_top = INFINITY;
	if (t_bot < rec->tmin || t_bot > rec->tmax)
		t_bot = INFINITY;
		
	if (t_top == INFINITY && t_bot == INFINITY)
		return (FALSE);

	if (t_top < t_bot && t_top < rec->t)
		rec->t = t_top;
	else if (t_bot < t_top && t_bot < rec->t)
		rec->t = t_bot;
	else
		return (TRUE);
	rec->p = vsum(r->orig, vmul_t(rec->t, r->dir));
	rec->normal = cy->dir;
	set_face_normal(r, rec);
	rec->albedo = vmul_t(1.0 / 255.0, color);
	return (TRUE);
}
