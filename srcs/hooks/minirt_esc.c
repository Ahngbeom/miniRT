/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_esc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:16:59 by bahn              #+#    #+#             */
/*   Updated: 2022/03/31 16:00:39 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	minirt_esc(int keycode, t_scene *scene)
{
	// printf("Keycode : %d\n", keycode);
	if (keycode == 53 || keycode == 65307)
	{
		minirt_close(0, scene);
	}
	return (0);
}