/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:35:26 by jseol             #+#    #+#             */
/*   Updated: 2022/05/05 12:04:38 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vunit(t_vec3 v)
{
	double	len;

	len = vlength(v);
	v.x /= len;
	v.y /= len;
	v.z /= len;
	return (v);
}

t_vec3	vmin(t_vec3 u, t_vec3 v)
{
	if (u.x > v.x)
		u.x = v.x;
	if (u.y > v.y)
		u.y = v.y;
	if (u.z > v.z)
		u.z = v.z;
	return (u);
}
