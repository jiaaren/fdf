/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 12:41:59 by jkhong            #+#    #+#             */
/*   Updated: 2021/07/23 14:02:03 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

// Handles x plane
void	make_line_x(t_coor a, t_coor b, int color, t_img *img)
{
	int			x;
	int			y;
	const int	dx = abs_int(b.x - a.x);
	const int	dy = abs_int(b.y - a.y);
	int			p;

	x = a.x;
	y = a.y;
	p = 2 * dy - dx;
	while (x <= b.x)
	{
		my_mlx_pixel_put(img, x, y, color);
		x++;
		if (p < 0)
			p += (2 * dy);
		else
		{
			p += (2 * dy) - (2 * dx);
			if (b.y - a.y > 0)
				y++;
			else
				y--;
		}
	}
}

// Handles y plane
void	make_line_y(t_coor a, t_coor b, int color, t_img *img)
{
	int			x;
	int			y;
	const int	dx = abs_int(b.x - a.x);
	const int	dy = abs_int(b.y - a.y);
	int			p;

	x = a.x;
	y = a.y;
	p = 2 * dx - dy;
	while (y <= b.y)
	{
		my_mlx_pixel_put(img, x, y, color);
		y++;
		if (p < 0)
			p += (2 * dx);
		else
		{
			p += (2 * dx) - (2 * dy);
			if (b.x - a.x > 0)
				x++;
			else
				x--;
		}
	}
}

// Bresenham's algorithm
void	make_line(t_coor a, t_coor b, int color, t_img *img)
{
	int		temp;
	float	grad;

	// condition to avoid division by zero, since gradient = y / x
	if (b.x - a.x == 0)
		grad = (b.y - a.y);
	else
		grad = (b.y - a.y) / (float)(b.x - a.x);
	// condition to swap coordinates
	if ((b.x < a.x && abs_float(grad) <= 1.0)
		|| (b.y < a.y && abs_float(grad) > 1.0))
	{
		temp = a.x;
		a.x = b.x;
		b.x = temp;
		temp = a.y;
		a.y = b.y;
		b.y = temp;
	}
	// condition to choose algorithm for X or Y plane
	if (grad >= -1 && grad <= 1)
		make_line_x(a, b, color, img);
	else
		make_line_y(a, b, color, img);
}
