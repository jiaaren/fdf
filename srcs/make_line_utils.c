/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 18:15:14 by jkhong            #+#    #+#             */
/*   Updated: 2021/07/23 13:58:15 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

/*
	Purpose: put pixel in coordinate (x, y) based on int color
	- Substitute to standard MiniLibX mlx_pixel_put function

	Also considers edge detection
	- compares x, y coordinate passed in against screen width/height
*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!(x >= 0 && x <= img->reso_w && y >= 0 && y <= img->reso_h))
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// returns absolute amount of int argument passed in
int	abs_int(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

// returns absolute amount of float argument passed in
float	abs_float(float n)
{
	if (n < 0.0)
		return (-n);
	return (n);
}
