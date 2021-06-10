/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 12:42:56 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 15:11:13 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFDF_H
# define LIBFDF_H

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define ABS(x) (((x) < 0) ? -(x) : (x))
# define ISOMETRIC 1
# define PERSPECTIVE 2
# define FIELD_OF_VIEW 45
# define RESO_X 800
# define RESO_Y 800
# define HEX_COLOR 0x00FF0000
# define Z_ADJ 1.0
# define WIN_FIT 0.60

typedef struct s_coor
{
	int x;
	int y;
	int z;
}				t_coor;

typedef struct	s_reso
{
	int w;
	int h;
}				t_reso;

typedef struct	s_trans
{
	int x;
	int y;
}				t_trans;

typedef struct s_matrix
{
	float a;
	float b;
	float c;
	float d;
	float e;
	float f;
	float g;
	float h;
	float i;
}				t_matrix;

// create struct for transformation matrix, zoom and translation



typedef struct	s_win
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

// for cube
// struct for grid (grid & tmp_grid), grid width and grid size as well
typedef struct s_grid
{
	t_coor		**grid;
	t_coor		**tmp_grid;
	int			box_len;
	int			grid_len; // no need?
	int			row;
	int			col;
}				t_grid;

// theta = degree of rotation
typedef struct s_tform
{
	t_coor		rot;
	t_trans		trans;
	float		zoom;
	int			perspective;
}				t_tform;

typedef struct s_data
{
	t_win		win;
	t_img		img;
	t_grid		grid;
	t_tform		tform;
}				t_data;

// grid processing
t_coor	**alloc_grid(int row, int col);
t_coor	**make_grid(char ***split, t_grid *grid);
t_coor	**free_grid(t_coor **grid, int row);
char	***make_char_arr(t_list *lst, int row);
char	***free_char_arr(char ***split, int row);
int		read_file(const char *filename, t_grid *grid);

// utils
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// ft_make_line
// change make_line to accept t_coor
void	make_line_r(int x1, int y1, int x2, int y2, int color, t_img *img);
void	make_line_l(int x1, int y1, int x2, int y2, int color, t_img *img);
void	make_line(int x1, int y1, int x2, int y2, int color, t_img *img);

// rotation
t_matrix	rotate_x(int degree);
t_matrix	rotate_y(int degree);
t_matrix	rotate_z(int degree);
void		apply_rotate(t_coor *coor, char axis, int degree);

// transformation
void	apply_zoom(t_coor *coor, float zoom);
void 	apply_translate(t_coor *coor, t_trans trans);
void 	apply_transformation(t_grid *grid, t_tform *tform);

// projection
void	apply_perspective(t_coor *coor);
void	apply_iso(t_coor *coor);



#endif