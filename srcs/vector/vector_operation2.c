/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:33:37 by jseol             #+#    #+#             */
/*   Updated: 2022/05/04 16:36:41 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vmul(t_vec3 u, t_vec3 v) // 벡터 * 벡터 함수
{
	t_vec3	vec;

	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	vec.z = u.z * v.z;
	return (vec);
}

t_vec3	vmul_t(double t, t_vec3 v) // 스칼라 * 벡터 함수
{
	t_vec3	vec;

	vec.x = v.x * t;
	vec.y = v.y * t;
	vec.z = v.z * t;
	return (vec);
}

t_vec3	vdiv(t_vec3 v, double t) // 벡터 나눗셈 함수
{
	return (vmul_t(1 / t, v));
}

double	vdot(t_vec3 u, t_vec3 v) // 벡터 내적 연산
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	vcross(t_vec3 u, t_vec3 v) // 벡터 외적 연산
{
	return (vector_init(u.y * v.z - u.z * v.y, \
						u.z * v.x - u.x * v.z, \
							u.x * v.y - u.y * v.x));
}
