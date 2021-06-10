/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_grid_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 12:14:51 by jkhong            #+#    #+#             */
/*   Updated: 2021/06/10 21:03:42 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"
#include "libft.h"

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
	free(tmp);
	return (lst);
}

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

int	check_array(char ***split, int row, int *col)
{
	int	arr_len;
	int	i;
	int	count_tmp;

	*col = 0;
	arr_len = 0;
	while (split && split[0][arr_len])
		arr_len++;
	i = 0;
	while (i < row)
	{
		count_tmp = 0;
		while (split[i][count_tmp])
			count_tmp++;
		if (count_tmp != arr_len)
			return (-1);
		i++;
	}
	*col = arr_len;
	if (row == 0 || *col == 0)
		return (-1);
	return (0);
}
