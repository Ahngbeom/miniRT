/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_esc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseol <jseol@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:16:59 by bahn              #+#    #+#             */
/*   Updated: 2022/05/04 17:38:52 by jseol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	minirt_esc(int keycode, t_scene *scene)
{
	if (keycode == 53 || keycode == 65307)
	{
		minirt_close(scene);
	}
	return (0);
}
