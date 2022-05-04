/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:35:26 by jseol             #+#    #+#             */
/*   Updated: 2022/05/04 16:35:46 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
