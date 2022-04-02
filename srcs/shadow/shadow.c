/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:22:52 by bahn              #+#    #+#             */
/*   Updated: 2022/04/02 21:23:14 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	in_shadow(t_object *objects, t_ray ray, double light_length)
{
	t_hit_record rec;
	
	rec.tmin = 0;
	rec.tmax = light_length;
	if (hit(objects, &ray, &rec))
		return (TRUE);
	else
		return (FALSE);
}
