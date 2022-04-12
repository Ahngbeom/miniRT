/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:46:31 by bahn              #+#    #+#             */
/*   Updated: 2022/04/12 22:29:37 by bahn             ###   ########.fr       */
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

t_bool		hit_cylinder_rectangle(t_cylinder *cy, t_ray *r, t_hit_record *rec, t_color3 color)
{
	t_vec3		oc;
	
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		root;
	
	// 원기둥의 어느 한 지점에서 원기둥의 높이 / 2 만큼 더해주거나 빼주어 원기둥의 윗면/아랫면의 좌표를 구한다.
	cy->coord_top = vsum(cy->coord, vmul_t(cy->height / 2, cy->dir));
	cy->coord_bot = vsub(cy->coord, vmul_t(cy->height / 2, cy->dir));

	oc = vsub(r->orig, cy->coord); // 카메라 원점에서 원기둥의 어느 한 지점까지의 방향 벡터
	
	a = vlength2(vcross(r->dir, cy->dir));
	half_b = vdot(vcross(r->dir, cy->dir), vcross(oc, cy->dir));
	c = vlength2(vcross(oc, cy->dir)) - pow(cy->diameter / 2, 2.0);
	discriminant = pow(half_b, 2.0) - a * c;
	
	if (discriminant < EPSILON) // 실근이 없는 경우. 광선과 원기둥은 부딪히지 않음.
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
	// 윗면에 대해서 내적 결과 값이 0보다 크다면 광선은 옆면보다 윗면을 먼저 부딪히는 경우를 의미한다.
	// 아랫면에 대해서 내적 결과 값이 0보다 작다면 광선은 옆면보다 아랫면을 먼저 부딪히는 경우를 의미한다.
	//
	// 사실 잘 모르겠다... 벡터 연산 개념을 완전히 이해하고 원기둥 방정식까지 이해를 해야 알 수 있을 것 같다.
	if (vdot(cy->dir, vsub(ray_at(r, root), cy->coord_top)) > 0) // 광선이 윗면과 부딪혔을 경우
		return (FALSE);
	if (vdot(cy->dir, vsub(ray_at(r, root), cy->coord_bot)) < 0) // 광선이 아랫면과 부딪혔을 경우
		return (FALSE);
	
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	// rec->normal = vdiv(vsub(rec->p, vsum(cy->coord, cy->dir)), cy->diameter / 2);
	rec->normal = vunit(vsub(rec->p, vsum(vmul_t(vdot(cy->dir, vsub(rec->p, cy->coord)), cy->dir), cy->coord)));
	// set_face_normal(r, rec);
	// rec->p = vsum(rec->p, vmul_t(EPSILON, rec->normal));
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

	// printf("oc top : %f, %f, %f\n", oc_top.x, oc_top.y, oc_top.z);
	// printf("t top : %f\n", t_top);
	// printf("oc bot : %f, %f, %f\n", oc_bot.x, oc_bot.y, oc_bot.z);
	// printf("t bot : %f\n", t_bot);

	if (t_top < rec->tmin || t_top > rec->tmax)
		t_top = INFINITY;
	if (t_bot < rec->tmin || t_bot > rec->tmax)
		t_bot = INFINITY;
		
	if (t_top == INFINITY && t_bot == INFINITY)
		return (FALSE);

	if (t_top < t_bot && t_top < rec->t)
	{
		// printf("Top HIT\n");
		rec->t = t_top;
		rec->p = vsum(r->orig, vmul_t(rec->t, r->dir));
		rec->normal = vunit(vsub(rec->p, vsum(vmul_t(vdot(cy->dir, vsub(rec->p, cy->coord)), cy->dir), cy->coord)));
	}
	else if (t_bot < t_top && t_bot < rec->t)
	{
		// printf("Bottom HIT\n");
		rec->t = t_bot;
		rec->p = vsum(r->orig, vmul_t(rec->t, r->dir));
		rec->normal = cy->dir;
	}
	
	rec->albedo = vmul_t(1.0 / 255.0, color);
	
	// printf("rec->t: %f\n", rec->t);
	// printf("rec->p: %f, %f, %f\n", rec->p.x, rec->p.y, rec->p.z);
	// printf("rec->normal: %f, %f, %f\n", rec->normal.x, rec->normal.y, rec->normal.z);

	
	return (TRUE);
}
