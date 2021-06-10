/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:50:43 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 21:13:58 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

void	exit_hook(t_data *data)
{
	free_grid(data->grid.grid, data->grid.row);
	free_grid(data->grid.tmp_grid, data->grid.row);
	mlx_destroy_image(data->win.mlx, data->img.img);
	mlx_destroy_window(data->win.mlx, data->win.window);
	mlx_destroy_display(data->win.mlx);
	free(data->win.mlx);
	exit(0);
}

void	key_hook2(int keycode, t_data *data)
{
	if (keycode == 'h')
		data->tform.zoom += 0.1;
	else if (keycode == 'u')
		data->tform.zoom -= 0.1;
	else if (keycode == 'w')
		data->tform.trans.y += 10;
	else if (keycode == 's')
		data->tform.trans.y -= 10;
	else if (keycode == 'a')
		data->tform.trans.x -= 10;
	else if (keycode == 'd')
		data->tform.trans.x += 10;
	else if (keycode == 'q')
		switch_projection(&data->tform.projection);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 'j')
		data->tform.rot.x += 5;
	else if (keycode == 'i')
		data->tform.rot.x += -5;
	else if (keycode == 'k')
		data->tform.rot.y += 5;
	else if (keycode == 'o')
		data->tform.rot.y += -5;
	else if (keycode == 'l')
		data->tform.rot.z += 5;
	else if (keycode == 'p')
		data->tform.rot.z += -5;
	if (keycode == 65307)
		exit_hook(data);
	key_hook2(keycode, data);
	if (data->tform.zoom > 0.0)
		output_grid(data);
	else
		output_blank(data);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("File name missing.\n", 2);
		return (1);
	}
	if (initialise_grid(&data, argv[1]) == -1)
		return (2);
	initialise_window(&data, argv[1]);
	initialise_transform(&data);
	output_grid(&data);
	mlx_key_hook(data.win.window, key_hook, &data);
	mlx_loop(data.win.mlx);
	return (0);
}
