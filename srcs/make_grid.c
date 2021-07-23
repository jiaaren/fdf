/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:51:55 by jkhong            #+#    #+#             */
/*   Updated: 2021/07/23 13:48:10 by jkhong           ###   ########.fr       */
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

/*
	(i) allocate grid using row and col numbers
	(ii) calculate starting x and y coordinates, need to visualise a 4 quadrant axis
	(iii) assign coordinates for all points (i.e. row * col) according to:
		- starting x and y coordinates
		- box_length calculated via make_tgrid()
*/
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
			tmp[i][j].z = -(ft_atoi(split[i][j])) * (grid->box_len) * Z_SCALE;
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

/*
	Calculates optimal box length based upon window resolution
	- compares max box_width and max_box_length and chooses lower value

	Updates and allocates value for tmp_grid variable
*/
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

/*
	Objective: update the grid->grid & grid->tmp_grid variables in data struct
	Return values: returns (-1) if error noted, 0 if success
	Errors: inconsistent columns in each row, Invalid file (handled in initialise.c) 

	Steps
	I. Parse file 
	(i) make_list (MALLOC): generate list of rows using get_next_line and returns lst
	(ii) make_char_arr (MALLOC): returns double dested array for char *, i.e. char***, using ft_split
	e.g. make_list returns {"0 0 0 0"}, while make_char_arr returns {"0", "0", "0", "0"}

	II. Validate data
	(i) check_arr: returns true (0) or false (-1) if number of rows are inconsistent
					- also updates 'col' variable if success
	
	III. Update grid if no errors noted
	(i) update_tgrid:
		- calculates box_len and update data struct
		- (MALLOC) allocates memory for tmp_grid
	(ii) make_grid: reads double nested char * array, uses box_len calculated
		- updates grid pointer in data_struct
	
	IV. Free
	(i) frees list created (*lst)
	(ii) frees double nested char * array (***split)

	V. Return
	(-1) if error noted, 0 if success
*/
int	read_file(int fd, t_grid *grid)
{
	t_list	*lst;
	int		row;
	int		col;
	char	***split;
	int		err;

	err = 0;
	lst = NULL;
	row = 0;
	lst = make_list(fd, &row);
	split = NULL;
	split = make_char_arr(lst, row);
	if (check_array(split, row, &col) == -1)
		err = -1;
	else
	{
		grid->grid = NULL;
		update_tgrid(grid, row, col);
		grid->grid = make_grid(split, grid);
	}
	ft_lstclear(&lst, free);
	split = free_char_arr(split, row);
	close(fd);
	return (err);
}
