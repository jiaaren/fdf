/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:53:11 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 17:52:03 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

void	apply_perspective(t_coor *coor, double Z0)
{
	coor->x = (coor->x * Z0) / (Z0 + coor->z);
	coor->y = (coor->y * Z0) / (Z0 + coor->z);
}

void	apply_iso(t_coor *coor)
{
	t_coor	tmp;

	tmp.x = coor->x;
	tmp.y = coor->y;
	coor->x = (tmp.x - tmp.y) * cos(0.523599);
	coor->y = -(coor->z) + (tmp.x + tmp.y) * sin(0.523599);
	coor->z = coor->z;
}

int	switch_projection(int *projection)
{
	if (*projection == ISOMETRIC)
		*projection = PERSPECTIVE;
	else
		*projection = ISOMETRIC;
}
