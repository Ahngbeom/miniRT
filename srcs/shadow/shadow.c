/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:22:52 by bahn              #+#    #+#             */
/*   Updated: 2022/05/05 01:39:40 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	shadow_checker(t_object *objects, t_vec3 light_dir, t_hit_record rec)
{
	t_hit_record	shadow_rec;
	t_ray			light_ray;
	double			light_len;

	light_len = vlength(light_dir);
	light_ray = ray_init(vsum(rec.p, vmul_t(EPSILON, rec.normal)), light_dir);
	shadow_rec.tmin = EPSILON;
	shadow_rec.tmax = light_len;
	if (shading(objects, &light_ray, &shadow_rec) == TRUE)
		return (TRUE);
	else
		return (FALSE);
}

t_bool	shading(t_object *objects, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	tmp_rec;

	tmp_rec = *rec;
	hit_anything = FALSE;
	while (objects != NULL)
	{
		if (hit_object(objects, ray, &tmp_rec) == TRUE)
			hit_anything = TRUE;
		objects = objects->next;
	}
	return (hit_anything);
}
