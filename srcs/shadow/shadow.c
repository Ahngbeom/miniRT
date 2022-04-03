/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:22:52 by bahn              #+#    #+#             */
/*   Updated: 2022/04/03 18:58:08 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	shadow_checker(t_object *objects, t_light light, t_vec3 light_dir, t_hit_record rec)
{
	double			light_len;	// 교점에서 광원 원점까지의 거리
	t_ray			light_ray; 	// 교점에서부터 광원의 원점으로 향하는 방향 벡터
	t_hit_record	shadow_rec;	// 그림자에 대해서 처리하기 위한 t_hit_record

	light_len = vlength(vsub(light.orig, rec.p)); // 교점에서 광원 원점까지의 거리 계산
	light_ray = ray_init(vsum(rec.p, vmul_t(EPSILON, rec.normal)), light_dir); // ???
	shadow_rec.tmin = EPSILON;
	shadow_rec.tmax = light_len; // 광원 원점까지의 거리를 tmax 값에 대입
	if (hit(objects, &light_ray, &shadow_rec)) // 존재하는 각 오브젝트의 그림자 생성 여부 판단
		return (TRUE);
	else
		return (FALSE);
}
