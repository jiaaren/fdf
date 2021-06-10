/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 12:41:59 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 10:48:40 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!(x >= 0 && x <= img->reso_w && y >= 0 && y <= img->reso_w))
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
/* 
	add colour variable as well
	By default, this would only work for gradients of 0 (i.e. straight line) to 1

*/
void	make_line_test(int x1, int y1, int x2, int y2, int color, t_img *img)
{
	int x;
	int y;
	const int dx = x2 - x1;
	const int dy = y2 - y1;
	int p;

	x = x1;
	y = y1;
	p = 2*dy - dx;
	while (x <= x2)
	{
		my_mlx_pixel_put(img, x, y, color);
		x++;
		if (p < 0)
			(p += 2 * dy);
		else
		{
			p += (2 * dy) - (2 * dx);
			y++;
		}
	}

}

/*
	Test for make_line_r
	make_line_r(250, 250, 300, 300, 0x00FF0000, &img); // test limit
	make_line_r(250, 250, 300, 301, 0x0000FF00, &img); 
	make_line_r(250, 250, 300, 200, 0x00FF0000, &img); // test limit
	make_line_r(250, 250, 300, 199, 0x0000FF00, &img); 
	make_line_r(250, 250, 300, 250, 0x0000FF00, &img);
	make_line_r(250, 250, 300, 225, 0x0000FF00, &img);
	make_line_r(250, 250, 300, 275, 0x0000FF00, &img);
	make_line_r(250, 250, 300, 300, 0x0000FF00, &img);
*/

void	make_line_r(int x1, int y1, int x2, int y2, int color, t_img *img)
{
	int x;
	int y;
	const int dx = ABS(x2 - x1);
	const int dy = ABS(y2 - y1);
	int p;

	x = x1;
	y = y1;
	p = 2 * dy - dx;
	while (x <= x2)
	{
		my_mlx_pixel_put(img, x, y, color);
		x++;
		if (p < 0)
			p += (2 * dy);
		else
		{
			p += (2 * dy) - (2 * dx);
			if (y2 - y1 > 0) // this essentially checks if gradient is negative, this will never be zero because if gradient is zero p will be less than 0
				y++;
			else
				y--;
		}
	}
}

void	make_line_l(int x1, int y1, int x2, int y2, int color, t_img *img)
{
	int x;
	int y;
	const int dx = ABS(x2 - x1);
	const int dy = ABS(y2 - y1);
	int p;

	x = x1;
	y = y1;
	p = 2 * dx - dy;
	while (y <= y2)
	{
		my_mlx_pixel_put(img, x, y, color);
		y++;
		if (p < 0)
			p += (2 * dx);
		else
		{
			p += (2 * dx) - (2 * dy);
			if (x2 - x1 > 0)
				x++;
			else
				x--;
		}
	}
}

void	make_line(int x1, int y1, int x2, int y2, int color, t_img *img)
{
	int temp;
	float grad;

	if (x2 - x1 == 0)
		grad = (y2 - y1);
	else
		grad = (y2 - y1) / (float)(x2 - x1); // can be more efficient i guess, use ints instead of cloat?
	if ((x2 < x1 && ABS(grad) <= 1) || (y2 < y1 && ABS(grad) > 1)) // why don't need to consider the opposite end for y?
	{
		temp = x1;
		x1 = x2;
		x2 = temp;

		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	if (grad >= -1 && grad <= 1)
		make_line_r(x1, y1, x2, y2, color, img);
	else
		make_line_l(x1, y1, x2, y2, color, img);
}

// make_line(250, 250, 300, 300, 0x00FF0000, &img); // test limit
// make_line(250, 250, 300, 301, 0x0000FF00, &img); 
// make_line(250, 250, 300, 200, 0x00FF0000, &img); // test limit
// make_line(250, 250, 300, 199, 0x0000FF00, &img); 
// make_line(250, 250, 300, 250, 0x0000FF00, &img);
// make_line(250, 250, 300, 225, 0x0000FF00, &img);
// make_line(250, 250, 300, 275, 0x0000FF00, &img);
// make_line(250, 250, 300, 300, 0x0000FF00, &img);

// make_line(250, 250, 200, 200, 0x0000FF00, &img); // test limit
// make_line(250, 250, 200, 225, 0x0000FF00, &img); 
// make_line(250, 250, 200, 250, 0x0000FF00, &img); // test limit
// make_line(250, 250, 200, 275, 0x0000FF00, &img); 
// make_line(250, 250, 200, 300, 0x0000FF00, &img);

// make_line(250, 250, 300, 300, 0x00FF0000, &img);
// make_line(250, 250, 275, 300, 0x00FF0000, &img);
// make_line(250, 250, 250, 300, 0x00FF0000, &img);
// make_line(250, 250, 225, 300, 0x00FF0000, &img);
// make_line(250, 250, 200, 300, 0x00FF0000, &img);

// make_line(250, 250, 300, 200, 0x00FF0000, &img);
// make_line(250, 250, 275, 200, 0x00FF0000, &img);
// make_line(250, 250, 250, 200, 0x00FF0000, &img);
// make_line(250, 250, 225, 200, 0x00FF0000, &img);
// make_line(250, 250, 200, 200, 0x00FF0000, &img);
