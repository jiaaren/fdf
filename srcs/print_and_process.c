/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:28:12 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 17:41:47 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

void	clean_image(int rows, int cols, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->reso_h)
	{
		j = 0;
		while (j < img->reso_w)
		{
			my_mlx_pixel_put(img, j, i, 0x00000000);
			j++;
		}
		i++;
	}
}

void	print_grid_points(t_grid *grid, t_img *img, int color)
{
	int	i;
	int	j;
	int	tmp_x;
	int	tmp_y;

	i = 0;
	while (i < grid->row)
	{
		j = 0;
		while (j < grid->col)
		{
			tmp_x = grid->tmp_grid[i][j].x;
			tmp_y = grid->tmp_grid[i][j].y;
			my_mlx_pixel_put(img, tmp_x, tmp_y, color);
			my_mlx_pixel_put(img, tmp_x + 1, tmp_y, color);
			my_mlx_pixel_put(img, tmp_x, tmp_y + 1, color);
			my_mlx_pixel_put(img, tmp_x + 1, tmp_y + 1, color);
			j++;
		}
		i++;
	}
}

void	print_grid_line(t_grid *grid, t_img *img, int color)
{
	int		i;
	int		j;
	t_coor	**g;

	g = grid->tmp_grid;
	i = 0;
	while (i < grid->row)
	{
		j = 0;
		while (j < grid->col)
		{
			if (i != (grid->row - 1))
				make_line(g[i][j], g[i + 1][j], color, img);
			if (j != (grid->col - 1))
				make_line(g[i][j], g[i][j + 1], color, img);
			j++;
		}
		i++;
	}
}

void	output_blank(t_data *data)
{
	clean_image(RESO_Y, RESO_X, &data->img);
	mlx_put_image_to_window(data->win.mlx,
		data->win.window, data->img.img, 0, 0);
}

void	output_grid(t_data *data)
{
	clean_image(RESO_Y, RESO_X, &data->img);
	copy_grid(&data->grid);
	apply_transformation(&data->grid, &data->tform);
	print_grid_line(&data->grid, &data->img, HEX_COLOR);
	mlx_put_image_to_window(data->win.mlx,
		data->win.window, data->img.img, 0, 0);
}
