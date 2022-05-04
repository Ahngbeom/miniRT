/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:39:46 by bahn              #+#    #+#             */
/*   Updated: 2022/04/28 15:58:03 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vset(t_vec3 *vec, double x, double y, double z) // 벡터 값 설정 함수
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

double	vlength(t_vec3 v) // 벡터의 크기/길이 추출 함수
{
	return (sqrt(vlength2(v)));
}

double	vlength2(t_vec3 v) // 벡터 크기/길이 제곱 추출 함수
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	vsum(t_vec3 u, t_vec3 v) // 벡터 합 함수
{
	t_vec3	vec;
	
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	vec.z = u.z + v.z;
	return (vec);
}

t_vec3	vsub(t_vec3 u, t_vec3 v) // 벡터 차 함수
{
	t_vec3	vec;
	
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	vec.z = u.z - v.z;
	return (vec);
}

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
	return vmul_t(1 / t, v);
}

double	vdot(t_vec3 u, t_vec3 v) // 벡터 내적 연산
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	vcross(t_vec3 u, t_vec3 v) // 벡터 외적 연산
{
	return vector_init(u.y * v.z - u.z * v.y, \
						u.z * v.x - u.x * v.z, \
							u.x * v.y - u.y * v.x);
}

t_vec3	vunit(t_vec3 v) // 단위 벡터 반환
{
	double	len;

	len = vlength(v);
	// if (len == 0)
	// {
	// 	printf("Error\n:Devider is 0");
	// 	minirt_close(0, NULL);
	// }
	v.x /= len;
	v.y /= len;
	v.z /= len;
	return (v);
	// return vdiv(v, sqrt(pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0)));
}

t_vec3	vmin(t_vec3 u, t_vec3 v) // 두 벡터 간의 작은 원소들만 반환
{
	if (u.x > v.x)
		u.x = v.x;
	if (u.y > v.y)
		u.y = v.y;
	if (u.z > v.z)
		u.z = v.z;
	return (u);
}