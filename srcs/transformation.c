/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:51:21 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 10:55:00 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

void	apply_zoom(t_coor *coor, float zoom)
{
	if (zoom < 0)
		return ;
	coor->x *= zoom;
	coor->y *= zoom;
	// see if including z affects anything
	coor->z *= zoom;
}

void  apply_translate(t_coor *coor, t_trans trans)
{
	coor->x += trans.x;
	coor->y += trans.y;
}

void	apply_center(t_coor *coor)
{
	coor->x = coor->x + RESO_X / 2;
	coor->y = (RESO_Y / 2) - coor->y;
}

void  apply_transformation(t_grid *grid, t_tform *tform)
{
	int i;
	int j;

	i = 0;
	while (i < grid->row)
	{
		j = 0;
		while (j < grid->col)
		{
			apply_rotate(&grid->tmp_grid[i][j], 'x', tform->rot.x);
			apply_rotate(&grid->tmp_grid[i][j], 'y', tform->rot.y);
			apply_rotate(&grid->tmp_grid[i][j], 'z', tform->rot.z);
			if (tform->perspective == ISOMETRIC)
			{
				apply_iso(&grid->tmp_grid[i][j]);
				apply_zoom(&grid->tmp_grid[i][j], tform->zoom);
			}
			else if (tform->perspective == PERSPECTIVE)
			{
				apply_zoom(&grid->tmp_grid[i][j], tform->zoom);
				apply_perspective(&grid->tmp_grid[i][j]);
			}
			apply_translate(&grid->tmp_grid[i][j], tform->trans);
			apply_center(&grid->tmp_grid[i][j]);
			j++;
		}
		i++;
	}
}
