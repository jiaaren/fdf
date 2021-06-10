/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:22:20 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 17:58:06 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

void	initialise_window(t_data *data)
{
	data->win.mlx = mlx_init();
	data->win.window = mlx_new_window(data->win.mlx, RESO_X, RESO_Y, "Hello");
	data->img.img = mlx_new_image(data->win.mlx, RESO_X, RESO_Y);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
	data->win.reso_w = RESO_X;
	data->win.reso_h = RESO_Y;
	data->img.reso_w = RESO_X;
	data->img.reso_h = RESO_Y;
}

void	initialise_grid(t_data *data, char *filename)
{
	read_file(filename, &data->grid);
}

void	initialise_transform(t_data *data)
{
	data->tform.rot.x = -5;
	data->tform.rot.y = -5;
	data->tform.rot.z = -95;
	data->tform.zoom = 0.75;
	data->tform.trans.x = 0;
	data->tform.trans.y = 0;
	data->tform.projection = ISOMETRIC;
	data->tform.z0_const
		= (RESO_X / 2.0) / tan((FIELD_OF_VIEW / 2.0) * (M_PI / 180.0));
}
