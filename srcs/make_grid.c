/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:51:55 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 16:58:16 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"
#include "libft.h"

t_coor	**alloc_grid(int row, int col)
{
	t_coor	**tmp;
	int		i;

	tmp = malloc(sizeof(t_coor *) * row);
	i = 0;
	while (i < row)
	{
		tmp[i] = malloc(sizeof(t_coor) * col);
		i++;
	}
	return (tmp);
}

t_coor	**make_grid(char ***split, t_grid *grid)
{
	int		i;
	int		j;
	t_coor	**tmp;
	int		start_x;
	int		start_y;

	if (!split)
		return (NULL);
	tmp = alloc_grid(grid->row, grid->col);
	i = 0;
	start_x = -(grid->box_len * (grid->col - 1) / 2);
	start_y = (grid->box_len * (grid->row - 1) / 2);
	while (i < grid->row)
	{
		j = 0;
		while (j < grid->col)
		{
			tmp[i][j].x = start_x + (j * grid->box_len);
			tmp[i][j].y = start_y - (i * grid->box_len);
			tmp[i][j].z = -(ft_atoi(split[i][j])) * (grid->box_len) * Z_ADJ;
			j++;
		}
		i++;
	}
	return (tmp);
}

t_coor	**free_grid(t_coor **grid, int row)
{
	int	i;

	i = 0;
	while (i < row)
		free(grid[i++]);
	free(grid);
	return (NULL);
}

void	update_tgrid(t_grid *grid, int row, int col)
{
	int	max_box_width;
	int	max_box_height;

	grid->col = col;
	grid->row = row;
	max_box_width = (RESO_X * WIN_FIT) / col;
	max_box_height = (RESO_Y * WIN_FIT) / row;
	if (max_box_width > max_box_height)
		grid->box_len = max_box_width;
	else
		grid->box_len = max_box_height;
	grid->tmp_grid = alloc_grid(row, col);
}

int	read_file(const char *filename, t_grid *grid)
{
	int		fd;
	t_list	*lst;
	int		row;
	int		col;
	char	***split;

	lst = NULL;
	row = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	lst = make_list(fd, &row);
	split = NULL;
	split = make_char_arr(lst, row);
	col = 0;
	while (split && split[0][col])
		col++;
	grid->grid = NULL;
	update_tgrid(grid, row, col);
	grid->grid = make_grid(split, grid);
	ft_lstclear(&lst, free);
	split = free_char_arr(split, row);
	close(fd);
	return (0);
}
