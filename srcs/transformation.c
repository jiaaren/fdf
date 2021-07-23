/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:51:21 by jkhong            #+#    #+#             */
/*   Updated: 2021/07/23 14:19:12 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

// Magnifies coordinates by appling Zoom scale
void	apply_zoom(t_coor *coor, float zoom)
{
	if (zoom < 0)
		return ;
	coor->x *= zoom;
	coor->y *= zoom;
	coor->z *= zoom;
}

// Moves coordinates by according to x, y distance displaced
void	apply_translate(t_coor *coor, t_trans trans)
{
	coor->x += trans.x;
	coor->y += trans.y;
}

/*
	Converts coordinates from
	- 4 segment coordinate map (0, 0 in center)
	- to display coordinates (0, 0 in top left)
*/
void	apply_center(t_coor *coor)
{
	coor->x = coor->x + RESO_X / 2;
	coor->y = (RESO_Y / 2) - coor->y;
}

/*
	Loop through every single point in replicated tmp_grid, and:
	- apply_rotate: 3 times, for x, y and z
	- apply_projection: isometric/perspective
	- apply_zoom
	- apply_translate
	- apply_center

	Ordering is important
*/
void	apply_transformation(t_grid *grid, t_tform *tform)
{
	int	i;
	int	j;

	i = -1;
	while (++i < grid->row)
	{
		j = -1;
		while (++j < grid->col)
		{
			apply_rotate(&grid->tmp_grid[i][j], 'x', tform->rot.x);
			apply_rotate(&grid->tmp_grid[i][j], 'y', tform->rot.y);
			apply_rotate(&grid->tmp_grid[i][j], 'z', tform->rot.z);
			if (tform->projection == ISOMETRIC)
				apply_zoom(&grid->tmp_grid[i][j], tform->zoom);
			if (tform->projection == ISOMETRIC)
				apply_iso(&grid->tmp_grid[i][j], tform->iso_radian_const);
			else if (tform->projection == PERSPECTIVE)
				apply_perspective(&grid->tmp_grid[i][j], tform->z0_const);
			if (tform->projection == PERSPECTIVE)
				apply_zoom(&grid->tmp_grid[i][j], tform->zoom);
			apply_translate(&grid->tmp_grid[i][j], tform->trans);
			apply_center(&grid->tmp_grid[i][j]);
		}
	}
}
