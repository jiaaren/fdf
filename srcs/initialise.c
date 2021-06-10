/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:22:20 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 22:07:07 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

void	initialise_window(t_data *data, char *title)
{
	data->win.mlx = mlx_init();
	data->win.window = mlx_new_window(data->win.mlx, RESO_X, RESO_Y, title);
	data->img.img = mlx_new_image(data->win.mlx, RESO_X, RESO_Y);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);
	data->win.reso_w = RESO_X;
	data->win.reso_h = RESO_Y;
	data->img.reso_w = RESO_X;
	data->img.reso_h = RESO_Y;
}

int	initialise_grid(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("File error.\n", 2);
		return (-1);
	}
	if (read_file(fd, &data->grid) == -1)
	{
		ft_putstr_fd("Map error.\n", 2);
		return (-1);
	}
	return (0);
}

void	initialise_transform(t_data *data)
{
	data->tform.rot.x = DEFAULT_X_ROT;
	data->tform.rot.y = DEFAULT_Y_ROT;
	data->tform.rot.z = DEFAULT_Z_ROT;
	data->tform.zoom = DEFAULT_ZOOM;
	data->tform.trans.x = 0;
	data->tform.trans.y = 0;
	data->tform.projection = ISOMETRIC;
	data->tform.z0_const
		= (RESO_X / 2.0) / tan((FIELD_OF_VIEW / 2.0) * (M_PI / 180.0));
	data->tform.iso_radian_const
		= (ISO_DEGREE / 180.0) * M_PI;
}
