/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_esc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:16:59 by bahn              #+#    #+#             */
/*   Updated: 2022/03/28 18:44:18 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	minirt_esc(int keycode, t_minirt *miniRT)
{
	// printf("Keycode : %d\n", keycode);
	if (keycode == 53 || keycode == 65307)
	{
		minirt_close(0, miniRT);
	}
	return (0);
}