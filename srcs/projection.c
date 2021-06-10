/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:53:11 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 10:58:44 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

double Z0 = (RESO_X / 2.0) / tan((FIELD_OF_VIEW / 2.0) * (M_PI / 180.0));

void	apply_perspective(t_coor *coor)
{
	coor->x = (coor->x * Z0) / (Z0 + coor->z);
	coor->y = (coor->y * Z0) / (Z0 + coor->z);
}

// need to figure out where this is from
void	apply_iso(t_coor *coor)
{
	t_coor tmp;

	tmp.x = coor->x;
	tmp.y = coor->y;
	coor->x = (tmp.x - tmp.y) * cos(0.523599);
	coor->y = -(coor->z) + (tmp.x + tmp.y) * sin(0.523599);
	coor->z = coor->z;
}
