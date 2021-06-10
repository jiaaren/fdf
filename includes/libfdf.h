/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 12:42:56 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 19:06:27 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFDF_H
# define LIBFDF_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define ISOMETRIC 1
# define PERSPECTIVE 2
# define FIELD_OF_VIEW 45
# define RESO_X 800
# define RESO_Y 800
# define HEX_COLOR 0x0000FF00
# define Z_ADJ 1.0
# define WIN_FIT 0.80

typedef struct s_coor
{
	int	x;
	int	y;
	int	z;
}				t_coor;

typedef struct s_reso
{
	int	w;
	int	h;
}				t_reso;

typedef struct s_trans
{
	int	x;
	int	y;
}				t_trans;

typedef struct s_matrix
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	e;
	float	f;
	float	g;
	float	h;
	float	i;
}				t_matrix;

typedef struct s_win
{
	void	*mlx;
	void	*window;
	int		reso_w;
	int		reso_h;
}				t_win;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		reso_w;
	int		reso_h;
}				t_img;

typedef struct s_grid
{
	t_coor		**grid;
	t_coor		**tmp_grid;
	int			box_len;
	int			row;
	int			col;
}				t_grid;

typedef struct s_tform
{
	t_coor		rot;
	t_trans		trans;
	float		zoom;
	int			projection;
	double		z0_const;
}				t_tform;

typedef struct s_data
{
	t_win		win;
	t_img		img;
	t_grid		grid;
	t_tform		tform;
}				t_data;

// initialisation
void		initialise_window(t_data *data, char *title);
void		initialise_grid(t_data *data, char *filename);
void		initialise_transform(t_data *data);

// grid processing
char		***make_char_arr(t_list *lst, int row);
char		***free_char_arr(char ***split, int row);
t_list		*make_list(int fd, int *row);
t_coor		**alloc_grid(int row, int col);
t_coor		**make_grid(char ***split, t_grid *grid);
t_coor		**free_grid(t_coor **grid, int row);
void		update_tgrid(t_grid *grid, int row, int col);
int			read_file(const char *filename, t_grid *grid);
void		copy_grid(t_grid *grid);

// utils
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			abs_int(int n);
float		abs_float(float n);

// ft_make_line
void		make_line_r(t_coor a, t_coor b, int color, t_img *img);
void		make_line_l(t_coor a, t_coor b, int color, t_img *img);
void		make_line(t_coor a, t_coor b, int color, t_img *img);

// rotation
t_matrix	rotate_x(int degree);
t_matrix	rotate_y(int degree);
t_matrix	rotate_z(int degree);
void		apply_rotate(t_coor *coor, char axis, int degree);

// transformation
void		apply_zoom(t_coor *coor, float zoom);
void		apply_translate(t_coor *coor, t_trans trans);
void		apply_transformation(t_grid *grid, t_tform *tform);

// projection
void		apply_perspective(t_coor *coor, double Z0);
void		apply_iso(t_coor *coor);
void		switch_projection(int *projection);

// image processing
void		clean_image(t_img *img);
void		print_grid_points(t_grid *grid, t_img *img, int color);
void		print_grid_line(t_grid *grid, t_img *img, int color);
void		output_blank(t_data *data);
void		output_grid(t_data *data);

#endif