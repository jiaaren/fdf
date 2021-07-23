/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_grid_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:14:51 by jkhong            #+#    #+#             */
/*   Updated: 2021/07/23 13:52:17 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"
#include "libft.h"

/*
	- Reads *lst of rows for char * separated by ' ' 
	- creates double nested array of char *, and returns data
*/
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
	int	i;
	int	j;

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

// Calls GNL and stores rows in list, returns list
t_list	*make_list(int fd, int *row)
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
	// TO FREE - final char *tmp which has NULL in first index, but still occupies memory
	free(tmp);
	return (lst);
}

// Replicates grid to tmp_grid. Purpose: maintain integrity of grid->grid
void 	copy_grid(t_grid *grid)
{
	int	i;
	int	j;

	i = 0;
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

/*
	Return values:
	1. False, i.e. -1 if columns in each row is inconsistent
	2. If either row or col is 0
	3. Initialises calculates columns and updates int ptr 'col'
*/
int	check_array(char ***split, int row, int *col)
{
	// arr_len to initially store column length
	int	arr_len;
	int	i;
	int	count_tmp;

	*col = 0;
	arr_len = 0;
	// calculates len columns of first row
	while (split && split[0][arr_len])
		arr_len++;
	i = 0;
	while (i < row)
	{
		// resets to 0 and counts columns for each row
		count_tmp = 0;
		while (split[i][count_tmp])
			count_tmp++;
		if (count_tmp != arr_len)
			return (-1);
		i++;
	}
	// update col ptr with col length if no error
	*col = arr_len;
	if (row == 0 || *col == 0)
		return (-1);
	return (0);
}
