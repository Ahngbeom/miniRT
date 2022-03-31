/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:34:04 by bahn              #+#    #+#             */
/*   Updated: 2022/03/31 15:01:28 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*sphere_init(t_point3 center, double radius)
{
	t_sphere	*sp;
	
	sp = ft_calloc(sizeof(t_sphere), 1);
	if (sp == NULL)
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	// sp->hit_func = hit_sphere;
	return (sp);
}

t_bool		hit_sphere(t_object *world, t_ray *r, t_hit_record *rec) // 짝수 근의 공식 전환 및 교점 정보 별도 저장
{
	t_sphere	*sp;
	t_vec3		oc; // 방향 벡터로 나타낸 구의 중심
	double		a; // a 계수
	double		half_b; // b 계수
	double		c; // c 계수
	double		discriminant; // 판별식
	double		sqrtd; // 판별식에서 제곱근 식의 결과 값 저장
	double		root; // 근의 공식 결과 값 저장. 두 근

	sp = world->element;
	oc = vsub(r->orig, sp->center); // 카메라에서 시작된 광선 시작점 - 구의 중심 = 구의 중심 방향 벡터
	a = vlength2(r->dir); 			// a = D * D
	half_b = vdot(oc, r->dir); 		// b / 2 = D * (O - C)
	c = vlength2(oc) - sp->radius2; // c = (O - C) * (O - C) - r^2
	discriminant = pow(half_b, 2.0) - (a * c); // discriminant = b^2 - a * c
	
	if (discriminant < 0) // 실근이 없는 경우
		return (FALSE);

	sqrtd = sqrt(discriminant); // 제곱근 적용
	root = (-half_b - sqrtd) / a; // 근의 공식에서 작은 근 계산.
	if (root < rec->tmin || root > rec->tmax) // 작은 근이 tmin, tmax 범위 안에 존재하지않는 값인지 검사
	{
		root = (-half_b + sqrtd) / a; // 근의 공식에서 큰 근 계산.
		if (root < rec->tmin || root > rec->tmax) // 큰 근이 tmin, tmax 범위 안에 존재하지않는 값인지 검사
			return (FALSE); // 광선이 구에 부딪히지 않음
	}
	rec->t = root; // t에 짝수 근의 공식의 작은 근 대입
	rec->p = ray_at(r, rec->t); // 광선과 구의 교점 벡터
	rec->normal = vdiv(vsub(rec->p, sp->center), sp->radius); // 법선 벡터 정규화
	set_face_normal(r, rec); // hit record 법선 벡터와 광선의 법선 벡터를 비교하여 앞면/뒷면 판단
	rec->albedo = world->albedo;
	return (TRUE);
}

// double		hit_sphere(t_sphere *sphere, t_ray *r) // 구와 광선 Hit 여부 검사
// {
// 	t_vec3	oc; // 방향 벡터로 나타낸 구의 중심
// 	double	a; // a 계수
// 	double	b; // b 계수
// 	double	c; // c 계수
// 	double	discriminant; // 판별식

// 	oc = vsub(r->orig, sphere->center); // 카메라에서 시작된 광선 시작점 - 구의 중심 = 구의 중심 방향 벡터
// 	a = vdot(r->dir, r->dir); 			// a = D * D
// 	b = 2.0 * vdot(oc, r->dir); 		// b = 2 * D * (O - C)
// 	c = vdot(oc, oc) - sphere->radius2; // c = (O - C) * (O - C) - r^2
// 	discriminant = pow(b, 2.0) - (4 * a * c); // discriminant = b^2 - 4 * a * c
// 	if (discriminant < 0) // 실근이 없는 경우
// 		return (-1.0); // 음수 : 광선이 구와 부딪히지않음
// 	else
// 		// return (discriminant > 0); // 음수 : 광선이 구와 부딪히지않음, 0 또는 양수 : 광선이 구에 부딪힘
// 		return ((-b - sqrt(discriminant)) / (2.0 * a)); // 근의 공식을 이용하여 t 값 연산. 두 근 중 작은 근 반환
// }