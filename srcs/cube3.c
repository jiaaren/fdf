/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:50:43 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 13:37:33 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

// anyway to make this a constant?


// 2. created 3d struct

// Translate function TODO

// Rotate function


void clean_image(int rows, int cols, t_img *img)
{
	int i = 0;
	int j;

	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			my_mlx_pixel_put(img, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}

void  copy_grid(t_grid *grid)
{
	int i = 0;
	int j = 0;

	while (i < grid->row)
	{
		j = 0;
		while (j < grid->col)
		{
			grid->tmp_grid[i][j].x = grid->grid[i][j].x;
			grid->tmp_grid[i][j].y = grid->grid[i][j].y;
			grid->tmp_grid[i][j].z = grid->grid[i][j].z;
			j++;
		}
		i++;
	}
}

void	print_grid_points(t_grid *grid, t_img *img, int color)
{
	int i = 0;
	int j = 0;

	while (i < grid->row)
	{
		j = 0;
		while (j < grid->col)
		{
			my_mlx_pixel_put(img, grid->tmp_grid[i][j].x, grid->tmp_grid[i][j].y, color);
			my_mlx_pixel_put(img, grid->tmp_grid[i][j].x + 1, grid->tmp_grid[i][j].y, color);
			my_mlx_pixel_put(img, grid->tmp_grid[i][j].x, grid->tmp_grid[i][j].y + 1, color);
			my_mlx_pixel_put(img, grid->tmp_grid[i][j].x + 1, grid->tmp_grid[i][j].y + 1, color);
			j++;
		}
		i++;
	}
}

void	print_grid_line(t_grid *grid, t_img *img, int color)
{
	int i;
	int j;
	t_coor **g;

	g = grid->tmp_grid; 
	i = 0;
	while (i < grid->row)
	{
		j = 0;
		while (j < grid->col)
		{
			if (i != (grid->row - 1))
				make_line(g[i][j].x, g[i][j].y, g[i + 1][j].x, g[i + 1][j].y, color, img);
			if (j != (grid->col - 1))
				make_line(g[i][j].x, g[i][j].y, g[i][j + 1].x, g[i][j + 1].y, color, img);
			j++;
		}
		i++;
	}
}

void output_grid(t_data *data)
{
	clean_image(RESO_Y, RESO_X, &data->img);
	copy_grid(&data->grid);
	apply_transformation(&data->grid, &data->tform);
	// print_grid_points(&data->grid, &data->img, 0x00FF99FF);
	print_grid_line(&data->grid, &data->img, 0x00FF99FF);
	mlx_put_image_to_window(data->win.mlx, data->win.window, data->img.img, 0, 0);
}

int	switch_projection(int *projection)
{
	if (*projection == ISOMETRIC)
		*projection = PERSPECTIVE;
	else
		*projection = ISOMETRIC;
}

int key_hook(int keycode, t_data *data)
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
	else if (keycode == 'h')
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
		switch_projection(&data->tform.perspective);
	else if (keycode == 't')
	{
		data->tform.rot.x += -5;
		data->tform.rot.y += 5;
		data->tform.rot.z += -10;	
	}
	output_grid(data);
}

void	initialise_window(t_data *data)
{
	data->win.mlx = mlx_init();
	data->win.window = mlx_new_window(data->win.mlx, RESO_X, RESO_Y, "Hello");
	data->img.img = mlx_new_image(data->win.mlx, RESO_X, RESO_Y);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_len, &data->img.endian);	
	// assign height and width
	data->win.reso_w = RESO_X;
	data->win.reso_h = RESO_Y;
	data->img.reso_w = RESO_X;
	data->img.reso_h = RESO_Y;
}

// need to populate height, i.e. 'z'
void	populate_grid(t_grid *grid, int start_x, int start_y)
{
	int	i;
	int j;

	i = 0;
	while (i < grid->row)
	{
		j = 0;
		while (j < grid->col)
		{
			grid->grid[i][j].x = start_x + (j * grid->box_len);
			grid->grid[i][j].y = start_y - (i * grid->box_len);
			// z needs to be updated
			// need to figure out length between each x & y
			// figure out how to center
			grid->grid[i][j].z = 1;
			j++;
		}
		i++;
	}
}

void	make_grid_tmp(t_grid *grid)
{
	int start_x;
	int start_y;

	// these 3 variables need to be fed from process inputs
	grid->box_len = 40;
	grid->row = 10;
	grid->col = 20;

	start_x = -(grid->box_len * (grid->col - 1) / 2);
	start_y = (grid->box_len * (grid->row - 1) / 2);
	grid->grid = alloc_grid(grid->row, grid->col);
	populate_grid(grid, start_x, start_y);
	grid->grid[5][5].z = -100;
	grid->grid[4][5].z = -100;
	grid->grid[3][5].z = -100;
	grid->grid[2][5].z = -100;
	grid->grid[1][5].z = -100;
	grid->grid[5][6].z = -75;
	grid->grid[4][6].z = -75;
	grid->grid[3][6].z = -75;
	grid->grid[2][6].z = -75;
	grid->grid[1][6].z = -75;
	grid->grid[5][4].z = -75;
	grid->grid[4][4].z = -75;
	grid->grid[3][4].z = -75;
	grid->grid[2][4].z = -75;
	grid->grid[1][4].z = -75;
}

void	initialise_grid(t_data *data)
{
	make_grid_tmp(&data->grid);
	data->grid.tmp_grid = alloc_grid(data->grid.row, data->grid.col);
	// need another coordinate to return grid size (can combine along with grid for make_grid afterwards)
	// for grid also include update of grid width and height

	// TESTING
	// for (int i = 0; i < data->grid.row; i++)
	// {
	// 	for (int j = 0; j < data->grid.col; j++)
	// 		printf("(%4i,%4i) ", data->grid.grid[i][j].x, data->grid.grid[i][j].y);
	// 	printf("\n");	
	// }
}

void	initialise_transform(t_data *data)
{
	// rotation
	data->tform.rot.x = 0;
	data->tform.rot.y = 0;
	data->tform.rot.z = 0;
	// zoom
	data->tform.zoom = 1.0;
	//translation
	data->tform.trans.x = 0;
	data->tform.trans.y = 0;
	// perspective
	data->tform.perspective = ISOMETRIC;
}

int main(void)
{
	t_data data;

	// initialise window
	initialise_window(&data);
	// assign cube
	initialise_grid(&data);
	// apply changes - create temp cube & setup
	initialise_transform(&data);
	// output grid
	output_grid(&data);
	// key hook
	mlx_key_hook(data.win.window, key_hook, &data);
		// // TO DEL
		// // mlx_put_image_to_window(data.win.mlx, data.win.window, data.img.img, 0, 0);
	mlx_loop(data.win.mlx);
	return (0);
}