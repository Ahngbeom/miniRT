/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:47:58 by bahn              #+#    #+#             */
/*   Updated: 2022/03/31 14:55:36 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		vector_init(double x, double y, double z) // 벡터 초기화 함수
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_point3	point_init(double x, double y, double z) // 포인트 벡터 초기화 함수
{
	t_point3	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_color3		color_init(double r, double g, double b) // 색상 벡터 초기화 함수
{
	t_color3	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}