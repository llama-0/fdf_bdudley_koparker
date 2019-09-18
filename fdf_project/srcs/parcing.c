/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:47:52 by koparker          #+#    #+#             */
/*   Updated: 2019/09/18 20:15:16 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void		error_message(int index, t_data	*data, char **str)
{
	if (index == 0)
		ft_putendl("Invalid altitude in the cart");
	else if (index == 1)
		ft_putendl("Invalid color in the cart");
	else if (index == 2)
		ft_putendl("Invalid length cart");
	else if (index == 3)
		perror("Memory allocation failed\n");
	delete_array(data);
	//TODO: delete split
	ft_free_char_arr(&str);
	exit(1);

}

void		size_array(t_data *data, size_t length)
{
	if (data->size_y == 0)
	{
		data->size_x = length;
		data->capacity_y = length;
	}
	else
		data->capacity_y *= 2;
	data->arr = new_array(&(data->arr), data);
}

t_point		**read_file(const int fd, t_data *data)
{
	size_t	i;
	char	*line;
	char	**split;

	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		i = ft_2d_strlen(split);
		if (data->size_y >= data->capacity_y)
			size_array(data, i);
		if (data->size_x != i)
			error_message(2, data, split);
		i = -1;
		while (++i < data->size_x)
		{
			if (valid_nbr(split[i], data, i, data->size_y) == 0)
				error_message(0, data, split);
			if (valid_color(split[i], data, i, data->size_y) == 0)
				error_message(1, data, split);
		}
		if (split)
			ft_free_char_arr(&split);
		data->size_y++;
	}
	return (data->arr);
}

void	coord_to_pixel(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	step_x;
	size_t	step_y;

	step_x = (data->size_x > 1) ? (DW - 1) / (data->size_x - 1) : DW - 1;
	step_y = (data->size_y > 1) ? (DH - 1) / (data->size_y - 1) : DH - 1;
	j = 0;
	while (j < data->size_y)
	{
		i = 0;
		while (i < data->size_x)
		{
            (data->arr)[j][i].x = i * step_x;
            (data->arr)[j][i].y = j * step_y;
			i++;
		}
		j++;
	}
}

void	shift_coords(int *x, int *y, int shift)
{
	*x += shift;
	*y += shift; 
}