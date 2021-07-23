/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:53:11 by jkhong            #+#    #+#             */
/*   Updated: 2021/07/23 14:06:02 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

/*
	grid->tmp is passed in to convert x and y coordinates to 3D
	- apply_perspective requires Z0 constant
	- apply_iso (isometric) reads iso_rad_const, ultimately derived from libfdf.h
		- default degree const = radian of (30 degrees)
*/
void	apply_perspective(t_coor *coor, double Z0)
{
	coor->x = (coor->x * Z0) / (Z0 + coor->z);
	coor->y = (coor->y * Z0) / (Z0 + coor->z);
}

void	apply_iso(t_coor *coor, float iso_rad_const)
{
	t_coor	tmp;

	tmp.x = coor->x;
	tmp.y = coor->y;
	coor->x = (tmp.x - tmp.y) * cos(iso_rad_const);
	coor->y = -(coor->z) + (tmp.x + tmp.y) * sin(iso_rad_const);
	coor->z = coor->z;
}

// swaps projection variable in tform->projection between ISOMETRIC and PERSPECTIVE
void	switch_projection(int *projection)
{
	if (*projection == ISOMETRIC)
		*projection = PERSPECTIVE;
	else
		*projection = ISOMETRIC;
}
