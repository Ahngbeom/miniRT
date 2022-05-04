/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 02:39:46 by bahn              #+#    #+#             */
/*   Updated: 2022/05/04 16:35:07 by jseol            ###   ########.fr       */
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
