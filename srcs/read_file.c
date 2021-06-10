/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:14:51 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 13:36:16 by jkhong           ###   ########.fr       */
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

t_coor	**make_grid(char ***split, int row, int col)
{
	int		i;
	int		j;
	t_coor	**tmp;

	if (!split)
		return (NULL);
    tmp = alloc_grid(row, col);
	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			// combine this with cube3.c
			tmp[i][j].x = i;
			tmp[i][j].y = j;
			tmp[i][j].z = ft_atoi(split[i][j]);
			j++;
		}
		i++;
	}
	return (tmp);
}

t_coor **free_grid(t_coor **grid, int row)
{
	int i;

	i = 0;
	while (i < row)
		free(grid[i++]);
	free(grid);
	return (NULL);
}


char 	***make_char_arr(t_list *lst, int row)
{
	char	***split;
	int		i;

	split = malloc(sizeof(char **) * row);
	i = row - 1;
	while (i >= 0)
	{
		split[i] = ft_split((char *)(lst->content), ' ');
		lst = lst->next;
		i--;
	}
	return (split);
}

char	***free_char_arr(char ***split, int row)
{
	int i;
	int j;

	i = 0;

	while (i < row)
	{
		j = 0;
		while (split[i][j])
		{
			free(split[i][j]);
			j++;
		}
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

t_list  *make_list(int fd, int *row)
{
	char	*tmp;
	t_list	*lst;

	lst = NULL;
	*row = 0;
	while (get_next_line(fd, &tmp) > 0)
	{
		ft_lstadd_front(&lst, ft_lstnew(tmp));
		(*row)++;
	}
    // why is there still something in tmp?, because of the zero?
    free(tmp); // not sure why this is required
    return (lst);
}

void    update_tgrid(t_grid *grid, int row, int col)
{
    int max_box_width;
    int max_box_height;

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

int read_file(const char *filename, t_grid *grid)
{
	int		fd;
	t_list	*lst;
	int		row;
    char	***split;

	lst = NULL;
	row = 0;
	fd = open(filename, O_RDONLY);
	if (fd == - 1)
		return (-1);
    lst = make_list(fd, &row);
    split = NULL;
	split = make_char_arr(lst, row);


	// can probably modify ft_split to also return the number of words, i.e. ft_split2
	int col;
	col = 0;
	while (split && split[0][col])
		col++;
    
	grid->grid = NULL;
	grid->grid = make_grid(split, row, col);

	// if (grid->grid)
	// {
	// 	for (int i = 0; i < row; i ++)
	// 	{
	// 		for (int j = 0; j < col; j++)
	// 			printf("%2i ", grid->grid[i][j].z);
	// 		printf("\n");
	// 	}
	// }
	// figur eout how to free

	// freeing everything

	ft_lstclear(&lst, free);
	split = free_char_arr(split, row);
	grid->grid = free_grid(grid->grid, row);
	close(fd);
	return (0);
}